#ifndef IMGUI_IMEDGEBUTTON_HPP__
#define IMGUI_IMEDGEBUTTON_HPP__

/* An IMEdgeButton has a corner and an edge texture as well
 * as a center button texture. The corners and edges are drawn
 * with a consistent width/resolution regardless of changes
 * to the size of the button as a whole.
 */

#include "IMButton.hpp"
#include "SFML/Graphics.hpp"

namespace sf { 
    class Texture; 
    class Font;
};

class IMEdgeButton : public IMButton
{
public:
    IMEdgeButton();
    IMEdgeButton( int x_pos, int y_pos, int x_size, int y_size );

    IMEdgeButton( const IMButton& other );
    IMEdgeButton& operator=( const IMButton& rhs );

    virtual ~IMEdgeButton();

// New functionality
    void setCornerNormalTexture( Texture *texture );
    void setCornerHoverTexture( Texture *texture );
    void setCornerPressedTexture( Texture *texture );
    void setCornerAllTextures( Texture *texture );
    void setEdgeNormalTexture( Texture *texture );
    void setEdgeHoverTexture( Texture *texture );
    void setEdgePressedTexture( Texture *texture );
    void setEdgeAllTextures( Texture *texture );

    void setEdgeWidth( int pixels );

    virtual void draw( ButtonState state, int x_pos, int y_pos, int x_size, int y_size );

protected:
    Texture *corner_normal_texture, *corner_hover_texture, *corner_pressed_texture;
    Texture *edge_normal_texture, *edge_hover_texture, *edge_pressed_texture;
    int edge_width;
};
#endif
