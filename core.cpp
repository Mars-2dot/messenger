#include "core.h"

/******************************************************************************************************
 *												Metods                                                *
 ******************************************************************************************************/

const QString core::toxGetFriendName( Tox* tox, uint32_t friendNumber, void* core, TOX_ERR_FRIEND_QUERY* error )
{
    uint8_t* name;
    size_t size;
    size = tox_friend_get_name_size( tox, friendNumber, nullptr );
    tox_friend_get_name( tox, friendNumber, name, nullptr );
    QString qName;
    qName = convertString( name, size ).getQString();
    return qName;
}

void core::toxBootstrap()
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

    for ( size_t i = 0; i < sizeof( nodes ) / sizeof( DHT_node ); i++ ) {
        unsigned char key_bin[TOX_PUBLIC_KEY_SIZE];
        sodium_hex2bin( key_bin, sizeof( key_bin ), nodes[i].key_hex, sizeof( nodes[i].key_hex ) - 1,
                        nullptr, nullptr, nullptr );
        tox_bootstrap( tox, nodes[i].ip, nodes[i].port, key_bin, nullptr );
    }
}

void core::signUp( const QString& Name, const QString& Password )
{
    tox_options_default( options );
    tox_options_set_log_user_data( options, this );
    tox = tox_new( options, nullptr );
    QByteArray temp = Name.toLocal8Bit();
    static const char* name = temp.data();
    tox_self_set_name( tox,  ( const uint8_t* ) name, strlen( name ), nullptr );
    static const char* status_message = temp.data();
    tox_self_set_status_message( tox, ( const uint8_t* )status_message, strlen( status_message ), nullptr );

    toxBootstrap();

    saveData( Name, Password );
    toxCallbacks();
}

void core::signIn( const QString& name, const QString& password )
{
    uint8_t* data = ( uint8_t* )convertString( db->getUserData( name ) ).getDataFromQString();
    QString id = db->getToxID( name );
    size_t sizeData = convertString( db->getUserData( name ) ).getBytes().size() / 2;

    emit signalSetId( id );

    tox_options_default( options );

    tox_options_set_savedata_type( options, TOX_SAVEDATA_TYPE_TOX_SAVE );
    tox_options_set_savedata_data( options, ( uint8_t* )data, sizeData );
    tox_options_set_savedata_length( options, sizeData );

    tox = tox_new( options, nullptr );

    toxBootstrap( );
    toxCallbacks();
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

    while ( 1 ) {
        tox_iterate( tox, this );
        usleep( tox_iteration_interval( tox ) * 1000 );
    }

    tox_kill( tox );
}

void core::login( const QString& name, const QString& password, const bool loginType )
{
    toxUser.Name = name;
    toxUser.Password = password;

    if ( loginType ) {
        signIn( name, password );
    } else {
        signUp( name, password );
    }
}

void core::slotAcceptFriendRequest( const QString& message )
{
    uint8_t* key = ( uint8_t* )convertString( db->getPublicKey( message ) ).getDataFromQString();

    tox_friend_add_norequest( tox, key, nullptr );

    uint32_t numberFriend = tox_friend_by_public_key( tox, key, nullptr );
    uint32_t dataSize = tox_get_savedata_size( tox );
    data.resize( dataSize  );
    tox_get_savedata( tox, ( uint8_t* )data.data() );
    QString userData = convertString( data ).getBytes().toHex();

    emit signalAddFriend( toxUser.Name, message, db->getPublicKey( message ), userData, QString::number( numberFriend ) );
}

void core::slotSendMessage( const QString& message, const QString& name )
{
    tox_friend_send_message( tox, db->getFriendNumber( name ), TOX_MESSAGE_TYPE_NORMAL, convertString( message ).data(),
                             message.size(), nullptr );
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
        if ( db->checkUser( name, password, loginType ) ) {
            emit signalError( 0 );
        } else {
            emit signalCheckSuccessful( name, password, loginType );
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
        qFriendList.append( toxGetFriendName( tox, friendsList[i], core, nullptr ) );
    }

    delete friendsList;
    emit signalSendFriendList( qFriendList );
}

