#include "IMInstantButton.hpp"

#include "IMGuiManager.hpp"

IMInstantButton::IMInstantButton() : IMButton()
{
}

IMInstantButton::IMInstantButton( int x_pos, int y_pos, int x_size, int y_size )
    : IMButton( x_pos, y_pos, x_size, y_size )
{
}

IMInstantButton::IMInstantButton( const IMButton& other )
    : IMButton( other )
{
}

IMInstantButton& IMInstantButton::operator=( const IMButton& rhs )
{
    IMButton::operator=( rhs );
    return (*this);
}

IMInstantButton::~IMInstantButton()
{ }

int IMInstantButton::doButton( int x_pos, int y_pos, int x_size, int y_size )
{
    IMGuiManager::UIState& uistate = IMGuiManager::getSingleton().state;
    sf::Vector2i& mouse_pos = uistate.mouse_pos;

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
        draw( BUTTON_PRESSED, x_pos, y_pos, x_size, y_size );
    }
    else
    {
        if (uistate.hot_widget == this)
        {
            // Hover
            draw( BUTTON_HOVER, x_pos, y_pos, x_size, y_size );
        }
        else
        {
            // Normal
            draw( BUTTON_NORMAL, x_pos, y_pos, x_size, y_size );
        }
    }

    if (uistate.active_widget == this)  // THE ONLY DIFFERENCE IS HERE
        return 1;
    else
        return 0;
} 
