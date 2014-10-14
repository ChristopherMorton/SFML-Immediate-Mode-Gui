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

void makeSprite( Texture *corner, Texture *edge, Texture *center, 
      int x_pos, int y_pos, int x_size, int y_size, int edge_width )
{
    Sprite *c_nw, *c_ne, *c_se, *c_sw, *e_n, *e_e, *e_s, *e_w, *c;
    c_nw = new Sprite( *corner );
    c_ne = new Sprite( *corner );
    c_se = new Sprite( *corner );
    c_sw = new Sprite( *corner );
    e_n = new Sprite( *edge );
    e_e = new Sprite( *edge );
    e_s = new Sprite( *edge );
    e_w = new Sprite( *edge );
    c = new Sprite( *center );

    Vector2i center_dim( x_size - (2 * edge_width), y_size - (2 * edge_width) );

    // Scaling
    FloatRect corner_scale = c_nw->getGlobalBounds();
    corner_scale.width = edge_width / corner_scale.width;
    corner_scale.height = edge_width / corner_scale.height;
    c_nw->setScale( corner_scale.width, corner_scale.height );
    c_ne->setScale( corner_scale.width, corner_scale.height );
    c_se->setScale( corner_scale.width, corner_scale.height );
    c_sw->setScale( corner_scale.width, corner_scale.height );

    FloatRect edge_scale = e_n->getGlobalBounds();
    edge_scale.height = edge_width / edge_scale.height;
    e_n->setScale( center_dim.x / edge_scale.width, edge_scale.height );
    e_s->setScale( center_dim.x / edge_scale.width, edge_scale.height );
    e_e->setScale( center_dim.y / edge_scale.width, edge_scale.height );
    e_w->setScale( center_dim.y / edge_scale.width, edge_scale.height );

    FloatRect c_scale = c->getGlobalBounds();
    c->setScale( center_dim.x / c_scale.width, center_dim.y / c_scale.height );

    // Rotation
    c_ne->setRotation( 90 );
    c_se->setRotation( 180 );
    c_sw->setRotation( 270 );

    e_e->setRotation( 90 );
    e_s->setRotation( 180 );
    e_w->setRotation( 270 );

    // Positioning
    c_nw->setPosition( x_pos, y_pos );
    c_ne->setPosition( x_pos + x_size, y_pos );
    c_se->setPosition( x_pos + x_size, y_pos + y_size );
    c_sw->setPosition( x_pos, y_pos + y_size );

    e_n->setPosition( x_pos + edge_width, y_pos );
    e_e->setPosition( x_pos + x_size, y_pos + edge_width );
    e_s->setPosition( x_pos + x_size - edge_width, y_pos + y_size );
    e_w->setPosition( x_pos, y_pos + y_size - edge_width );

    c->setPosition( x_pos + edge_width, y_pos + edge_width );

    // Draw

    IMGuiManager &manager = IMGuiManager::getSingleton();

    manager.pushSprite( c_nw );
    manager.pushSprite( c_ne );
    manager.pushSprite( c_se );
    manager.pushSprite( c_sw );
    manager.pushSprite( e_n );
    manager.pushSprite( e_e );
    manager.pushSprite( e_s );
    manager.pushSprite( e_w );
    manager.pushSprite( c );
}

int IMEdgeButton::doButton( int x_pos, int y_pos, int x_size, int y_size )
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
        makeSprite( corner_pressed_texture, edge_pressed_texture, pressed_look,
              x_pos, y_pos, x_size, y_size, edge_width );
    }
    else
    {
        if (uistate.hot_widget == this)
        {
            // Hover
            makeSprite( corner_hover_texture, edge_hover_texture, hover_look,
                  x_pos, y_pos, x_size, y_size, edge_width );
        }
        else
        {
            // Normal
            makeSprite( corner_normal_texture, edge_normal_texture, normal_look,
                  x_pos, y_pos, x_size, y_size, edge_width );
        }
    }

    if (uistate.mouse_down == 0 && uistate.hot_widget == this && uistate.active_widget == this)
        return 1;
    else
        return 0;

}
