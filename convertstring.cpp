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
    assert( length <= INT_MAX );
    string = QByteArray( reinterpret_cast<const char*>( text ), length );
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

