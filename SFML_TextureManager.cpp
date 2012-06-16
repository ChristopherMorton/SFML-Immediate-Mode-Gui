#include "SFML_TextureManager.hpp"

#include <SFML/Graphics/Texture.hpp>

SFML_TextureManager::SFML_TextureManager()
{
    path_list.push_back("./"); // Default search directory
}

SFML_TextureManager::~SFML_TextureManager()
{
    clearAllTextures();
}

SFML_TextureManager& SFML_TextureManager::getSingleton()
{
    static SFML_TextureManager singleton;
    return singleton;
}

void SFML_TextureManager::addSearchDirectory( string dir )
{ 
    path_list.push_front( dir );
}
    
void SFML_TextureManager::clearSearchDirectories()
{
    path_list.clear();
    path_list.push_back("./");
}

bool SFML_TextureManager::addTexture( string path )
{
    Texture* texture = new Texture();
    bool success = false;
    for ( deque<string>::iterator it = path_list.begin();
            it != path_list.end();
            ++it )
    {
        // Try to load from this path
        string full_path( *it );
        full_path.append( path );

        if ( texture->loadFromFile( full_path ) )
        {
            // Success!
            success = true;
            break; 
        }
    }

    if (success)
    {
        // If there's already a texture for this string, we delete it
        map<string, Texture*>::iterator it = texture_map.find( path );
        if (it != texture_map.end())
        {
            if (it->second != NULL)
                delete (it->second);
        }

        texture_map[path] = texture;
        return true;
    }
    else
    { 
        // Couldn't create
        delete texture;
        return false;
    }
}

bool SFML_TextureManager::addTexture( string internal_path, Texture* texture )
{
    if (texture == NULL) {
        return false;
    }
    else
    {
        // If there's already a texture for this string, we delete it
        map<string, Texture*>::iterator it = texture_map.find( internal_path );
        if (it != texture_map.end())
        {
            if (it->second != NULL)
                delete (it->second);
        }

        texture_map[internal_path] = texture;
        return true;
    }
}

Texture* SFML_TextureManager::getTexture( string path )
{
    map<string, Texture*>::iterator it = texture_map.find( path );
    if ( it != texture_map.end() ) {
        // Found it
        return it->second;
    }
    else
    {
        // Attempt to create it
        if ( addTexture( path ) )
        {
            return texture_map[path];
        }
        else
        {
            return NULL; // No good
        }
    }
}

bool SFML_TextureManager::clearTexture( string path )
{
    map<string, Texture*>::iterator it = texture_map.find( path );
    if ( it != texture_map.end() ) {
        // Texture exists, clear it
        if (it->second != NULL)
            delete (it->second);
        texture_map.erase(it);
        return true;
    }
    return false;
}

void SFML_TextureManager::clearAllTextures()
{
    map<string, Texture*>::iterator it = texture_map.begin();
    while ( it != texture_map.end() ) {
        if (it->second != NULL)
            delete (it->second);
        
        ++it;
    }
    texture_map.clear();
} 
