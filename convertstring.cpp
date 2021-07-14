#include "convertstring.h"

convertString::convertString( const QString& text )
    : convertString( text.toUtf8() )
{
}

convertString::convertString( const QByteArray& text )
    : string( text )
{

}

convertString::convertString( const uint8_t* text, size_t length )
{
    assert( length <= std::numeric_limits<size_t>::max() );
    string = QByteArray( reinterpret_cast<const char*>( text ), length );
}

convertString::convertString( const uint8_t* text, textType type )
{
    std::copy( &text[0], &text[type], std::back_inserter( string ) );
}

convertString::convertString( const uint8_t* data )
{
    std::copy( &data[0], &data[sizeof ( data )], std::back_inserter( string ) );
}

const uint8_t* convertString::data() const
{
    return reinterpret_cast<const uint8_t*>( string.constData() );
}

size_t convertString::size() const
{
    return string.size();
}

QString convertString::getQString() const
{
    return QString::fromUtf8( string );
}

QByteArray convertString::getBytes() const
{
    return QByteArray( string );
}

const uint8_t* convertString::getDataFromQString() const
{
    return reinterpret_cast<const uint8_t*>( QByteArray::fromHex( string ).data() );
}