void core::slotSetStatus( TOX_USER_STATUS  status )
{
    tox_self_set_status( tox, status );
}

void core::slotFriendAdd( const QString& friendID, const QString& message )
{
    uint8_t* toxId = convertString( friendID ).getDataFromQString();
    uint8_t* msg = ( uint8_t* )convertString( message ).data();

    for ( int i = 0; i < TOX_ADDRESS_SIZE; i++ ) {
        qDebug() << i << toxId[i];
    }

    tox_friend_add( tox, toxId, msg, message.size(), nullptr );
}

void core::slotUpdateUserData()
{
    uint32_t dataSize = tox_get_savedata_size( tox );
    data.resize( dataSize  );
    tox_get_savedata( tox, ( uint8_t* )data.data() );
    QString userData = convertString( data ).getBytes().toHex();
    db->slotSaveData( toxUser.Name, userData );
}

/******************************************************************************************************
 *												Callbacks                                             *
 ******************************************************************************************************/
void core::friendRequestCb( Tox* tox, const uint8_t* public_key, const uint8_t* message, size_t length,
                            void* Core )
{
    QString msg = convertString( message, length ).getQString();
    QString publicKey = convertString( public_key, TOX_PUBLIC_KEY_SIZE ).getBytes().toHex();

    emit static_cast<core*>( Core )->signalFriendRequest( msg );
    emit static_cast<core*>( Core )->signalDataBaseAddRequst( msg.split( " " )[0], publicKey, msg );
}

