import sys
import os
import argparse
import asyncio
import base64
import struct
import json
import numpy as np
from google import genai
from google.genai import types

# ==================== GLOBALS (Popolate dal server backend) ====================
HOST = "127.0.0.1"
PORT = 8888
PLUSQODE_SERVER_HOST = "127.0.0.1"
PLUSQODE_SERVER_PORT = 9090
AGENT_NAME = "hotel"
GEMINI_API_KEY = ""
GEMINI_MODEL_NAME = "gemini-2.5-flash-native-audio-preview-12-2025"
VOICE_NAME = "Aoede"

DYNAMIC_INSTRUCTION = ""
WELCOME_MESSAGE = "Benvenuto nel ristorante La Trota, come posso aiutarla?"
MODEL_NAME = "booking"

# Nuovi parametri
LANGUAGE = "it-IT"
TEMPERATURE = None
MAX_OUTPUT_TOKENS = None
# ==============================================================================

CRUD_ACTIONS = [
    "find",
    "findFirst",
    "findByTableViewFields",
    "findByTableViewFieldsFirst",
    "create",
    "update",
    "updateFirst",
    "delete"
]


async def send_to_plusqode_server(command: str, payload: dict) -> dict:
    """Sends a JSON command to the PlusQode server and returns the response."""
    print(f"\n[PLUSQODE CLIENT] Command: '{command}' | Payload: {payload}")
    try:
        reader, writer = await asyncio.open_connection(PLUSQODE_SERVER_HOST, PLUSQODE_SERVER_PORT)
        writer.write((json.dumps({"command": command, "payload": payload}, ensure_ascii=False) + "\n").encode('utf-8'))
        await writer.drain()
        
        response_bytes = await reader.readline()
        writer.close()
        await writer.wait_closed()
        
        return json.loads(response_bytes.decode('utf-8')) if response_bytes else {"status": "error", "message": "No response received"}
    except Exception as e:
        print(f"[!] PlusQode connection error: {e}")
        return {"status": "error", "message": str(e)}


async def fetch_config_from_plusqode():
    """Recupera l'intera configurazione, il prompt e il messaggio di benvenuto dal backend PlusQode all'avvio."""
    global HOST, PORT, AGENT_NAME
    global GEMINI_API_KEY, GEMINI_MODEL_NAME, VOICE_NAME
    global DYNAMIC_INSTRUCTION, WELCOME_MESSAGE, MODEL_NAME
    global LANGUAGE, TEMPERATURE, MAX_OUTPUT_TOKENS

    res = await send_to_plusqode_server("pbx_voice_agent.findFirst", {"name": AGENT_NAME})

    print("\n" + "="*20 + " RISPOSTA CONFIGURAZIONE DAL BACKEND PLUSQODE " + "="*20)
    print(json.dumps(res, indent=2, ensure_ascii=False))
    print("="*80 + "\n")

    if res.get("status") == "error":
        print(f"[!] ERRORE CRITICO: Impossibile recuperare la configurazione dal server PlusQode: {res.get('message')}")
        sys.exit(1)

    result_data = res.get("result", res) if isinstance(res.get("result"), dict) else res

    if isinstance(result_data, dict):
        DYNAMIC_INSTRUCTION = str(result_data.get("description", "")).strip()
        
        if result_data.get("welcome_message"):
            WELCOME_MESSAGE = str(result_data["welcome_message"]).strip()
        
        if result_data.get("model_name"):
            MODEL_NAME = str(result_data["model_name"]).strip()
            
        # Controllo dei campi sia in nuova che in vecchia nomenclatura JSON
        if result_data.get("host"):
            HOST = str(result_data["host"]).strip()
        elif result_data.get("listen_host"):
            HOST = str(result_data["listen_host"]).strip()

        if result_data.get("port"):
            PORT = int(result_data["port"])
        elif result_data.get("listen_port"):
            PORT = int(result_data["listen_port"])
        
        if result_data.get("agent_name"):
            AGENT_NAME = str(result_data["agent_name"]).strip()

        if result_data.get("gemini_api_key"):
            GEMINI_API_KEY = str(result_data["gemini_api_key"]).strip()

        if result_data.get("gemini_model_name"):
            GEMINI_MODEL_NAME = str(result_data["gemini_model_name"]).strip()
        elif result_data.get("model_id"):
            GEMINI_MODEL_NAME = str(result_data["model_id"]).strip()

        if result_data.get("voice_name"):
            VOICE_NAME = str(result_data["voice_name"]).strip()

        # Lettura dei nuovi parametri
        if result_data.get("language"):
            LANGUAGE = str(result_data["language"]).strip()

        if result_data.get("temperature") is not None:
            TEMPERATURE = float(result_data["temperature"])

        if result_data.get("max_output_tokens") is not None:
            MAX_OUTPUT_TOKENS = int(result_data["max_output_tokens"])

    if not DYNAMIC_INSTRUCTION:
        print("[!] ERRORE CRITICO: La 'description' ricevuta dal server PlusQode è VUOTA o ASSENTE.")
        sys.exit(1)

    print("[*] Configurazione caricata con successo dal server backend:")
    print(f"    - HOST              : {HOST}")
    print(f"    - PORT              : {PORT}")
    print(f"    - AGENT_NAME        : {AGENT_NAME}")
    print(f"    - MODEL_NAME        : {MODEL_NAME}")
    print(f"    - GEMINI_MODEL_NAME : {GEMINI_MODEL_NAME}")
    print(f"    - VOICE_NAME        : {VOICE_NAME}")
    print(f"    - LANGUAGE          : {LANGUAGE}")
    print(f"    - TEMPERATURE       : {TEMPERATURE}")
    print(f"    - MAX_OUTPUT_TOKENS : {MAX_OUTPUT_TOKENS}")
    print(f"    - WELCOME_MESSAGE   : {WELCOME_MESSAGE}")
    print(f"    - API_KEY           : {'*' * (len(GEMINI_API_KEY) - 4) + GEMINI_API_KEY[-4:] if GEMINI_API_KEY else 'NON IMPOSTATA'}\n")


