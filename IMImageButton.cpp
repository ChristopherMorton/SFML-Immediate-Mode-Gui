#include "IMImageButton.hpp"

#include "IMGuiManager.hpp"

IMImageButton::IMImageButton() : IMButton()
{
}

IMImageButton::IMImageButton( int x_pos, int y_pos, int x_size, int y_size )
    : IMButton( x_pos, y_pos, x_size, y_size ),
      image_texture(NULL),
      _x_image_offset(0),
      _y_image_offset(0),
      _x_image_scale(1.0),
      _y_image_scale(1.0)
{
}

IMImageButton::IMImageButton( const IMButton& other )
    : IMButton( other ),
      image_texture(NULL),
      _x_image_offset(0),
      _y_image_offset(0),
      _x_image_scale(1.0),
      _y_image_scale(1.0)
{
}

IMImageButton& IMImageButton::operator=( const IMButton& rhs )
{
    IMButton::operator=( rhs );
    image_texture = NULL;
    _x_image_offset = 0;
    _y_image_offset = 0;
    _x_image_scale = 1.0;
    _y_image_scale = 1.0;
    return (*this);
}

IMImageButton::~IMImageButton()
{ }

int IMImageButton::doButton( int x_pos, int y_pos, int x_size, int y_size )
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

    // Draw the image first (on top)
    if (image_texture) {
       Sprite *image = new Sprite( *image_texture );
       image->setPosition( x_pos + _x_image_offset , y_pos + _y_image_offset );
       image->setScale( _x_image_scale, _y_image_scale );
       IMGuiManager::getSingleton().pushSprite( image );
    }

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

void IMImageButton::setImage( Texture *texture )
{
    image_texture = texture;
}

void IMImageButton::setImageOffset( int x_off, int y_off )
{
    _x_image_offset = x_off;
    _y_image_offset = y_off;
}

int IMImageButton::setImageSize( int x_size, int y_size )
{
   if (image_texture) {
      Vector2u t_size = image_texture->getSize();

      _x_image_scale = ((float)x_size) / t_size.x;
      _y_image_scale = ((float)y_size) / t_size.y;
      return 0;
   }
   return -1;
}
