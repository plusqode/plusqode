/*
 * Copyright (C) 2026 - PlusQode - www.plusqode.com - plusqode@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



   #include "pos/pepsontmt88lan.h"

   
   

bool PEpsonTMT88Lan::send(const QString& ipAddress, int port, const QString& filename, int copyNumber) {

    QString fileContent = PDir::fileContent(filename);

    PTcpSocket tcpSocket;
    bool result = tcpSocket.connectToHost(ipAddress, port);

    if(!result) return false;

    for(int i = 0; i < copyNumber; i++)
        tcpSocket.send(fileContent);

    tcpSocket.waitForBytesWritten();
    tcpSocket.close();

    return true;

}
