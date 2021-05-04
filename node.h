#ifndef NODE_H
#define NODE_H

#pragma once
#include "qtincludes.h"

class Node : public QObject
{
    Q_OBJECT
public:
    typedef enum netCommands {
        getOnline = 0,
        loginSuccessful = 1,
        recoverContactList = 2,
        message = 3,
        errorLogin = 4,
        addInContactList = 5,
        successfulAddContact = 6,
        errorAddContact = 7,
        updateContactList = 8
    } netCommands ;

    QString netCommand[9] = {
        "getOnline",
        "loginSuccessful",
        "recoverContactList",
        "message",
        "errorLogin",
        "addInContactList",
        "successfulAddContact",
        "errorAddContact",
        "updateContactList"
    };

public:
    explicit Node( QObject* parent = nullptr );

private:
    QTcpServer* node = new QTcpServer();
public slots:
    void slotStartPort( const QString& name, const QString& password, const QString& ip, const int port );
private slots:
    void slotNewConnection();
    void slotReadyRead();
signals:
    void signalNewMessage( const QString&, const QString& );
};

#endif // NODE_H
