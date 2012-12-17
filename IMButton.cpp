#include "IMButton.hpp"

#include "IMGuiManager.hpp"

#include "SFML/Graphics/Texture.hpp"

#include <iostream>

using namespace sf;

IMButton::IMButton() : normal_look(NULL), hover_look(NULL), pressed_look(NULL)
{
    _x_position = _y_position = 0;
    _x_dimension = _y_dimension = 100;
}

IMButton::IMButton( int x_pos, int y_pos, int x_size, int y_size )
    : normal_look(NULL), hover_look(NULL), pressed_look(NULL)
{ 
    setPosition( x_pos, y_pos );
    setSize( x_size, y_size );
}

IMButton::IMButton( const IMButton& other )
    : normal_look( other.normal_look ),
      hover_look( other.hover_look ),
      pressed_look( other.pressed_look )
{ 
    setPosition( other._x_position, other._y_position );
    setSize( other._x_dimension, other._y_dimension );
}

IMButton& IMButton::operator=( const IMButton& other )
{
    normal_look = other.normal_look;
    hover_look = other.hover_look;
    pressed_look = other.pressed_look;
    setPosition( other._x_position, other._y_position );
    setSize( other._x_dimension, other._y_dimension );
    return *this;
}

IMButton::~IMButton() 
{ }

///////////////////////////////////////////////////////////////////////////
// Overrides from IMGuiWidget:
int IMButton::doWidget() 
{ 
    return doButton( _x_position, _y_position, _x_dimension, _y_dimension );
}


// Moves the widget before doWidget-ing, the values are absolute
int IMButton::doMove( int x_pos, int y_pos, bool keep_new_position ) 
{
    if (keep_new_position) {
        _x_position = x_pos;
        _y_position = y_pos;
    }
    return doButton( x_pos, y_pos, _x_dimension, _y_dimension );
}

// Moves the widget before doWidget-ing, the values are relative
int IMButton::doShift( int x_shift, int y_shift, bool keep_new_position ) 
{
    if (keep_new_position) {
        _x_position += x_shift;
        _y_position += y_shift;
        return doWidget();
    } else {
        return doButton( _x_position + x_shift, _y_position + y_shift, _x_dimension, _y_dimension );
    }
}

// Resizes before Doing
int IMButton::doResize( int x_size, int y_size, bool keep_new_size ) 
{
    if (keep_new_size) {
        _x_dimension = x_size;
        _y_dimension = y_size;
    }
    return doButton( _x_position, _y_position, x_size, y_size );
}

int IMButton::setPosition( int x_pos, int y_pos )
{
    _x_position = x_pos;
    _y_position = y_pos;
    return 0;
}

int IMButton::setSize( int x_dim, int y_dim )
{
    _x_dimension = x_dim;
    _y_dimension = y_dim;
    return 0;
}

///////////////////////////////////////////////////////////////////////////

int IMButton::doButton( int x_pos, int y_pos, int x_size, int y_size )
{
    IMGuiManager::UIState& uistate = IMGuiManager::getSingleton().state;
    sf::Vector2i& mouse_pos = uistate.mouse_pos;

    // cout << "x: " << mouse_pos.x << ", y:" << mouse_pos.y << ", m_down: " << uistate.mouse_down << ", Active:" << uistate.active_widget << ", Hot:" << uistate.hot_widget << std::endl;
    if (uistate.hot_widget == NULL &&
         !(mouse_pos.x < x_pos ||
          mouse_pos.y < y_pos ||
          mouse_pos.x >= x_pos + x_size ||
          mouse_pos.y >= y_pos + y_size)) { // Mouse is over button

        uistate.hot_widget = this;
        if (uistate.active_widget == NULL && uistate.mouse_down) // Mouse clicked on button
            uistate.active_widget = this; 
    }
    // Render

    if (uistate.active_widget == this)
    {
        // Pressed
        Sprite *button = new Sprite( *pressed_look );
        FloatRect frect = button->getGlobalBounds();
        button->setPosition( x_pos, y_pos );
        button->setScale( x_size / frect.width, y_size / frect.height );
        IMGuiManager::getSingleton().pushSprite( button );
    }
    else
    {
        if (uistate.hot_widget == this)
        {
            // Hover
            Sprite *button = new Sprite( *hover_look );
            FloatRect frect = button->getGlobalBounds();
            button->setPosition( x_pos, y_pos );
            button->setScale( x_size / frect.width, y_size / frect.height );
            IMGuiManager::getSingleton().pushSprite( button );
        }
        else
        {
            // Normal
            Sprite *button = new Sprite( *normal_look );
            FloatRect frect = button->getGlobalBounds();
            button->setPosition( x_pos, y_pos );
            button->setScale( x_size / frect.width, y_size / frect.height );
            IMGuiManager::getSingleton().pushSprite( button );
        }
    }

    if (uistate.mouse_down == 0 && uistate.hot_widget == this && uistate.active_widget == this)
        return 1;
    else
        return 0;
}

void IMButton::setNormalTexture( Texture* texture ) 
{
    normal_look = texture;
}

void IMButton::setHoverTexture( Texture* texture ) 
{
    hover_look = texture;
}

void IMButton::setPressedTexture( Texture* texture ) 
{
    pressed_look = texture;
}
