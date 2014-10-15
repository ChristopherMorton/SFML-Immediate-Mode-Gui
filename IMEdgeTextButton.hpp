#ifndef IMGUI_IMEDGETEXTBUTTON_HPP__
#define IMGUI_IMEDGETEXTBUTTON_HPP__

/* An IMEdgeTextButton has a corner and an edge texture as well
 * as a center button texture. The corners and edges are drawn
 * with a consistent width/resolution regardless of changes
 * to the size of the button as a whole.
 *
 * It also has a text string that is displayed in the chosen
 * font and size at some location within the button, while the
 * normal/hover/pressed image changes behind it.
 */

#include "IMEdgeButton.hpp"
#include "IMTextButton.hpp"
#include "SFML/Graphics.hpp"

namespace sf { 
    class Texture; 
    class Font;
};

class IMEdgeTextButton : public IMEdgeButton
{
public:
    IMEdgeTextButton();
    IMEdgeTextButton( int x_pos, int y_pos, int x_size, int y_size );

    IMEdgeTextButton( const IMButton& other );
    IMEdgeTextButton& operator=( const IMButton& rhs );

    virtual ~IMEdgeTextButton();

// Text functionality
    void setFont( Font *font );
    void setText( std::string *text );
    void setTextOffset( int x_off, int y_off );
    void setTextSize( int pixels );
    void setTextColor( sf::Color color );
    int centerText();

// Combined functionality
    virtual void draw( ButtonState state, int x_pos, int y_pos, int x_size, int y_size );

protected:
    std::string *_text;
    sf::Font *_font;
    sf::Color _color;
    int _x_text_offset, _y_text_offset;
    int _char_size;
};
#endif
