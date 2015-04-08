#include "IMEdgeButton.hpp"

#include "IMGuiManager.hpp"

IMEdgeButton::IMEdgeButton() : IMButton()
{
}

IMEdgeButton::IMEdgeButton( int x_pos, int y_pos, int x_size, int y_size )
    : IMButton( x_pos, y_pos, x_size, y_size ),
      corner_normal_texture(NULL),
      corner_hover_texture(NULL),
      corner_pressed_texture(NULL),
      edge_normal_texture(NULL),
      edge_hover_texture(NULL),
      edge_pressed_texture(NULL),
      edge_width(0)
{
}

IMEdgeButton::IMEdgeButton( const IMButton& other )
    : IMButton( other ),
      corner_normal_texture(NULL),
      corner_hover_texture(NULL),
      corner_pressed_texture(NULL),
      edge_normal_texture(NULL),
      edge_hover_texture(NULL),
      edge_pressed_texture(NULL),
      edge_width(0)
{
}

IMEdgeButton& IMEdgeButton::operator=( const IMButton& rhs )
{
    IMButton::operator=( rhs );
    corner_normal_texture = NULL;
    corner_hover_texture = NULL;
    corner_pressed_texture = NULL;
    edge_normal_texture = NULL;
    edge_hover_texture = NULL;
    edge_pressed_texture = NULL;
    edge_width = 0;
    return (*this);
}

IMEdgeButton::~IMEdgeButton()
{ }

void IMEdgeButton::setCornerNormalTexture( Texture *texture )
{
    corner_normal_texture = texture;
}

void IMEdgeButton::setCornerHoverTexture( Texture *texture )
{
    corner_hover_texture = texture;
}

void IMEdgeButton::setCornerPressedTexture( Texture *texture )
{
    corner_pressed_texture = texture;
}

void IMEdgeButton::setCornerAllTextures( Texture *texture )
{
    setCornerNormalTexture( texture );
    setCornerHoverTexture( texture );
    setCornerPressedTexture( texture ); 
}

void IMEdgeButton::setEdgeNormalTexture( Texture *texture )
{
    edge_normal_texture = texture;
}

void IMEdgeButton::setEdgeHoverTexture( Texture *texture )
{
    edge_hover_texture = texture;
}

void IMEdgeButton::setEdgePressedTexture( Texture *texture )
{
    edge_pressed_texture = texture;
}

void IMEdgeButton::setEdgeAllTextures( Texture *texture )
{
    setEdgeNormalTexture( texture );
    setEdgeHoverTexture( texture );
    setEdgePressedTexture( texture );
}

void IMEdgeButton::setEdgeWidth( int pixels )
{
    if (pixels < 0) pixels = 0;
    edge_width = pixels;
}

void IMEdgeButton::draw( ButtonState state, int x_pos, int y_pos, int x_size, int y_size )
{
    Texture *corner = NULL, *edge = NULL, *center = NULL;
    if ( state == BUTTON_NORMAL) {
       corner = corner_normal_texture;
       edge = edge_normal_texture;
       center = normal_look;
    } else if ( state == BUTTON_HOVER ) {
       corner = corner_hover_texture; 
       edge = edge_hover_texture;
       center = hover_look;
    } else if ( state == BUTTON_PRESSED ) {
       corner = corner_pressed_texture;
       edge = edge_pressed_texture;
       center = pressed_look;
    }

    sp_corner_nw.setTexture( *corner );
    sp_corner_ne.setTexture( *corner );
    sp_corner_se.setTexture( *corner );
    sp_corner_sw.setTexture( *corner );
    sp_edge_n.setTexture( *edge );
    sp_edge_e.setTexture( *edge );
    sp_edge_s.setTexture( *edge );
    sp_edge_w.setTexture( *edge );
    sp_center.setTexture( *center );

    Vector2i center_dim( x_size - (2 * edge_width), y_size - (2 * edge_width) );

    // Scaling
    float scale_x, scale_y;
    Vector2u scale_2u = corner->getSize();
    scale_x = edge_width / (float)scale_2u.x;
    scale_y = edge_width / (float)scale_2u.y;
    sp_corner_nw.setScale( scale_x, scale_y );
    sp_corner_ne.setScale( scale_x, scale_y );
    sp_corner_se.setScale( scale_x, scale_y );
    sp_corner_sw.setScale( scale_x, scale_y );

    scale_2u = edge->getSize();
    scale_x = scale_2u.x;
    scale_y = edge_width / (float)scale_2u.y;
    sp_edge_n.setScale( center_dim.x / scale_x, scale_y );
    sp_edge_s.setScale( center_dim.x / scale_x, scale_y );
    sp_edge_e.setScale( center_dim.y / scale_x, scale_y );
    sp_edge_w.setScale( center_dim.y / scale_x, scale_y );

    scale_2u = center->getSize();
    sp_center.setScale( center_dim.x / (float)scale_2u.x, center_dim.y / (float)scale_2u.y );

    // Rotation
    sp_corner_ne.setRotation( 90 );
    sp_corner_se.setRotation( 180 );
    sp_corner_sw.setRotation( 270 );

    sp_edge_e.setRotation( 90 );
    sp_edge_s.setRotation( 180 );
    sp_edge_w.setRotation( 270 );

    // Positioning
    sp_corner_nw.setPosition( x_pos, y_pos );
    sp_corner_ne.setPosition( x_pos + x_size, y_pos );
    sp_corner_se.setPosition( x_pos + x_size, y_pos + y_size );
    sp_corner_sw.setPosition( x_pos, y_pos + y_size );

    sp_edge_n.setPosition( x_pos + edge_width, y_pos );
    sp_edge_e.setPosition( x_pos + x_size, y_pos + edge_width );
    sp_edge_s.setPosition( x_pos + x_size - edge_width, y_pos + y_size );
    sp_edge_w.setPosition( x_pos, y_pos + y_size - edge_width );

    sp_center.setPosition( x_pos + edge_width, y_pos + edge_width );

    // Draw

    IMGuiManager &manager = IMGuiManager::getSingleton();

    manager.pushSprite( &sp_corner_nw );
    manager.pushSprite( &sp_corner_ne );
    manager.pushSprite( &sp_corner_se );
    manager.pushSprite( &sp_corner_sw );
    manager.pushSprite( &sp_edge_n );
    manager.pushSprite( &sp_edge_e );
    manager.pushSprite( &sp_edge_s );
    manager.pushSprite( &sp_edge_w );
    manager.pushSprite( &sp_center );
}
