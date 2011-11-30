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
    SetPosition( x_pos, y_pos );
    SetSize( x_size, y_size );
}

IMButton::IMButton( const IMButton& other )
    : normal_look( other.normal_look ),
      hover_look( other.hover_look ),
      pressed_look( other.pressed_look )
{ 
    SetPosition( other._x_position, other._y_position );
    SetSize( other._x_dimension, other._y_dimension );
}

IMButton& IMButton::operator=( const IMButton& other )
{
    normal_look = other.normal_look;
    hover_look = other.hover_look;
    pressed_look = other.pressed_look;
    SetPosition( other._x_position, other._y_position );
    SetSize( other._x_dimension, other._y_dimension );
    return *this;
}

IMButton::~IMButton() 
{ }

///////////////////////////////////////////////////////////////////////////
// Overrides from IMGuiWidget:
int IMButton::Do() 
{ 
    return DoButton( _x_position, _y_position, _x_dimension, _y_dimension );
}


// Moves the widget before Do-ing, the values are absolute
int IMButton::DoMove( int x_pos, int y_pos, bool keep_new_position ) 
{
    if (keep_new_position) {
        _x_position = x_pos;
        _y_position = y_pos;
        return Do();
    } else {
        return DoButton( x_pos, y_pos, _x_dimension, _y_dimension );
    }
}

// Moves the widget before Do-ing, the values are relative
int IMButton::DoShift( int x_shift, int y_shift, bool keep_new_position ) 
{
    if (keep_new_position) {
        _x_position += x_shift;
        _y_position += y_shift;
        return Do();
    } else {
        return DoButton( _x_position + x_shift, _y_position + y_shift, _x_dimension, _y_dimension );
    }
}

// Resizes before Doing
int IMButton::DoResize( int x_size, int y_size, bool keep_new_size ) 
{
    if (keep_new_size) {
        _x_dimension = x_size;
        _y_dimension = y_size;
        return Do();
    } else {
        return DoButton( _x_position, _y_position, x_size, y_size );
    }
}

int IMButton::SetPosition( int x_pos, int y_pos )
{
    _x_position = x_pos;
    _y_position = y_pos;
    return 0;
}

int IMButton::SetSize( int x_dim, int y_dim )
{
    _x_dimension = x_dim;
    _y_dimension = y_dim;
    return 0;
}

///////////////////////////////////////////////////////////////////////////

int IMButton::DoButton( int x_pos, int y_pos, int x_size, int y_size )
{
    IMGuiManager::UIState& uistate = IMGuiManager::getSingleton().state;
    sf::Vector2i& mouse_pos = uistate.mouse_pos;
    //cout << "DO: mousex=" << mouse_pos.x << " mousey=" << mouse_pos.y << endl;
    if (uistate.hot_widget == NULL &&
         !(mouse_pos.x < x_pos ||
          mouse_pos.y < y_pos ||
          mouse_pos.x >= x_pos + x_size ||
          mouse_pos.y >= y_pos + y_size)) { // Mouse is over button

        uistate.hot_widget = this;
        if (uistate.active_widget == NULL && uistate.mouse_down)
            uistate.active_widget = this; 
    }
    // Render

    if (uistate.active_widget == this)
    {
        // Pressed
        Sprite *button = new Sprite( *pressed_look );
        button->SetPosition( x_pos, y_pos );
        button->Resize( x_size, y_size );
        IMGuiManager::getSingleton().PushSprite( button );
    }
    else
    {
        if (uistate.hot_widget == this)
        {
            // Hover
            Sprite *button = new Sprite( *hover_look );
            button->SetPosition( x_pos, y_pos );
            button->Resize( x_size, y_size );
            IMGuiManager::getSingleton().PushSprite( button );
        }
        else
        {
            // Normal
            Sprite *button = new Sprite( *normal_look );
            button->SetPosition( x_pos, y_pos );
            button->Resize( x_size, y_size );
            IMGuiManager::getSingleton().PushSprite( button );
        }
    }

    if (uistate.mouse_down == 0 && uistate.hot_widget == this && uistate.active_widget == this)
        return 1;
    else
        return 0;
}

void IMButton::SetNormalTexture( Texture* texture ) 
{
    normal_look = texture;
}

void IMButton::SetHoverTexture( Texture* texture ) 
{
    hover_look = texture;
}

void IMButton::SetPressedTexture( Texture* texture ) 
{
    pressed_look = texture;
}
