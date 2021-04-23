#include "netcontroller.h"

NetController::NetController( QObject* parent ) : QObject( parent )
{
}

void NetController::slotReadyRead()
{
    QDataStream in( TcpSocket );
    QTime time;
    QString data;
    in >> time >> data;
    QStringList ServerMessage = data.split( "|" );

    if ( ServerMessage[0] == netCommand[errorLogin] ) {
        emit signalError( 2 );
    } else if ( ServerMessage[0] == netCommand[message] ) {
        const QString& sender = ServerMessage[1];
        const QString& mes = ServerMessage[2];
        emit signalNewMessage( &sender, &mes );
    } else if ( ServerMessage[0] == netCommand[getOnline] ) {
        emit signalGetOnline( ServerMessage[1] );
    } else if ( ServerMessage[0] == netCommand[successfulAddContact] ) {
        emit signalUpdateContactList( ServerMessage[1] );
    } else if ( ServerMessage[0] == "ConnectSuccessful" ) {
        emit signalConnectSuccessful();
    } else if ( ServerMessage[0] == netCommand[loginSuccessful] ) {
        emit signalLoginSuccessful();
    } else if ( ServerMessage[0] == netCommand[updateContactList] ) {
        emit signalUpdateContactList( ServerMessage[1] );
    } else if ( ServerMessage[0] == netCommand[recoverContactList] ) {
        emit signalRecoverContactList( ServerMessage[1] );
    } else if ( ServerMessage[0] == "errorAddContact" ) {
        emit signalError( 3 );
    } else if ( ServerMessage[0] == "PersonalContactList" ) {
        emit signalContactList( ServerMessage[1] );
    } else if ( ServerMessage[0] == "fromUser" ) {
        emit signalFromUser( ServerMessage[1] + "|" + ServerMessage[2] );
    } else if ( ServerMessage[0] == "unreadMessage" ) {
        emit signalUnreadMessage( ServerMessage[1].split( "%" ) );
    } else if ( ServerMessage[0] == "successfulAddContact" ) {
        emit signalSuccessfulAddContact();
    } else if ( ServerMessage[0] == "countUnreadMessage" ) {
        emit signalCountUnreadMessage( ServerMessage[1].split( "%" ) );
    } else {
        emit signalError( 0 );
    }
}

void NetController::slotSend( QString command, QString message )
{
    QByteArray arrBlock;
    QDataStream out( &arrBlock, QIODevice::WriteOnly );
    out << QTime::currentTime() << command + "|" + message;
    TcpSocket->write( arrBlock );
}

void NetController::slotConnect()
{
    TcpSocket = new QTcpSocket( this );
    connect( TcpSocket, &QAbstractSocket::errorOccurred, this, &NetController::signalError );
    connect( TcpSocket, &QAbstractSocket::readyRead, this, &NetController::slotReadyRead );
    connect( TcpSocket, &QAbstractSocket::disconnected, this, &NetController::slotDisconnect );
    TcpSocket->connectToHost( QHostAddress::LocalHost, 2323 );

    if ( TcpSocket->waitForConnected( 1000 ) ) {
        emit signalConnectSuccessful();
    } else {
        emit signalError( 1 );
    }
}

void NetController::slotDisconnect()
{
    emit signalDisconnect();
}

void NetController::slotGetOnline()
{
    slotSend( netCommand[getOnline], "" );
}

void NetController::slotUpdateContastList()
{
    slotSend( netCommand[updateContactList], "" );
}

void NetController::slotAddContact( const QString& nameUser )
{
    slotSend( netCommand[addInContactList], nameUser );
}

void NetController::slotSendMessage( const QString* mes )
{
    slotSend( netCommand[message], *mes );
}
