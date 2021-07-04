#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QFile>

#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sodium/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <tox/tox.h>

#ifdef __cplusplus
}
#endif

class core : public QObject
{
    Q_OBJECT

private:
    Tox* tox ;
    QFile toxSave;
    Tox_Options* options = tox_options_new( NULL );

    typedef struct DHT_node {
        const char* ip;
        uint16_t port;
        const char key_hex[TOX_PUBLIC_KEY_SIZE * 2 + 1];
    } DHT_node;

    QByteArray data;

public:
    core( bool signType, const QString& name, const QString& password );
    void start( );
    void messageSend( QString& message );
    QStringList* getListFriends();

private:
    static void friend_request_cb( Tox* tox, const uint8_t* public_key, const uint8_t* message, size_t length,
                                   void* user_data );
    static void friend_message_cb( Tox* tox, uint32_t friend_number, TOX_MESSAGE_TYPE type, const uint8_t* message,
                                   size_t length, void* user_data );
    static void self_connection_status_cb( Tox* tox, TOX_CONNECTION connection_status, void* user_data );
    static void tox_friend_connection_status_cb( Tox* tox, uint32_t friend_number, TOX_CONNECTION connection_status,
                                                 void* user_data );
    uint8_t* QStringToUint8_t( QString& str );
    void toxCallbacks();
    void toxBootstrap( unsigned char* key_bin = nullptr );
    void signUp( const QString& Name, const QString& Password );
    void signIn( const QString& Name, const QString& Password );
    void saveData();

signals:
    void signalToxData( const QString&, const QString&, const QString& );
    void signalStatus( QString& );
    void signalClientInfo( uint32_t, TOX_MESSAGE_TYPE, const uint8_t*, size_t );
    void signalSaveData( QByteArray& );
    void signalSetStatus( int );
};

#endif // CORE_H
