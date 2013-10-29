#ifndef IMCURSOR_MANAGER_HPP__
#define IMCURSOR_MANAGER_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>

using namespace std;

class IMCursorManager
{
public:
    enum CursorType
    {
        NONE = 0, // Displays nothing
        SYSTEM, // If this is set as the cursor, sets m_window.ShowMouseCursor(true), (otherwise (false), obviously)
        DEFAULT, // This defaults to SYSTEM if it isn't available.  Also, IMGuiManager sets it to this in begin()

        // The rest default to NONE if not available (only happens if cursor is cleared)
        CLICKING,
        WAITING,
        TARGET,
        LEFT_RIGHT_DRAG,
        UP_DOWN_DRAG,
        NE_SW_DRAG,
        NW_SE_DRAG,
        ALT1,
        ALT2,
        ALT3,
        ALT4,
        NUMBER_OF_TYPES
    };

private:
    IMCursorManager();
    ~IMCursorManager();

    vector<sf::Sprite*> m_cursor_images;

    CursorType current_type;
    
    // Don't need mouse data, can access where the mouse is from sf::Mouse
public:

    static IMCursorManager& getSingleton();

    // Returns false if the given type has no associated image, otherwise sets the new cursor
    bool setCursor( const CursorType type );
    CursorType getCurrentCursor();

    bool clearCursor( const CursorType type );
    bool clearAllCursors();

    void drawCursor();

    /////////////////////////////////////////////////////////////
    // A variety of alternative ways to create the cursor images.
    /////////////////////////////////////////////////////////////
    
    // These require a specified offset and size value
    bool createCursor( const CursorType type, const sf::Texture* texture, 
            const int offset_x, const int offset_y, const int size_x, const int size_y );
    bool createCursor( const CursorType type, const sf::Texture* texture, 
            const sf::Vector2i offset, const sf::Vector2i size );
    bool createCursor( const CursorType type, const sf::Texture* texture, 
            const sf::Rect<int> offsetAndSize );

    // These only require a specified offset and take the size from the Texture
    bool createCursor( const CursorType type, const sf::Texture* texture, const int offset_x, const int offset_y );
    bool createCursor( const CursorType type, const sf::Texture* texture, const sf::Vector2i offset );
    bool createCursor( const CursorType type, const sf::Texture* texture );

private:
    void loadSprite( CursorType type, sf::Sprite* sprite );
};

#endif
