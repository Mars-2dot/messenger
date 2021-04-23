#ifndef NETCONTROLLER_H
#define NETCONTROLLER_H

#include "qtincludes.h"

class NetController : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* TcpSocket;

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
    explicit NetController( QObject* parent = nullptr );

private slots:
    void slotReadyRead();
public slots:
    void slotSend( QString command, QString message );
    void slotConnect();
    void slotDisconnect();
    void slotGetOnline();
    void slotUpdateContastList();
    void slotAddContact( const QString& nameUser );
    void slotSendMessage( const QString* mes );
signals:
    void signalError( int );
    void signalLoginSuccessful();
    void signalGetOnline( QString );
    void signalAddContact( const QString& );
    void signalRecoverContactList( QString );
    void signalFromUser( QString );
    void signalContactList( QString );
    void signalUnreadMessage( QStringList );
    void signalSuccessfulAddContact();
    void signalCountUnreadMessage( QStringList );
    void signalConnectSuccessful();
    void signalDisconnect();
    void signalNewMessage( const QString*, const QString* );
    void signalUpdateContactList( const QString& );
};

#endif // NETCONTROLLER_H
