#include "IMCursorManager.hpp"
#include "SFML_GlobalRenderWindow.hpp"

#include <iostream>

IMCursorManager::IMCursorManager()
    : m_cursor_images(NUMBER_OF_TYPES),
      current_type(DEFAULT)
{ }

IMCursorManager::~IMCursorManager()
{
    ClearAllCursors();
}

IMCursorManager& IMCursorManager::getSingleton()
{
    static IMCursorManager singleton;
    return singleton;
}

// Returns false if the given type has no associated image, otherwise sets the new cursor
bool IMCursorManager::SetCursor( const CursorType type )
{
    if ( NULL == m_cursor_images[type] && type > DEFAULT )
        return false;
    else
        return m_cursor_images[type];
}

IMCursorManager::CursorType IMCursorManager::GetCurrentCursor()
{
    return current_type;
}

bool IMCursorManager::ClearCursor( const CursorType type )
{
    if ( NULL == m_cursor_images[type] || type <= SYSTEM )
        return false;
    
    delete m_cursor_images[type];
    m_cursor_images[type] = NULL;
    return true;
}

bool IMCursorManager::ClearAllCursors()
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

void IMCursorManager::DrawCursor()
{
    if (SYSTEM == current_type || (DEFAULT == current_type && NULL == m_cursor_images[DEFAULT]))
    {
        // Use system cursor
        GlobalRenderWindow::GetWindow()->ShowMouseCursor(true);
    }
    else if ( ! (NONE == current_type || NULL == m_cursor_images[current_type]) )
    {
        sf::RenderWindow* renderer = GlobalRenderWindow::GetWindow();
        renderer->ShowMouseCursor(false);
        // Draw!
        sf::Sprite* toDraw( m_cursor_images[current_type] );
        sf::Vector2i mouse_position = sf::Mouse::GetPosition( *(renderer) );
        toDraw->SetOrigin( -mouse_position.x, -mouse_position.y );
        renderer->Draw( *toDraw ); 
    }
}

// These require a specified offset and size value
bool IMCursorManager::CreateCursor( const CursorType type, const sf::Texture* texture, const int offset_x, const int offset_y, const int size_x, const int size_y )
{ 
    if (NULL == texture)
        return false;

    if (type == NONE || type == SYSTEM)
        return false;

    sf::Sprite* cursorSprite = new sf::Sprite();
    cursorSprite->SetPosition( offset_x, offset_y );
    cursorSprite->SetScale( size_x, size_y );
    cursorSprite->SetTexture( *texture );

    LoadSprite( type, cursorSprite );
    return true;
}

bool IMCursorManager::CreateCursor( const CursorType type, const sf::Texture* texture, const sf::Vector2i offset, const sf::Vector2i size )
{
    return CreateCursor( type, texture, offset.x, offset.y, size.x, size.y );
}

bool IMCursorManager::CreateCursor( const CursorType type, const sf::Texture* texture, const sf::Rect<int> offsetAndSize )
{
    return CreateCursor( type, texture, offsetAndSize.Left, offsetAndSize.Top, offsetAndSize.Width, offsetAndSize.Height );
}

// These only require a specified offset and take the size from the Texture
bool IMCursorManager::CreateCursor( const CursorType type, const sf::Texture* texture, const int offset_x, const int offset_y )
{
    if (NULL == texture)
        return false;

    if (type == NONE || type == SYSTEM)
        return false;

    sf::Sprite* cursorSprite = new sf::Sprite( );
    cursorSprite->SetPosition( offset_x, offset_y );
    cursorSprite->SetTexture( *texture, true ); // Auto-scales

    LoadSprite( type, cursorSprite );
    return true;
}

bool IMCursorManager::CreateCursor( const CursorType type, const sf::Texture* texture, const sf::Vector2i offset )
{
    return CreateCursor( type, texture, offset.x, offset.y );
}

bool IMCursorManager::CreateCursor( const CursorType type, const sf::Texture* texture )
{ 
    return CreateCursor( type, texture, 0, 0 );
}

void IMCursorManager::LoadSprite( CursorType type, sf::Sprite* sprite )
{
    sf::Sprite*& old_sprite = m_cursor_images[type];

    if (NULL != old_sprite) // already exists a sprite for this type
        delete old_sprite;

    old_sprite = sprite;
}
