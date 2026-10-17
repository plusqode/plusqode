#include "misc/pjsonhttpservice.h"

PJsonHttpService::PJsonHttpService(QObject* parent) :
        QObject(parent) {

    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onRequestFinished(QNetworkReply*)));

}


void PJsonHttpService::postJson(const QString& _url, const QJsonObject& jsonBody) {

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)

    QString url = _url;

    // Gestione corretta dei prefissi http / https
    if (!url.startsWith("http://") && !url.startsWith("https://"))
            url = "http://" + url;

    QUrl urlObj(url);
    QNetworkRequest request(urlObj);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray data = QJsonDocument(jsonBody).toJson(QJsonDocument::Compact);

    //qDebug() << "==>" << url << data;

    // Invio della richiesta POST
    manager.post(request, data);

#endif

}


void PJsonHttpService::onRequestFinished(QNetworkReply* reply) {

    // Recuperiamo il reply inviato dal segnale sender/manager
    // QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    // Se non è stato possibile recuperarlo tramite sender(), usiamo l'argomento gestito internamente
    if (!reply) return;

    // Controllo se ci sono stati errori
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        emit postFinished(responseData);
    }
    else {
        QString errorString = reply->errorString();
        emit postError(errorString);
    }

    // Libera la memoria del QNetworkReply
    reply->deleteLater();

}


int PJsonHttpService::jsonServer(const QString& port, const QString& endpoint) {


}

