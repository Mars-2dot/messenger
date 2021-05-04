#include "netcontroller.h"

NetController::NetController( QObject* parent ) : QObject( parent )
{
    dataBase->moveToThread( dataBaseTread );
    disk->moveToThread( nodeThread );
    node->moveToThread( nodeThread );

    nodeThread->start();
    dataBaseTread->start();

    connect( this, &NetController::signalGetNodes, disk, &diskAPI::slotGetNodes, Qt::DirectConnection );
    connect( disk, &diskAPI::signalUpdateRegistrationData, dataBase, &DataBase::slotUpdateRegistationData,
             Qt::DirectConnection );
    connect( disk, &diskAPI::signalUpdateRegistrationData, this, &NetController::signalUpdateUserList,
             Qt::DirectConnection );
    connect( disk, &diskAPI::signalStartPot, node, &Node::slotStartPort,
             Qt::DirectConnection );
    connect( this, &NetController::signalAddRegUser, disk, &diskAPI::slotAddRegUser, Qt::DirectConnection );
    connect( dataBase, &DataBase::signalSetPort, node, &Node::slotStartPort, Qt::DirectConnection );
    connect( dataBase, &DataBase::signalSetConnect, this, &NetController::slotConnect, Qt::DirectConnection );
    connect( this, &NetController::signalConnectSuccessful, dataBase, &DataBase::slotUpdateStatus, Qt::DirectConnection );
    connect( this, &NetController::signalGetPort, dataBase, &DataBase::slotGetPort, Qt::DirectConnection );

    emit signalGetNodes();
}

void NetController::slotAddRegUser( const QString& name, const QString& password, const QString& ip, const int port )
{
    emit signalAddRegUser( name, password, "localhost", disk->user->port );
}

void NetController::slotSetUserData( const QString& name, const QString& password )
{
    disk->user->name = name;
    disk->user->password = password;

    if ( dataBase->registrationUser( disk->user->name, disk->user->password, disk->user->ip, disk->user->port ) ) {
        emit signalOperationSuccessful( 0 );
    } else {
        emit signalError( 0 );
    }
}

void NetController::slotSignUp( diskAPI::userData user )
{

}

void NetController::slotCheckUser( const QString& name, const QString& password )
{
    if ( dataBase->checkUser( name, password ) ) {
        emit signalOperationSuccessful( 0 );
    } else {
        emit signalError( 2 );
    }
}

void NetController::slotSendMessage( const QString& mes )
{
//    slotSend( netCommand[message], mes );
    slotSend( "message", mes );
}

void NetController::slotGetPort( const QString& nameUser )
{
    emit signalGetPort( nameUser );
}

void NetController::slotConnect( const QString& name, const QString& password, const QString& ip, const int port )
{
    socket = new QTcpSocket();
    connect( socket, &QAbstractSocket::connected, this, &NetController::slotConnected );
    connect( socket, &QAbstractSocket::disconnected, socket, &QAbstractSocket::deleteLater );
    socket->connectToHost( QHostAddress::LocalHost, port );
}

void NetController::slotConnected()
{

}

void NetController::slotSend( QString command, QString message )
{
    QByteArray arrBlock;
    QDataStream out( &arrBlock, QIODevice::WriteOnly );
    out << QTime::currentTime() << command + "|" + message;
    socket->write( arrBlock );
}

//void NetController::slotSendMessage( const QString* mes )
//{
//}
