#include "core.h"
#include <iostream>

void core::friend_request_cb( Tox* tox, const uint8_t* public_key, const uint8_t* message, size_t length,
                              void* user_data )
{
    tox_friend_add_norequest( tox, public_key, NULL );
}

void core::friend_message_cb( Tox* tox, uint32_t friend_number, TOX_MESSAGE_TYPE type, const uint8_t* message,
                              size_t length, void* user_data )
{
    tox_friend_send_message( tox, friend_number, type, message, length, NULL );
}

void core::self_connection_status_cb( Tox* tox, TOX_CONNECTION connection_status, void* user_data )
{
    switch ( connection_status ) {
        case TOX_CONNECTION_NONE:
            qDebug() << "Offline\n";
            break;

        case TOX_CONNECTION_TCP:
            qDebug() << "Online, using TCP\n";
            break;

        case TOX_CONNECTION_UDP:
            qDebug() << "Online, using UDP\n";
            break;
    }
}

void core::tox_friend_connection_status_cb( Tox* tox, uint32_t friend_number, TOX_CONNECTION connection_status,
                                            void* user_data )
{

}

uint8_t* core::QStringToUint8_t( QString& str )
{
    uint8_t* result = std::copy( str.toUtf8().begin(), str.toUtf8().end(), result );
    return result;
}

void core::toxCallbacks()
{
    tox_callback_friend_request( tox, friend_request_cb );
    tox_callback_friend_message( tox, friend_message_cb );
    tox_callback_self_connection_status( tox, self_connection_status_cb );
    tox_callback_friend_connection_status( tox, tox_friend_connection_status_cb );
}

void core::toxBootstrap( unsigned char* key_bin )
{
    DHT_node nodes[] = {
        {"85.143.221.42",                      33445, "DA4E4ED4B697F2E9B000EEFE3A34B554ACD3F45F5C96EAEA2516DD7FF9AF7B43"},
        {"2a04:ac00:1:9f00:5054:ff:fe01:becd", 33445, "DA4E4ED4B697F2E9B000EEFE3A34B554ACD3F45F5C96EAEA2516DD7FF9AF7B43"},
        {"78.46.73.141",                       33445, "02807CF4F8BB8FB390CC3794BDF1E8449E9A8392C5D3F2200019DA9F1E812E46"},
        {"2a01:4f8:120:4091::3",               33445, "02807CF4F8BB8FB390CC3794BDF1E8449E9A8392C5D3F2200019DA9F1E812E46"},
        {"tox.initramfs.io",                   33445, "3F0A45A268367C1BEA652F258C85F4A66DA76BCAA667A49E770BCC4917AB6A25"},
        {"tox2.abilinski.com",                 33445, "7A6098B590BDC73F9723FC59F82B3F9085A64D1B213AAF8E610FD351930D052D"},
        {"205.185.115.131",                       53, "3091C6BEB2A993F1C6300C16549FABA67098FF3D62C6D253828B531470B53D68"},
        {"tox.kurnevsky.net",                  33445, "82EF82BA33445A1F91A7DB27189ECFC0C013E06E3DA71F588ED692BED625EC23"}
    };

    for ( size_t i = 0; i < sizeof( nodes ) / sizeof( DHT_node ); i ++ ) {
        sodium_hex2bin( key_bin, sizeof( key_bin ), nodes[i].key_hex, sizeof( nodes[i].key_hex ) - 1,
                        NULL, NULL, NULL );
        tox_bootstrap( tox, nodes[i].ip, nodes[i].port, key_bin, NULL );
    }
}

void core::signUp( const QString& Name, const QString& Password )
{
    tox = tox_new( NULL, NULL );
    QByteArray temp = Name.toLocal8Bit();
    static const char* name = temp.data();
    tox_self_set_name( tox,  ( const uint8_t* ) name, strlen( name ), NULL );
    static const char* status_message = temp.data();
    tox_self_set_status_message( tox, ( const uint8_t* )status_message, strlen( status_message ), NULL );

    toxBootstrap();

    uint32_t fileSize = tox_get_savedata_size( tox );
    data.resize( fileSize );

    tox_get_savedata( tox, ( uint8_t* )data.data() );

    toxSave.setFileName( "tox.save" );
    toxSave.open( QIODevice::WriteOnly );
    toxSave.write( data );
    toxSave.close();
}