def build_generic_tool(model_name: str) -> types.Tool:
    """Crea dinamicamente il tool configurando l'enum con i comandi del modello letto dal backend."""
    allowed_commands = [f"{model_name}.{action}" for action in CRUD_ACTIONS]
    
    return types.Tool(
        function_declarations=[
            types.FunctionDeclaration(
                name="send_command",
                description=f"Esegue comandi di gestione sul modello '{model_name}'.",
                parameters=types.Schema(
                    type=types.Type.OBJECT,
                    properties={
                        "command": types.Schema(
                            type=types.Type.STRING,
                            description=f"Comando da eseguire sul modello '{model_name}'.",
                            enum=allowed_commands
                        ),
                        "payload": types.Schema(
                            type=types.Type.OBJECT,
                            description="Parametri associati al comando."
                        )
                    },
                    required=["command", "payload"]
                )
            )
        ]
    )


def pcm8k_to_pcm16k(pcm_8k_bytes):
    if not pcm_8k_bytes: return b""
    return np.repeat(np.frombuffer(pcm_8k_bytes, dtype='<i2'), 2).astype('<i2').tobytes()


def pcm24k_to_pcm8k(pcm_24k_bytes):
    if isinstance(pcm_24k_bytes, str):
        pcm_24k_bytes = base64.b64decode(pcm_24k_bytes)
    if not pcm_24k_bytes: return b""
    return np.frombuffer(pcm_24k_bytes, dtype='<i2')[::3].astype('<i2').tobytes()


