#include "IMEdgeTextButton.hpp"

#include "IMGuiManager.hpp"

IMEdgeTextButton::IMEdgeTextButton() : IMEdgeButton()
{
}

IMEdgeTextButton::IMEdgeTextButton( int x_pos, int y_pos, int x_size, int y_size )
    : IMEdgeButton( x_pos, y_pos, x_size, y_size ),
      _text(NULL),
      _font(NULL),
      _x_text_offset(0),
      _y_text_offset(0)
{
}

IMEdgeTextButton::IMEdgeTextButton( const IMButton& other )
    : IMEdgeButton( other ),
      _text(NULL),
      _font(NULL),
      _x_text_offset(0),
      _y_text_offset(0)
{
}

IMEdgeTextButton& IMEdgeTextButton::operator=( const IMButton& rhs )
{
    IMEdgeButton::operator=( rhs );
    _text = NULL;
    _font = NULL;
    _x_text_offset = 0;
    _y_text_offset = 0;
    return (*this);
}

IMEdgeTextButton::~IMEdgeTextButton()
{ }

void IMEdgeTextButton::setFont( Font *font )
{
    _font = font;
    sftext.setFont( *_font );
}

void IMEdgeTextButton::setText( std::string *text )
{
    _text = text;
    sftext.setString( *_text );
}

void IMEdgeTextButton::setTextOffset( int x_off, int y_off )
{
    _x_text_offset = x_off;
    _y_text_offset = y_off;
}

void IMEdgeTextButton::setTextSize( int pixels )
{
    _char_size = pixels;
    sftext.setCharacterSize( _char_size );
}

void IMEdgeTextButton::setTextColor( sf::Color color )
{
    _color = color;
    sftext.setColor( _color );
}

int IMEdgeTextButton::centerText()
{ 
    if (_text && _font) {
        Text t( *_text, *_font, _char_size );
        FloatRect f = t.getLocalBounds();
        _x_text_offset = (_x_dimension - f.width) / 2;
        _y_text_offset = (_y_dimension - (_char_size * 5 / 4)) / 2;

        return 0;
    } else
       return -1;
}

void IMEdgeTextButton::draw( ButtonState state, int x_pos, int y_pos, int x_size, int y_size )
{
    // First the text
    if (_text && _font) {
        sftext.setPosition( x_pos + _x_text_offset , y_pos + _y_text_offset );
        IMGuiManager::getSingleton().pushSprite( &sftext );
    }

    // Second the edge button
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

    if (!corner || !edge || !center) return;

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
