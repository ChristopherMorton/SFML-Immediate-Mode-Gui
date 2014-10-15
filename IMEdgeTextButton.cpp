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
}

void IMEdgeTextButton::setText( std::string *text )
{
    _text = text;
}

void IMEdgeTextButton::setTextOffset( int x_off, int y_off )
{
    _x_text_offset = x_off;
    _y_text_offset = y_off;
}

void IMEdgeTextButton::setTextSize( int pixels )
{
    _char_size = pixels;
}

void IMEdgeTextButton::setTextColor( sf::Color color )
{
    _color = color;
}

int IMEdgeTextButton::centerText()
{
    if (_text && _font) {
        Text t( *_text, *_font, _char_size );
        FloatRect f = t.getLocalBounds();
        _x_text_offset = (_x_dimension - f.width) / 2;

        _y_text_offset = (_y_dimension - _char_size) / 2;
        return 0;
    } else
       return -1;
}

void IMEdgeTextButton::draw( ButtonState state, int x_pos, int y_pos, int x_size, int y_size )
{
    // First the text
    if (_text && _font) {
        Text *text = new Text( *_text, *_font, _char_size );
        text->setPosition( x_pos + _x_text_offset , y_pos + _y_text_offset );
        text->setColor( _color );
        IMGuiManager::getSingleton().pushSprite( text );
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
