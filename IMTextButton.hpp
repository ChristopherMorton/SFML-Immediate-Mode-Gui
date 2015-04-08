#ifndef IMGUI_IMTEXTBUTTON_HPP__
#define IMGUI_IMTEXTBUTTON_HPP__

/* An IMTextButton has a text string that is displayed in the chosen
 * font and size at some location within the button, while the
 * normal/hover/pressed image changes behind it.
 */

#include "IMButton.hpp"
#include "SFML/Graphics.hpp"

#include <string>

namespace sf { 
    class Texture; 
    class Font;
};

class IMTextButton : public IMButton
{
public:
    IMTextButton();
    IMTextButton( int x_pos, int y_pos, int x_size, int y_size );

    IMTextButton( const IMButton& other );
    IMTextButton& operator=( const IMButton& rhs );

    virtual ~IMTextButton();

    virtual void draw( ButtonState state, int x_pos, int y_pos, int x_size, int y_size );

// New functionality
    void setFont( Font *font );
    void setText( std::string *text );
    void setTextOffset( int x_off, int y_off );
    void setTextSize( int pixels );
    void setTextColor( sf::Color color );
    int centerText();

protected:
    std::string *_text;
    sf::Font *_font;
    sf::Color _color;
    int _x_text_offset, _y_text_offset;
    int _char_size;
    sf::Text sftext;
};
#endif

