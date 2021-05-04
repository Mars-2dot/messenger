#include "diskapi.h"

diskAPI::diskAPI()
{
    connect( this, &diskAPI::signalGetNodes, this, &diskAPI::slotDonwloadfile );
    connect( this, &diskAPI::signalAddNode, this, &diskAPI::slotAddNode );
}

void diskAPI::slotGetNodes()
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    connect( manager, &QNetworkAccessManager::finished, this, &diskAPI::slotFinishNodes );
    QUrl url ( "https://cloud-api.yandex.net/v1/disk/resources/download?path=nodes.json" );

    request.setUrl( url );
    request.setRawHeader( "Accept", "application/json" );
    request.setRawHeader( "Authorization", "OAuth " + token.toLocal8Bit() );
    manager->get( request );
}

void diskAPI::slotAddRegUser( const QString& name, const QString& password, const QString& ip, const int port )
{
    QFile* file = new QFile( nodesPathFile );
    QDir mkpath;
    mkpath.mkpath( QDir::currentPath() + "/temp" );
    QFile* fileUpload = new QFile( nodesUploadPath );

    if ( file->open( QFile::ReadOnly ) ) {
        QJsonObject json = QJsonDocument::fromJson( file->readAll() ).object(), RegList;
        QJsonArray regUser, temp;
        temp = json["RegList"].toArray();

        for ( int i = 0; i < temp.size(); i++ ) {
            QJsonObject subTree = temp[i].toObject();
            regUser.append( temp[i] );
        }

        RegList.insert( "Name", name );
        RegList.insert( "pasword", password );
        RegList.insert( "IP", ip );
        RegList.insert( "PORT", port );

        regUser.append( RegList );
        json.insert( "RegList", regUser );
        file->close();

        if ( fileUpload->open( QFile::WriteOnly ) ) {
            fileUpload->write( QJsonDocument( json ).toJson() );
            fileUpload->close();
            getLinkToUpload( "nodes.json", "", true );
        } else {
            spdlog::error( "Error write file" );
        }
    } else {
        spdlog::error( "Error read file" );
    }
}

void diskAPI::slotDonwloadfile( const QString& link )
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    connect( manager, &QNetworkAccessManager::finished, this, &diskAPI::slotDonwloadReady );

    request.setUrl( link  );
    manager->get( request );
}

void diskAPI::slotUpdateNodes( const QString& path, const QString& ip, const int& port, const QString& name )
{
    QJsonObject nodes, users, regList;
    QJsonArray userArray, regArray;

    regList.insert( "RegName", "User" );
    regList.insert( "pwd", "123" );

    userArray.append( users );
    regArray.append( regList );

    nodes.insert( "Nodes", userArray );
    nodes.insert( "RegList", regArray );

    QJsonDocument jsonDoc( nodes );
    QString nodesJson = jsonDoc.toJson( QJsonDocument::Indented );

    QFile file;
    file.setFileName( "nodes.json" );
    file.open( QIODevice::WriteOnly | QIODevice::Text );
    QTextStream stream( &file );
    stream << nodesJson;
    file.close();
}

void diskAPI::slotFinishNodes( QNetworkReply* reply )
{
    if ( !reply->error() ) {
        QJsonDocument document = QJsonDocument::fromJson( reply->readAll() );
        QJsonObject root = document.object();

        QString link = root["href"].toString();
        emit signalGetNodes( link );
    } else {
        qDebug() << reply->error();
        qDebug() << "error's of reply";
    }
}

void diskAPI::slotDonwloadReady( QNetworkReply* reply )
{
    if ( reply->error() ) {
        qDebug() << reply->errorString();
    } else {
        QFile* file = new QFile( nodesPathFile );

        if ( file->open( QFile::WriteOnly ) ) {
            file->write( reply->readAll() );
            file->close();
        }

        slotParseJson( nodesPathFile );
    }
}

