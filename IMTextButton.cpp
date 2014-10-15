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
        Text *text = new Text( *_text, *_font, _char_size );
        text->setPosition( x_pos + _x_text_offset , y_pos + _y_text_offset );
        text->setColor( _color );
        IMGuiManager::getSingleton().pushSprite( text );
    }

    Texture *tex = NULL;
    if (state == BUTTON_NORMAL) tex = normal_look;
    if (state == BUTTON_HOVER) tex = hover_look;
    if (state == BUTTON_PRESSED) tex = pressed_look;

    Sprite *button = new Sprite( *tex );
    FloatRect frect = button->getGlobalBounds();
    button->setPosition( x_pos, y_pos );
    button->setScale( x_size / frect.width, y_size / frect.height );
    IMGuiManager::getSingleton().pushSprite( button );
}

void IMTextButton::setFont( Font *font )
{
    _font = font;
}

void IMTextButton::setText( std::string *text )
{
    _text = text;
}

void IMTextButton::setTextOffset( int x_off, int y_off )
{
    _x_text_offset = x_off;
    _y_text_offset = y_off;
}

void IMTextButton::setTextSize( int pixels )
{
    _char_size = pixels;
}

void IMTextButton::setTextColor( sf::Color color )
{
    _color = color;
}

int IMTextButton::centerText()
{
    if (_text && _font) {
        Text t( *_text, *_font, _char_size );
        FloatRect f = t.getLocalBounds();
        _x_text_offset = (_x_dimension - f.width) / 2;

        _y_text_offset = (_y_dimension - _char_size) / 2;
        return 0;
    } else
       return -1;
}
