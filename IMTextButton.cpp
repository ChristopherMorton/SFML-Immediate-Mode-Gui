#include "IMTextButton.hpp"

#include "IMGuiManager.hpp"

using namespace std;
using namespace sf;

IMTextButton::IMTextButton() : IMButton(),
      _text(NULL),
      _font(NULL)
{
}

IMTextButton::IMTextButton( int x_pos, int y_pos, int x_size, int y_size )
    : IMButton( x_pos, y_pos, x_size, y_size ),
      _text(NULL),
      _font(NULL),
      _x_text_offset(0),
      _y_text_offset(0)
{
}

IMTextButton::IMTextButton( const IMButton& other )
    : IMButton( other ),
      _text(NULL),
      _font(NULL),
      _x_text_offset(0),
      _y_text_offset(0)
{
}

IMTextButton& IMTextButton::operator=( const IMButton& rhs )
{
    IMButton::operator=( rhs );
    _text = NULL;
    _font = NULL;
    _x_text_offset = 0;
    _y_text_offset = 0;
    return (*this);
}

IMTextButton::~IMTextButton()
{ }

void IMTextButton::draw( ButtonState state, int x_pos, int y_pos, int x_size, int y_size )
{
    if (_text && _font) {
        sftext.setPosition( x_pos + _x_text_offset , y_pos + _y_text_offset );
        IMGuiManager::getSingleton().pushSprite( &sftext );
    }

    Texture *tex = NULL;
    if (state == BUTTON_NORMAL) tex = normal_look;
    if (state == BUTTON_HOVER) tex = hover_look;
    if (state == BUTTON_PRESSED) tex = pressed_look;

    if (!tex) return;

    sp_button.setTexture( *tex );
    Vector2u dim = tex->getSize();
    sp_button.setPosition( x_pos, y_pos );
    sp_button.setScale( x_size / (float)dim.x, y_size / (float)dim.y );
    IMGuiManager::getSingleton().pushSprite( &sp_button );
}

void IMTextButton::setFont( Font *font )
{
    _font = font;
    sftext.setFont( *_font );
}

void IMTextButton::setText( std::string *text )
{
    _text = text;
    sftext.setString( *_text );
}

void IMTextButton::setTextOffset( int x_off, int y_off )
{
    _x_text_offset = x_off;
    _y_text_offset = y_off;
}

void IMTextButton::setTextSize( int pixels )
{
    _char_size = pixels;
    sftext.setCharacterSize( _char_size );
}

void IMTextButton::setTextColor( sf::Color color )
{
    _color = color;
    sftext.setColor( _color );
}

int IMTextButton::centerText()
{
    if (_text && _font) {
        Text t( *_text, *_font, _char_size );
        FloatRect f = t.getLocalBounds();

        _x_text_offset = (_x_dimension - f.width) / 2;
        _y_text_offset = (_y_dimension - (_char_size * 5 / 4)) / 2;

        return 0;
    } else
       return -1;
}