void diskAPI::slotParseJson( const QString& path )
{
    QFile* file = new QFile( path );
    file->open( QFile::ReadOnly );
    QJsonObject root = QJsonDocument::fromJson( file->readAll() ).object();
    QJsonArray nodes = root["Nodes"].toArray();
    QJsonArray regList = root["RegList"].toArray();
    userData usr;
    int lastPort = 2323;

    for ( int i = 0; i < regList.size(); i++ ) {
        QJsonObject subTree = regList[i].toObject();

        for ( QJsonObject::ConstIterator iterator = subTree.constBegin(); iterator != subTree.constEnd(); iterator++ ) {
            if ( iterator.key() == "Name" ) {
                usr.name = iterator.value().toString();
            }

            if ( iterator.key() == "pasword" ) {
                usr.password = iterator.value().toString();
            }

            if ( iterator.key() == "IP" ) {
                usr.ip = iterator.value().toString();
            }

            if ( iterator.key() == "PORT" ) {
                usr.port = iterator.value().toInt();
            }
        }

        if ( lastPort < usr.port ) {
            lastPort = usr.port;
        }

        emit signalUpdateRegistrationData( usr.name, usr.password, usr.ip, usr.port );
    }

    emit signalStartPot( usr.name, usr.password, usr.ip, ++lastPort );

    if ( !nodes.isEmpty() ) {
        emit signalAddNode( root );
    } else {

    }
}

void diskAPI::getLinkToUpload( QString path, QString fields, bool owerwrite )
{
    connect( manager, &QNetworkAccessManager::finished, this, &diskAPI::slotFinishLinkUpload );
    QUrl url ( "https://cloud-api.yandex.net/v1/disk/resources/upload?path=" + path + "&fields=" + fields );

    if ( owerwrite ) {
        url.setUrl( url.toString() + "&overwrite=true" );
    }

    request.setUrl( url );
    request.setRawHeader( "Accept", "application/json" );
    request.setRawHeader( "Authorization", "OAuth " + token.toLocal8Bit() );
    manager->get( request );

}

void diskAPI::slotAddNode( QJsonObject& json )
{
    QFile* file = new QFile( nodesPathFile );
    QDir mkpath;
    mkpath.mkpath( QDir::currentPath() + "/temp" );
    QFile* fileUpload = new QFile( nodesUploadPath );

    if ( file->open( QFile::ReadOnly ) ) {
        QJsonObject newNodes;
        QJsonArray nodes;
        newNodes.insert( "Name", user->name );
        newNodes.insert( "IP", user->ip );
        newNodes.insert( "PORT", user->port );
        nodes.append( newNodes );
        json.insert( "Nodes", nodes );
        file->close();

        if ( fileUpload->open( QFile::WriteOnly ) ) {
            fileUpload->write( QJsonDocument( json ).toJson() );
            fileUpload->close();
            getLinkToUpload( "nodes.json", "", true );
        } else {
            spdlog::error( "Error write file" );
        }
    } else {
        spdlog::error( "Error read file" );
    }
}

void diskAPI::slotFinishLinkUpload( QNetworkReply* reply )
{
    if ( !reply->error() ) {
        QJsonDocument document = QJsonDocument::fromJson( reply->readAll() );
        QJsonObject root = document.object();

        QString link = root["href"].toString();
        slotUplodaFile( link );
    } else {
        qDebug() << reply->error();
        qDebug() << "error's of reply";
    }
}

void diskAPI::slotUplodaFile( QString link )
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    connect( manager, &QNetworkAccessManager::finished, this, &diskAPI::slotFinishUpload );
    QUrl url (  link );
    QByteArray reqdata;
    QFile file( nodesUploadPath );

    if ( !file.open( QIODevice::ReadOnly ) ) {
        return;
    }

    reqdata = file.readAll();
    request.setUrl( url );
    request.setRawHeader( "content-type", "application/binary" );
    manager->put( request, reqdata );
}

void diskAPI::slotFinishUpload( QNetworkReply* reply )
{
    if ( !reply->error() ) {
        QJsonDocument document = QJsonDocument::fromJson( reply->readAll() );
        QJsonObject root = document.object();
    } else {
        qDebug() << reply->error();
        qDebug() << "error's of reply";
    }
}
