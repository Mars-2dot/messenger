#ifndef NETCONTROLLER_H
#define NETCONTROLLER_H

#pragma once
#include "diskapi.h"
#include "database.h"
#include "node.h"

class NetController : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* socket;
    Node* node = new Node();
    QThread* nodeThread = new QThread();
    QThread* dataBaseTread = new QThread();
    diskAPI* disk = new diskAPI();
    DataBase* dataBase = new DataBase();
    diskAPI::userData user;

public:
    explicit NetController( QObject* parent = nullptr );

public slots:
    void slotAddRegUser( const QString& name, const QString& password, const QString& ip, const int port );
    void slotSetUserData( const QString& name, const QString& password );
    void slotSignUp( diskAPI::userData user );
    void slotCheckUser( const QString& name, const QString& password );
    void slotSendMessage( const QString& mes );
    void slotGetPort( const QString& nameUser );
//    void slotStartPort( const QString& name, const QString& password, const QString& ip, const int port );
private slots:
//    void slotReadyRead();
    void slotSend( QString command, QString message );
    void slotConnect( const QString& name, const QString& password, const QString& ip, const int port );
    void slotConnected();
signals:
    void signalGetNodes();
    void signalGetPort( const QString& nameUser );
    void signalUpdateUserList( const QString& name, const QString& password, const QString& ip, const int port );
    void signalOperationSuccessful( const int );
    void signalAddRegUser( const QString& name, const QString& password, const QString& ip, const int port );
    void signalError( const int );
    void signalConnectSuccessful( const QString&, const QString& );
    void signalNewMessage( const QString&, const QString& );
};

#endif // NETCONTROLLER_H