void core::signIn( const QString& name, const QString& password )
{
    toxSave.setFileName( "tox.save" );
    toxSave.open( QIODevice::ReadOnly );
    data = toxSave.readAll();
    toxSave.close();
    size_t sizeData = data.size();

    tox_options_set_savedata_type( options, TOX_SAVEDATA_TYPE_TOX_SAVE );
    tox_options_set_savedata_data( options, ( uint8_t* )data.data(), sizeData );

    toxSave.setFileName( "keyPublic" );

    if ( !toxSave.exists() ) {
        toxSave.open( QIODevice::ReadOnly );
        data.clear();
        data = toxSave.readAll();
        toxSave.close();
    }

    unsigned char* key_bin;
    key_bin = ( unsigned char* )data.data();

    tox = tox_new( options, NULL );
    toxBootstrap( key_bin );
}

void core::saveData()
{
    uint8_t tox_id_bin[TOX_ADDRESS_SIZE];
    uint8_t tox_public_key[TOX_PUBLIC_KEY_SIZE];
    uint8_t tox_private_key[TOX_SECRET_KEY_SIZE];

    tox_self_get_address( tox, tox_id_bin );
    tox_self_get_public_key( tox, tox_public_key );
    tox_self_get_secret_key( tox, tox_private_key );

    char tox_id_hex[TOX_ADDRESS_SIZE * 2 + 1];
    char tox_public_hex[TOX_PUBLIC_KEY_SIZE * 2 + 1];
    char tox_private_hex[TOX_SECRET_KEY_SIZE * 2 + 1];

    sodium_bin2hex( tox_id_hex, sizeof( tox_id_hex ), tox_id_bin, sizeof( tox_id_bin ) );
    sodium_bin2hex( tox_public_hex, sizeof( tox_public_hex ), tox_public_key, sizeof( tox_public_key ) );
    sodium_bin2hex( tox_private_hex, sizeof( tox_private_hex ), tox_private_key, sizeof( tox_private_key ) );

    for ( size_t i = 0; i < sizeof( tox_id_hex ) - 1; i ++ ) {
        tox_id_hex[i] = toupper( tox_id_hex[i] );
    }

    for ( size_t i = 0; i < sizeof( tox_public_hex ) - 1; i ++ ) {
        tox_public_hex[i] = toupper( tox_public_hex[i] );
    }

    for ( size_t i = 0; i < sizeof( tox_private_hex ) - 1; i ++ ) {
        tox_private_hex[i] = toupper( tox_private_hex[i] );
    }

    toxSave.setFileName( "keyPublic" );

    if ( !toxSave.exists() ) {
        toxSave.open( QIODevice::WriteOnly );
        toxSave.write( tox_public_hex );
        toxSave.close();
    }
}

core::core( bool signType, const QString& name, const QString& password )
{
    if ( signType ) {
        signUp( name, password );
    } else {
        signIn( name, password );
    }
}

void core::start()
{
    toxCallbacks();

    while ( 1 ) {
        tox_iterate( tox, NULL );
        usleep( tox_iteration_interval( tox ) * 1000 );
    }

    tox_kill( tox );
}

void core::messageSend( QString& message )
{

}

QStringList* core::getListFriends()
{
    uint32_t* friendsList = new uint32_t( tox_self_get_friend_list_size( tox ) );
    tox_self_get_friend_list( tox, friendsList );

    for ( size_t i = 0 ; i < sizeof ( &friendsList ) / sizeof ( uint32_t ); i++ ) {
        qDebug() << friendsList[i];
    }

    QStringList* result;
    return result;
}
