#include "core.h"

void core::friendRequestCb( Tox* tox, const uint8_t* public_key, const uint8_t* message, size_t length,
                            void* Core )
{
    QString msg = convertString( message, length ).getQString();
    QString publicKey = convertString( public_key, TOX_PUBLIC_KEY_SIZE ).getBytes().toHex();

    emit static_cast<core*>( Core )->signalFriendRequest( msg );
    emit static_cast<core*>( Core )->signalDataBaseAddRequst( msg.split( " " )[0], publicKey, msg );
    emit static_cast<core*>( Core )->signalUpdateUserData();
}

void core::friendMessageCb( Tox* tox, uint32_t friend_number, TOX_MESSAGE_TYPE type, const uint8_t* message,
                            size_t length, void* Core )
{
    QString msg = convertString( message, length ).getQString();
    emit static_cast<core*>( Core )->signalSendMessage( toxGetFriendName( tox, friend_number, Core, NULL ), msg,
                                                        friend_number );
}

void core::selfConnectionStatusCb( Tox* tox, TOX_CONNECTION connection_status, void* Core )
{
    switch ( connection_status ) {
        case TOX_CONNECTION_NONE:
            emit static_cast<core*>( Core )->signalSetStatus( 1 );
            break;

        case TOX_CONNECTION_TCP:
            emit static_cast<core*>( Core )->signalSetStatus( 3 );
            static_cast<core*>( Core )->slotGetListFriends( Core );
            break;

        case TOX_CONNECTION_UDP:
            emit static_cast<core*>( Core )->signalSetStatus( 2 );
            static_cast<core*>( Core )->slotGetListFriends( Core );
            break;
    }
}

void core::toxFriendConnectionStatusCb( Tox* tox, uint32_t friend_number, TOX_CONNECTION connection_status,
                                        void* Core )
{

}

void core::toxLogCb( Tox* tox, TOX_LOG_LEVEL level, const char* file, uint32_t line, const char* func,
                     const char* message, void* Core )
{
}

const QString core::toxGetFriendName( Tox* tox, uint32_t friendNumber, void* core, TOX_ERR_FRIEND_QUERY* error )
{
    uint8_t* name;
    size_t size;
    size = tox_friend_get_name_size( tox, friendNumber, NULL );
    tox_friend_get_name( tox, friendNumber, name, NULL );
    QString qName;
    qName = convertString( name, size ).getQString();
    return qName;
}

void core::toxCallbacks()
{
    tox_callback_friend_request( tox, friendRequestCb );
    tox_callback_friend_message( tox, friendMessageCb );
    tox_callback_self_connection_status( tox, selfConnectionStatusCb );
    tox_callback_friend_connection_status( tox, toxFriendConnectionStatusCb );
}

void core::toxBootstrap( uint8_t* keyBin )
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

    if ( keyBin == nullptr ) {
        unsigned char key_bin[TOX_PUBLIC_KEY_SIZE];

        for ( size_t i = 0; i < sizeof( nodes ) / sizeof( DHT_node ); i ++ ) {
            sodium_hex2bin( key_bin, sizeof( key_bin ), nodes[i].key_hex, sizeof( nodes[i].key_hex ) - 1,
                            NULL, NULL, NULL );
            tox_bootstrap( tox, nodes[i].ip, nodes[i].port, key_bin, NULL );
        }
    } else {
        for ( size_t i = 0; i < sizeof( nodes ) / sizeof( DHT_node ); i ++ ) {
            tox_bootstrap( tox, nodes[i].ip, nodes[i].port, keyBin, NULL );
        }
    }

}

void core::signUp( const QString& Name, const QString& Password )
{
    tox_options_default( options );
    tox_options_set_log_user_data( options, this );
    tox = tox_new( options, NULL );
    QByteArray temp = Name.toLocal8Bit();
    static const char* name = temp.data();
    tox_self_set_name( tox,  ( const uint8_t* ) name, strlen( name ), NULL );
    static const char* status_message = temp.data();
    tox_self_set_status_message( tox, ( const uint8_t* )status_message, strlen( status_message ), NULL );

    toxBootstrap();

    saveData( Name, Password );
}

void core::signIn( const QString& name, const QString& password )
{
    uint8_t* data = ( uint8_t* )convertString( db->getUserData( name ) ).getDataFromQString();
    QString id = db->getToxID( name );
    size_t sizeData = convertString( db->getUserData( name ) ).getBytes().size() / 2;

    emit signalSetId( id );

    tox_options_set_savedata_type( options, TOX_SAVEDATA_TYPE_TOX_SAVE );
    tox_options_set_savedata_data( options, ( uint8_t* )data, sizeData );

    tox = tox_new( options, NULL );
    tox_options_set_log_user_data( options, this );
    tox_options_set_savedata_type( options, TOX_SAVEDATA_TYPE_TOX_SAVE );
    tox_options_set_log_callback( options, toxLogCb );
    tox_get_savedata( tox, data );
    slotSetStatus( TOX_USER_STATUS_NONE );

    uint8_t* keyBin = ( uint8_t* )convertString( db->getUserPublicKey( name ) ).getDataFromQString();
    toxBootstrap( keyBin );
}

