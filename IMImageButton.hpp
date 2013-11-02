#ifndef IMGUI_IMAGEBUTTON_HPP__
#define IMGUI_IMAGEBUTTON_HPP__

/* An IMImageButton has an additional image that is always displayed
 * at some location within the button, while the normal/hover/pressed
 * image changes behind it.  This is for interfaces that use the same
 * button type but need to specialize the appearance. 
 */

#include "IMButton.hpp"

namespace sf { 
    class Texture; 
};

class IMImageButton : public IMButton
{
public:
    IMImageButton();
    IMImageButton( int x_pos, int y_pos, int x_size, int y_size );

    IMImageButton( const IMButton& other );
    IMImageButton& operator=( const IMButton& rhs );

    virtual ~IMImageButton();

    virtual int doButton( int x_pos, int y_pos, int x_size, int y_size );

// New functionality
    void setImage( sf::Texture *texture );
    int setImageSize( int x_size, int y_size ); // Fails if there is no texture
    void setImageOffset( int x_off, int y_off );

protected:
    sf::Texture* image_texture;
    int _x_image_offset, _y_image_offset;
    float _x_image_scale, _y_image_scale;
};
#endif

