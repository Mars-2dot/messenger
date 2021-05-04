#ifndef DISKAPI_H
#define DISKAPI_H

#pragma once
#include "qtincludes.h"

class diskAPI : public QObject
{
    Q_OBJECT
public:
    struct userData {
        QString name;
        QString password;
        QString ip;
        int     port;
    };
    userData* user = new userData;
private:
    QNetworkRequest request;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QString token = "AQAAAABUhgnSAADLW2uvWzGSTEiNiBP3HKEnqgI";
    QString nodesPathFile = QDir::currentPath() + "/nodes.json";
    QString nodesUploadPath = QDir::currentPath() + "/temp/nodes.json";

public:
    diskAPI(  );
public slots:
    void slotGetNodes();
    void slotAddRegUser( const QString& name, const QString& password, const QString& ip, const int port );
private slots:
    void slotDonwloadfile( const QString& link );
    void slotUpdateNodes( const QString& path, const QString& ip, const int& port, const QString& name );
    void slotFinishNodes( QNetworkReply* reply );
    void slotDonwloadReady( QNetworkReply* reply );
    void slotParseJson( const QString& path );
    void getLinkToUpload( QString path, QString fields, bool owerwrite );
    void slotFinishLinkUpload( QNetworkReply* reply );
    void slotUplodaFile( QString link );
    void slotFinishUpload( QNetworkReply* reply );
    void slotAddNode( QJsonObject& json );
signals:
    void signalGetNodes( const QString& );
    void signalReadNodes( const QString& );
    void signalUpdateRegistrationData( const QString& nameUser, const QString& passwordUser, const QString& ipUser,
                                       const int portUser );
    void signalOperationCompleted();
    void signalAddNode( QJsonObject& );
    void signalStartPot( const QString& name, const QString& password, const QString& ip, const int port );
};
#endif // DISKAPI_H
