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

    if (uistate.active_widget == this)  // THE ONLY DIFFERENCE IS HERE
        return 1;
    else
        return 0;
} 