void core::saveData( const QString& Name, const QString& Password )
{
    uint8_t toxIdBin[TOX_ADDRESS_SIZE];
    uint8_t toxPublicKey[TOX_PUBLIC_KEY_SIZE];
    uint8_t toxPrivetKey[TOX_SECRET_KEY_SIZE];
    uint32_t dataSize = tox_get_savedata_size( tox );
    data.resize( dataSize  );

    tox_self_get_address( tox, toxIdBin );
    tox_self_get_public_key( tox, toxPublicKey );
    tox_self_get_secret_key( tox, toxPrivetKey );
    tox_get_savedata( tox, ( uint8_t* )data.data() );

    QString id = convertString( toxIdBin, TOX_ADDRESS_SIZE ).getBytes().toHex().toUpper();
    QString publicKey = convertString( toxPublicKey, TOX_PUBLIC_KEY_SIZE ).getBytes().toHex().toUpper();
    QString privetKey = convertString( toxPrivetKey, TOX_SECRET_KEY_SIZE ).getBytes().toHex().toUpper();
    QString userData = convertString( data ).getBytes().toHex();

    emit signalSetId( id );

    db->addUser( Name, Password, userData, publicKey, privetKey, id );
}

const QString& core::getToxId( Tox* tox )
{
    uint8_t tox_id_bin[TOX_ADDRESS_SIZE];
    tox_self_get_address( tox, tox_id_bin );
    char tox_id_hex[TOX_ADDRESS_SIZE * 2 + 1];
    sodium_bin2hex( tox_id_hex, sizeof( tox_id_hex ), tox_id_bin, sizeof( tox_id_bin ) );

    for ( size_t i = 0; i < sizeof( tox_id_hex ) - 1; i ++ ) {
        tox_id_hex[i] = toupper( tox_id_hex[i] );
    }

    toxUser.id = ( char* )tox_id_hex;
    return toxUser.id;
}

core::core( bool signType, const QString& name, const QString& password )
{
    if ( signType ) {
        signUp( name, password );
    } else {
        signIn( name, password );
    }
}

core::core()
{
    connect( this, &core::signalDataBaseAddRequst, db, &DataBase::slotAddRequest );
    connect( this, &core::signalAddFriend, db, &DataBase::slotAddFriend );
    connect( this, &core::signalSaveUserData, db, &DataBase::slotSaveData );
    connect( this, &core::signalUpdateUserData, this, &core::slotUpdateUserData );
}

core::~core()
{
    tox_kill( tox );
}

void core::start()
{
    toxCallbacks();

    while ( 1 ) {
        tox_iterate( tox, this );
        usleep( tox_iteration_interval( tox ) * 1000 );
    }

    tox_kill( tox );
}

void core::login( const QString& name, const QString& password, const bool loginType )
{
    if ( loginType ) {
        signIn( name, password );
    } else {
        signUp( name, password );
    }
}

void core::slotAcceptFriendRequest( const QString& message )
{
    uint8_t* key = ( uint8_t* )convertString( db->getPublicKey( message ) ).getDataFromQString();
    tox_friend_add_norequest( tox, key, NULL );

    emit signalAddFriend( toxUser.Name, message, db->getPublicKey( message ) );
}

void core::slotSendMessage( const QString& message, uint32_t number )
{
    tox_friend_send_message( tox, number, TOX_MESSAGE_TYPE_NORMAL, ( uint8_t* )message.toLocal8Bit().toUInt(),
                             message.size(), NULL );
}

void core::slotAddFriend( const QString& Name )
{

}

void core::slotCheckUser( const QString& name, const QString& password, const bool loginType )
{
    if ( loginType ) {
        if ( db->checkUser( name, password, loginType ) ) {
            emit signalCheckSuccessful( name, password, loginType );
        } else {
            emit signalError( 2 );
        }
    } else {
        if ( db->checkRegUser( name, password, loginType ) ) {
            emit signalCheckSuccessful( name, password, loginType );
        } else {
            emit signalError( 0 );
        }
    }
}

void core::slotGetListFriends( void* core )
{
    size_t friendsListSize = tox_self_get_friend_list_size( tox );
    uint32_t* friendsList = new uint32_t( friendsListSize );
    QStringList qFriendList;
    tox_self_get_friend_list( tox, friendsList );

    for ( size_t i = 0 ; i < friendsListSize; i++ ) {
        qDebug() << friendsList[i];
        qFriendList.append( toxGetFriendName( tox, friendsList[i], core, NULL ) );
    }

    emit signalSendFriendList( qFriendList );
}

void core::slotSetStatus( TOX_USER_STATUS  status )
{
    tox_self_set_status( tox, status );
}

void core::slotFriendAdd( const QString& friendID, const QString& message )
{
    uint8_t* id = ( uint8_t* )convertString( friendID ).getDataFromQString();
    uint8_t* msg = ( uint8_t* )convertString( message ).data();
    tox_friend_add( tox, id, msg, sizeof ( msg ), NULL );
}

void core::slotUpdateUserData()
{
    uint32_t dataSize = tox_get_savedata_size( tox );
    data.resize( dataSize  );
    tox_get_savedata( tox, ( uint8_t* )data.data() );
    QString userData = convertString( data ).getBytes().toHex();
    emit signalSaveUserData( toxUser.Name, userData );
}