async def handle_audiosocket_connection(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    peer = writer.get_extra_info('peername')
    print(f"\n[+] AudioSocket connection established: {peer}")

    # Costruisci il Tool dinamicamente usando il model_name scaricato
    current_tool = build_generic_tool(MODEL_NAME)

    pcm_out_buffer = bytearray()
    buffer_lock = asyncio.Lock()

    # Client inizializzato con le credenziali ricevute dal backend
    client = genai.Client(api_key=GEMINI_API_KEY, http_options={'api_version': 'v1alpha'})

    # Costruzione dinamica dei parametri di configurazione
    config_args = {
        "response_modalities": ["AUDIO"],
        "tools": [current_tool],
        "speech_config": types.SpeechConfig(
            voice_config=types.VoiceConfig(prebuilt_voice_config=types.PrebuiltVoiceConfig(voice_name=VOICE_NAME))
        ),
        "system_instruction": types.Content(
            parts=[types.Part.from_text(text=f"Lingua della conversazione: {LANGUAGE}\n\n{DYNAMIC_INSTRUCTION}")]
        )
    }

    if TEMPERATURE is not None:
        config_args["temperature"] = TEMPERATURE

    if MAX_OUTPUT_TOKENS is not None:
        config_args["max_output_tokens"] = MAX_OUTPUT_TOKENS

    config = types.LiveConnectConfig(**config_args)

    try:
        async with client.aio.live.connect(model=GEMINI_MODEL_NAME, config=config) as session:
            print("[✓] Gemini Live session active")

            print("[*] Invio messaggio di avvio per far parlare Gemini per primo...")
            
            trigger_prompt = (
                f"L'utente si è appena connesso alla chiamata. "
                f"Dai subito il benvenuto dicendo esattamente: '{WELCOME_MESSAGE}'"
            )
            
            await session.send_client_content(
                turns=[
                    types.Content(
                        role="user",
                        parts=[
                            types.Part.from_text(text=trigger_prompt)
                        ]
                    )
                ],
                turn_complete=True
            )

            async def audiosocket_to_gemini():
                while True:
                    try:
                        header = await reader.readexactly(3)
                        if header[0] == 0x00 or struct.unpack(">H", header[1:3])[0] == 0: break
                        pcm_data = await reader.readexactly(struct.unpack(">H", header[1:3])[0])

                        if header[0] == 0x10:
                            async with buffer_lock:
                                is_speaking = len(pcm_out_buffer) > 640
                            if not is_speaking:
                                pcm_16k = pcm8k_to_pcm16k(pcm_data)
                                if pcm_16k:
                                    await session.send_realtime_input(audio=types.Blob(data=pcm_16k, mime_type="audio/pcm;rate=16000"))
                    except Exception:
                        break

            async def gemini_to_buffer():
                nonlocal pcm_out_buffer
                while True:
                    try:
                        async for response in session.receive():
                            if response.tool_call:
                                for fc in response.tool_call.function_calls:
                                    res = await send_to_plusqode_server(
                                        fc.args.get("command", ""), 
                                        fc.args.get("payload", {})
                                    )
                                    await session.send_tool_response(
                                        function_responses=[
                                            types.FunctionResponse(name=fc.name, id=fc.id, response={"result": res})
                                        ]
                                    )

                            if response.server_content:
                                if response.server_content.interrupted:
                                    async with buffer_lock: pcm_out_buffer.clear()
                                    continue
                                if response.server_content.model_turn:
                                    for part in response.server_content.model_turn.parts:
                                        if part.inline_data and part.inline_data.data:
                                            pcm_8k = pcm24k_to_pcm8k(part.inline_data.data)
                                            if pcm_8k:
                                                async with buffer_lock: pcm_out_buffer.extend(pcm_8k)
                    except asyncio.CancelledError:
                        break
                    except Exception as e:
                        print(f"[!] Gemini receiving error: {e}")
                        break

            async def buffer_to_audiosocket():
                nonlocal pcm_out_buffer
                while True:
                    try:
                        await asyncio.sleep(0.02)
                        async with buffer_lock:
                            if len(pcm_out_buffer) >= 320:
                                chunk, pcm_out_buffer = bytes(pcm_out_buffer[:320]), pcm_out_buffer[320:]
                            else:
                                chunk = None
                        if chunk:
                            writer.write(struct.pack(">BH", 0x10, len(chunk)) + chunk)
                            await writer.drain()
                    except asyncio.CancelledError:
                        break
                    except Exception:
                        break

            await asyncio.gather(audiosocket_to_gemini(), gemini_to_buffer(), buffer_to_audiosocket())

    except Exception as e:
        print(f"[!] Session error: {e}")
    finally:
        writer.close()
        await writer.wait_closed()


async def main():
    # 1. Recupera la configurazione e il prompt direttamente da PlusQode
    await fetch_config_from_plusqode()

    # 2. Avvia il server usando HOST e PORT ricevuti dal backend
    server = await asyncio.start_server(handle_audiosocket_connection, HOST, PORT)
    print(f"[*] AudioSocket Server listening on {HOST}:{PORT}")
    print(f"[*] Connected to PlusQode Backend on {PLUSQODE_SERVER_HOST}:{PLUSQODE_SERVER_PORT}")
    
    async with server:
        await server.serve_forever()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="AudioSocket Gemini Agent with direct PlusQode configuration")
    parser.add_argument("plusqode_host", help="Host del server PlusQode (es. 127.0.0.1)")
    parser.add_argument("plusqode_port", type=int, help="Porta del server PlusQode (es. 8888)")
    parser.add_argument("agent_name", help="Agent Name (es. hotel)")

    args = parser.parse_args()

    PLUSQODE_SERVER_HOST = args.plusqode_host
    PLUSQODE_SERVER_PORT = args.plusqode_port
    AGENT_NAME           = args.agent_name

    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\n[*] Server stopped.")
