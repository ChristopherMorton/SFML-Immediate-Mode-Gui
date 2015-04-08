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

void IMImageButton::draw( ButtonState state, int x_pos, int y_pos, int x_size, int y_size )
{
    if (image_texture) {
        sp_image.setPosition( x_pos + _x_image_offset , y_pos + _y_image_offset );
        sp_image.setScale( _x_image_scale, _y_image_scale );
        IMGuiManager::getSingleton().pushSprite( &sp_image );
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

void IMImageButton::setImage( Texture *texture )
{
    image_texture = texture;
    if (texture) sp_image.setTexture( *texture );
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
