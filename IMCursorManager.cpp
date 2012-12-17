#include "IMCursorManager.hpp"
#include "IMGuiManager.hpp"

#include <iostream>

IMCursorManager::IMCursorManager()
    : m_cursor_images(NUMBER_OF_TYPES),
      current_type(DEFAULT)
{ }

IMCursorManager::~IMCursorManager()
{
    clearAllCursors();
}

IMCursorManager& IMCursorManager::getSingleton()
{
    static IMCursorManager singleton;
    return singleton;
}

// Returns false if the given type has no associated image, otherwise sets the new cursor
bool IMCursorManager::setCursor( const CursorType type )
{
    if ( NULL == m_cursor_images[type] && type > DEFAULT )
        return false;
    else
        return m_cursor_images[type];
}

IMCursorManager::CursorType IMCursorManager::getCurrentCursor()
{
    return current_type;
}

bool IMCursorManager::clearCursor( const CursorType type )
{
    if ( NULL == m_cursor_images[type] || type <= SYSTEM )
        return false;
    
    delete m_cursor_images[type];
    m_cursor_images[type] = NULL;
    return true;
}

bool IMCursorManager::clearAllCursors()
{
    vector<sf::Sprite*>::iterator it = m_cursor_images.begin();

    while (it != m_cursor_images.end()) {
        if ( NULL != (*it) ) {
            delete (*it);
            (*it) = NULL;
        }
        ++it;
    }
    return true;
}

void IMCursorManager::drawCursor()
{
    RenderWindow* renderer = IMGuiManager::getSingleton().getRenderWindow();
    if (NULL == renderer) return; // Can't draw on nothing!

    if (SYSTEM == current_type || (DEFAULT == current_type && NULL == m_cursor_images[DEFAULT]))
    {
        // Use system cursor
        renderer->setMouseCursorVisible(true);
    }
    else if ( ! (NONE == current_type || NULL == m_cursor_images[current_type]) )
    {
        // Use custom cursor image
        renderer->setMouseCursorVisible(false);
        // Draw!
        sf::Sprite* toDraw( m_cursor_images[current_type] );
        sf::Vector2i mouse_position = sf::Mouse::getPosition( *(renderer) );
        toDraw->setOrigin( -mouse_position.x, -mouse_position.y );
        renderer->draw( *toDraw ); 
    }
}

// These require a specified offset and size value
bool IMCursorManager::createCursor( const CursorType type, const sf::Texture* texture, const int offset_x, const int offset_y, const int size_x, const int size_y )
{ 
    if (NULL == texture)
        return false;

    if (type == NONE || type == SYSTEM)
        return false;

    sf::Sprite* cursorSprite = new sf::Sprite();
    cursorSprite->setPosition( offset_x, offset_y );
    cursorSprite->setScale( size_x, size_y );
    cursorSprite->setTexture( *texture );

    loadSprite( type, cursorSprite );
    return true;
}

bool IMCursorManager::createCursor( const CursorType type, const sf::Texture* texture, const sf::Vector2i offset, const sf::Vector2i size )
{
    return createCursor( type, texture, offset.x, offset.y, size.x, size.y );
}

bool IMCursorManager::createCursor( const CursorType type, const sf::Texture* texture, const sf::Rect<int> offsetAndSize )
{
    return createCursor( type, texture, offsetAndSize.left, offsetAndSize.top, offsetAndSize.width, offsetAndSize.height );
}

// These only require a specified offset and take the size from the Texture
bool IMCursorManager::createCursor( const CursorType type, const sf::Texture* texture, const int offset_x, const int offset_y )
{
    if (NULL == texture)
        return false;

    if (type == NONE || type == SYSTEM)
        return false;

    sf::Sprite* cursorSprite = new sf::Sprite( );
    cursorSprite->setPosition( offset_x, offset_y );
    cursorSprite->setTexture( *texture, true ); // Auto-scales

    loadSprite( type, cursorSprite );
    return true;
}

bool IMCursorManager::createCursor( const CursorType type, const sf::Texture* texture, const sf::Vector2i offset )
{
    return createCursor( type, texture, offset.x, offset.y );
}

bool IMCursorManager::createCursor( const CursorType type, const sf::Texture* texture )
{ 
    return createCursor( type, texture, 0, 0 );
}

void IMCursorManager::loadSprite( CursorType type, sf::Sprite* sprite )
{
    sf::Sprite*& old_sprite = m_cursor_images[type];

    if (NULL != old_sprite) // already exists a sprite for this type
        delete old_sprite;

    old_sprite = sprite;
}