void core::friendMessageCb( Tox* tox, uint32_t friend_number, TOX_MESSAGE_TYPE type, const uint8_t* message,
                            size_t length, void* Core )
{
    QString msg = convertString( message, length ).getQString();
    emit static_cast<core*>( Core )->signalSendMessage( toxGetFriendName( tox, friend_number, Core, nullptr ), msg,
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

//IN PORGRESS

void core::toxFriendConnectionStatusCb( Tox* tox, uint32_t friend_number, TOX_CONNECTION connection_status,
                                        void* Core )
{
    qWarning() << "toxFriendConnectionStatusCb";
}

void core::toxLogCb( Tox* tox, TOX_LOG_LEVEL level, const char* file, uint32_t line, const char* func,
                     const char* message, void* Core )
{
    qWarning() << "toxLogCb";
}

void core::toxFriendNameCb( Tox* tox, uint32_t friend_number, const uint8_t* name, size_t length, void* Core )
{
    qWarning() << "toxFriendNameCb";
}

void core::toxFriendStatusMessageCb( Tox* tox, uint32_t friend_number, const uint8_t* message, size_t length,
                                     void* Core )
{
    qWarning() << "toxFriendStatusMessageCb";
}

void core::toxFriendStatusCb( Tox* tox, uint32_t friend_number, TOX_USER_STATUS status, void* Core )
{
    qWarning() << "toxFriendStatusCb";
}

void core::toxFriendTypingCb( Tox* tox, uint32_t friend_number, bool is_typing, void* Core )
{
    qWarning() << "toxFriendTypingCb";
}

void core::toxFriendReadReceiptCb( Tox* tox, uint32_t friend_number, uint32_t message_id, void* Core )
{
    qWarning() << "toxFriendReadReceiptCb";
}

void core::toxFileRecvControlCb( Tox* tox, uint32_t friend_number, uint32_t file_number, TOX_FILE_CONTROL control,
                                 void* Core )
{
    qWarning() << "toxFileRecvControlCb";
}

void core::toxFileChunkRequestCb( Tox* tox, uint32_t friend_number, uint32_t file_number, uint64_t position,
                                  size_t length, void* Core )
{
    qWarning() << "toxFileChunkRequestCb";
}

void core::toxFileRecvCb( Tox* tox, uint32_t friend_number, uint32_t file_number, uint32_t kind, uint64_t file_size,
                          const uint8_t* filename, size_t filename_length, void* Core )
{
    qWarning() << "toxFileRecvCb";
}

void core::toxFileRecvChunkCb( Tox* tox, uint32_t friend_number, uint32_t file_number, uint64_t position,
                               const uint8_t* data, size_t length, void* Core )
{
    qWarning() << "toxFileRecvChunkCb";
}

void core::toxConferenceInviteCb( Tox* tox, uint32_t friend_number, TOX_CONFERENCE_TYPE type, const uint8_t* cookie,
                                  size_t length, void* Core )
{
    qWarning() << "toxConferenceInviteCb";
}

void core::toxConferenceConnectedCb( Tox* tox, uint32_t conference_number, void* Core )
{
    qWarning() << "toxConferenceConnectedCb";
}

void core::toxConferenceMessageCb( Tox* tox, uint32_t conference_number, uint32_t peer_number, TOX_MESSAGE_TYPE type,
                                   const uint8_t* message, size_t length, void* Core )
{
    qWarning() << "toxConferenceMessageCb";
}

void core::toxConferenceTitleCb( Tox* tox, uint32_t conference_number, uint32_t peer_number, const uint8_t* title,
                                 size_t length, void* Core )
{
    qWarning() << "toxConferenceTitleCb";
}

void core::toxConferencePeerNameCb( Tox* tox, uint32_t conference_number, uint32_t peer_number, const uint8_t* name,
                                    size_t length, void* Core )
{
    qWarning() << "toxConferencePeerNameCb";
}

void core::toxConferencePeerListChangedCb( Tox* tox, uint32_t conference_number, void* Core )
{
    qWarning() << "toxConferencePeerListChangedCb";
}

void core::toxFriendLossyPacketCb( Tox* tox, uint32_t friend_number, const uint8_t* data, size_t length,
                                   void* Core )
{
    qWarning() << "toxFriendLossyPacketCb";
}

void core::toxFriendLosslessPacketCb( Tox* tox, uint32_t friend_number, const uint8_t* data, size_t length,
                                      void* Core )
{
    qWarning() << "toxFriendLosslessPacketCb";
}

void core::toxCallbacks()
{
    tox_callback_friend_request( tox, friendRequestCb );
    tox_callback_friend_message( tox, friendMessageCb );
    tox_callback_self_connection_status( tox, selfConnectionStatusCb );
    tox_callback_friend_connection_status( tox, toxFriendConnectionStatusCb );

    //In progress
    tox_callback_friend_name( tox, toxFriendNameCb );
    tox_callback_friend_status_message( tox, toxFriendStatusMessageCb );
    tox_callback_friend_status( tox, toxFriendStatusCb );
    tox_callback_friend_typing( tox, toxFriendTypingCb );
    tox_callback_friend_read_receipt( tox, toxFriendReadReceiptCb );
    tox_callback_file_recv( tox, toxFileRecvCb );
    tox_callback_file_recv_chunk( tox, toxFileRecvChunkCb );
    tox_callback_file_chunk_request( tox, toxFileChunkRequestCb );
    tox_callback_file_recv_control( tox, toxFileRecvControlCb );
    tox_callback_conference_connected( tox, toxConferenceConnectedCb );
    tox_callback_conference_invite( tox, toxConferenceInviteCb );
    tox_callback_conference_message( tox, toxConferenceMessageCb );
    tox_callback_conference_peer_list_changed( tox, toxConferencePeerListChangedCb );
    tox_callback_conference_peer_name( tox, toxConferencePeerNameCb );
    tox_callback_conference_title( tox, toxConferenceTitleCb );
    tox_callback_friend_lossy_packet( tox, toxFriendLossyPacketCb );
    tox_callback_friend_lossless_packet( tox, toxFriendLosslessPacketCb );
}
/******************************************************************************************************
 *												Parse Errors                                          *
 ******************************************************************************************************/

bool core::parseError( Tox_Err_Conference_Title error, int line )
{
    switch ( error ) {
        case TOX_ERR_CONFERENCE_TITLE_OK:
            return true;

        case TOX_ERR_CONFERENCE_TITLE_CONFERENCE_NOT_FOUND:
            qCritical() << line << ": Conference title not found";
            return false;

        case TOX_ERR_CONFERENCE_TITLE_INVALID_LENGTH:
            qCritical() << line << ": Invalid conference title length";
            return false;

        case TOX_ERR_CONFERENCE_TITLE_FAIL_SEND:
            qCritical() << line << ": Failed to send title packet";
            return false;

        default:
            qCritical() << line << ": Unknown Tox_Err_Conference_Title error code:" << error;
            return false;
    }
}

bool core::parseError( Tox_Err_Friend_Send_Message error, int line )
{
    switch ( error ) {
        case TOX_ERR_FRIEND_SEND_MESSAGE_OK:
            return true;

        case TOX_ERR_FRIEND_SEND_MESSAGE_NULL:
            qCritical() << line << "Send friend message passed an unexpected null argument";
            return false;

        case TOX_ERR_FRIEND_SEND_MESSAGE_FRIEND_NOT_FOUND:
            qCritical() << line << "Send friend message could not find friend";
            return false;

        case TOX_ERR_FRIEND_SEND_MESSAGE_FRIEND_NOT_CONNECTED:
            qCritical() << line << "Send friend message: friend is offline";
            return false;

        case TOX_ERR_FRIEND_SEND_MESSAGE_SENDQ:
            qCritical() << line << "Failed to allocate more message queue";
            return false;

        case TOX_ERR_FRIEND_SEND_MESSAGE_TOO_LONG:
            qCritical() << line << "Attemped to send message that's too long";
            return false;

        case TOX_ERR_FRIEND_SEND_MESSAGE_EMPTY:
            qCritical() << line << "Attempted to send an empty message";
            return false;

        default:
            qCritical() << line << "Unknown friend send message error:" << static_cast<int>( error );
            return false;
    }

}

bool core::parseError( Tox_Err_Conference_Send_Message error, int line )
{
    switch ( error ) {
        case TOX_ERR_CONFERENCE_SEND_MESSAGE_OK:
            return true;

        case TOX_ERR_CONFERENCE_SEND_MESSAGE_CONFERENCE_NOT_FOUND:
            qCritical() << line << "Conference not found";
            return false;

        case TOX_ERR_CONFERENCE_SEND_MESSAGE_FAIL_SEND:
            qCritical() << line << "Conference message failed to send";
            return false;

        case TOX_ERR_CONFERENCE_SEND_MESSAGE_NO_CONNECTION:
            qCritical() << line << "No connection";
            return false;

        case TOX_ERR_CONFERENCE_SEND_MESSAGE_TOO_LONG:
            qCritical() << line << "Message too long";
            return false;

        default:
            qCritical() << line << "Unknown Tox_Err_Conference_Send_Message  error:" << static_cast<int>( error );
            return false;
    }

}

bool core::parseError( Tox_Err_Conference_Peer_Query error, int line )
{
    switch ( error ) {
        case TOX_ERR_CONFERENCE_PEER_QUERY_OK:
            return true;

        case TOX_ERR_CONFERENCE_PEER_QUERY_CONFERENCE_NOT_FOUND:
            qCritical() << line << "Conference not found";
            return false;

        case TOX_ERR_CONFERENCE_PEER_QUERY_NO_CONNECTION:
            qCritical() << line << "No connection";
            return false;

        case TOX_ERR_CONFERENCE_PEER_QUERY_PEER_NOT_FOUND:
            qCritical() << line << "Peer not found";
            return false;

        default:
            qCritical() << line << "Unknown Tox_Err_Conference_Peer_Query error code:" << error;
            return false;
    }

}

bool core::parseError( Tox_Err_Conference_Get_Type error, int line )
{
    switch ( error ) {
        case TOX_ERR_CONFERENCE_JOIN_OK:
            return true;

        case TOX_ERR_CONFERENCE_JOIN_DUPLICATE:
            qCritical() << line << "Conference duplicate";
            return false;

        case TOX_ERR_CONFERENCE_JOIN_FAIL_SEND:
            qCritical() << line << "Conference join failed to send";
            return false;

        case TOX_ERR_CONFERENCE_JOIN_FRIEND_NOT_FOUND:
            qCritical() << line << "Friend not found";
            return false;

        case TOX_ERR_CONFERENCE_JOIN_INIT_FAIL:
            qCritical() << line << "Init fail";
            return false;

        case TOX_ERR_CONFERENCE_JOIN_INVALID_LENGTH:
            qCritical() << line << "Invalid length";
            return false;

        case TOX_ERR_CONFERENCE_JOIN_WRONG_TYPE:
            qCritical() << line << "Wrong conference type";
            return false;

        default:
            qCritical() << line << "Unknown Tox_Err_Conference_Join error code:" << error;
            return false;
    }

}

bool core::parseError( Tox_Err_Conference_Invite error, int line )
{
    switch ( error ) {
        case TOX_ERR_CONFERENCE_GET_TYPE_OK:
            return true;

        case TOX_ERR_CONFERENCE_GET_TYPE_CONFERENCE_NOT_FOUND:
            qCritical() << line << "Conference not found";
            return false;

        default:
            qCritical() << line << "Unknown Tox_Err_Conference_Get_Type error code:" << error;
            return false;
    }

}

bool core::parseError( Tox_Err_Conference_New error, int line )
{
    switch ( error ) {
        case TOX_ERR_CONFERENCE_INVITE_OK:
            return true;

        case TOX_ERR_CONFERENCE_INVITE_CONFERENCE_NOT_FOUND:
            qCritical() << line << "Conference not found";
            return false;

        case TOX_ERR_CONFERENCE_INVITE_FAIL_SEND:
            qCritical() << line << "Conference invite failed to send";
            return false;

        case TOX_ERR_CONFERENCE_INVITE_NO_CONNECTION:
            qCritical() << line << "Cannot invite to conference that we're not connected to";
            return false;

        default:
            qWarning() << "Unknown Tox_Err_Conference_Invite error code:" << error;
            return false;
    }

}

bool core::parseError( Tox_Err_Friend_By_Public_Key error, int line )
{
    switch ( error ) {
        case TOX_ERR_CONFERENCE_NEW_OK:
            return true;

        case TOX_ERR_CONFERENCE_NEW_INIT:
            qCritical() << line << "The conference instance failed to initialize";
            return false;

        default:
            qCritical() << line << "Unknown Tox_Err_Conference_New error code:" << error;
            return false;
    }

}

bool core::parseError( Tox_Err_Bootstrap error, int line )
{
    switch ( error ) {
        case TOX_ERR_FRIEND_BY_PUBLIC_KEY_OK:
            return true;

        case TOX_ERR_FRIEND_BY_PUBLIC_KEY_NULL:
            qCritical() << line << "null argument when not expected";
            return false;

        case TOX_ERR_FRIEND_BY_PUBLIC_KEY_NOT_FOUND:
            // we use this as a check for friendship, so this can be an expected result
            return false;

        default:
            qCritical() << line << "Unknown Tox_Err_Friend_By_Public_Key error code:" << error;
            return false;
    }

}

bool core::parseError( Tox_Err_Friend_Add error, int line )
{
    switch ( error ) {
        case TOX_ERR_BOOTSTRAP_OK:
            return true;

        case TOX_ERR_BOOTSTRAP_NULL:
            qCritical() << line << "null argument when not expected";
            return false;

        case TOX_ERR_BOOTSTRAP_BAD_HOST:
            qCritical() << line << "Could not resolve hostname, or invalid IP address";
            return false;

        case TOX_ERR_BOOTSTRAP_BAD_PORT:
            qCritical() << line << "out of range port";
            return false;

        default:
            qCritical() << line << "Unknown Tox_Err_bootstrap error code:" << error;
            return false;
    }

}

bool core::parseError( Tox_Err_Set_Info error, int line )
{
    switch ( error ) {
        case TOX_ERR_FRIEND_ADD_OK:
            return true;

        case TOX_ERR_FRIEND_ADD_NULL:
            qCritical() << line << "null argument when not expected";
            return false;

        case TOX_ERR_FRIEND_ADD_TOO_LONG:
            qCritical() << line << "The length of the friend request message exceeded";
            return false;

        case TOX_ERR_FRIEND_ADD_NO_MESSAGE:
            qCritical() << line << "The friend request message was empty.";
            return false;

        case TOX_ERR_FRIEND_ADD_OWN_KEY:
            qCritical() << line << "The friend address belongs to the sending client.";
            return false;

        case TOX_ERR_FRIEND_ADD_ALREADY_SENT:
            qCritical() << line << "The address belongs to a friend that is already on the friend list.";
            return false;

        case TOX_ERR_FRIEND_ADD_BAD_CHECKSUM:
            qCritical() << line << "The friend address checksum failed.";
            return false;

        case TOX_ERR_FRIEND_ADD_SET_NEW_NOSPAM:
            qCritical() << line << "The address belongs to a friend that is already on the friend list.";
            return false;

        case TOX_ERR_FRIEND_ADD_MALLOC:
            qCritical() << line << "A memory allocation failed when trying to increase the friend list size.";
            return false;

        default:
            qCritical() << line << "Unknown Tox_Err_Friend_Add error code:" << error;
            return false;

    }

}

bool core::parseError( Tox_Err_Friend_Query error, int line )
{
    switch ( error ) {
        case TOX_ERR_FRIEND_DELETE_OK:
            return true;

        case TOX_ERR_FRIEND_DELETE_FRIEND_NOT_FOUND:
            qCritical() << line << "There is no friend with the given friend number";
            return false;

        default:
            qCritical() << line << "Unknown Tox_Err_Friend_Delete error code:" << error;
            return false;
    }

}

bool core::parseError( Tox_Err_Friend_Get_Public_Key error, int line )
{
    switch ( error ) {
        case TOX_ERR_SET_INFO_OK:
            return true;

        case TOX_ERR_SET_INFO_NULL:
            qCritical() << line << "null argument when not expected";
            return false;

        case TOX_ERR_SET_INFO_TOO_LONG:
            qCritical() << line << "Information length exceeded maximum permissible size.";
            return false;

        default:
            qCritical() << line << "Unknown Tox_Err_Set_Info error code:" << error;
            return false;
    }

}

bool core::parseError( Tox_Err_Friend_Get_Last_Online error, int line )
{
    switch ( error ) {
        case TOX_ERR_FRIEND_QUERY_OK:
            return true;

        case TOX_ERR_FRIEND_QUERY_NULL:
            qCritical() << line << "null argument when not expected";
            return false;

        case TOX_ERR_FRIEND_QUERY_FRIEND_NOT_FOUND:
            qCritical() << line << "The friend_number did not designate a valid friend.";
            return false;

        default:
            qCritical() << line << "Unknown Tox_Err_Friend_Query error code:" << error;
            return false;
    }

}

bool core::parseError( Tox_Err_Set_Typing error, int line )
{
    switch ( error ) {
        case TOX_ERR_FRIEND_GET_PUBLIC_KEY_OK:
            return true;

        case TOX_ERR_FRIEND_GET_PUBLIC_KEY_FRIEND_NOT_FOUND:
            qCritical() << line << "There is no friend with the given friend number";
            return false;

        default:
            qCritical() << line << "Unknown Tox_Err_Friend_Get_Public_Key error code:" << error;
            return false;
    }
}

bool core::parseError( Tox_Err_Conference_Delete error, int line )
{
    switch ( error ) {
        case TOX_ERR_FRIEND_GET_LAST_ONLINE_OK:
            return true;

        case TOX_ERR_FRIEND_GET_LAST_ONLINE_FRIEND_NOT_FOUND:
            qCritical() << line << "There is no friend with the given friend number";
            return false;

        default:
            qCritical() << line << "Unknown Tox_Err_Friend_Get_Last_Online error code:" << error;
            return false;
    }
}


