#ifndef IMGUI_BUTTON_HPP__
#define IMGUI_BUTTON_HPP__

#include "IMGuiWidget.hpp"
#include <SFML/Graphics.hpp>

namespace sf { 
    class Texture;
    class Sprite;
};

using namespace sf;

enum ButtonState {
   BUTTON_NORMAL,
   BUTTON_HOVER,
   BUTTON_PRESSED
};

class IMButton : public IMGuiWidget
{
protected:
    Texture *normal_look, *hover_look, *pressed_look;
    Sprite sp_button;

public:
    IMButton();
    IMButton( int x_pos, int y_pos, int x_size, int y_size );

    IMButton( const IMButton& other );
    IMButton& operator=( const IMButton& rhs );

    // NOTE: This DOES NOT delete the look Textures, they should be handled elsewhere
    virtual ~IMButton();

    ///////////////////////////////////////////////////////////////////////////
    // Overrides from IMGuiWidget:
    virtual int doWidget();

    // Moves the widget before Do-ing, the values are absolute
    virtual int doMove( int x_pos, int y_pos, bool keep_new_position );
    // Moves the widget before Do-ing, the values are relative
    virtual int doShift( int x_shift, int y_shift, bool keep_new_position );
    // Resizes before Doing
    virtual int doResize( int x_size, int y_size, bool keep_new_size );

    virtual int setPosition( int x_pos, int y_pos );
    virtual int setSize( int x_dim, int y_dim );
    ///////////////////////////////////////////////////////////////////////////
    virtual int doButton( int x_pos, int y_pos, int x_size, int y_size );
    virtual void draw( ButtonState state, int x_pos, int y_pos, int x_size, int y_size );

    void setNormalTexture( Texture *texture );
    void setHoverTexture( Texture *texture );
    void setPressedTexture( Texture *texture );
    void setAllTextures( Texture *texture );
};

#endif
