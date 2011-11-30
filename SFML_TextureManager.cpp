#include "SFML_TextureManager.hpp"

#include <SFML/Graphics/Texture.hpp>

SFML_TextureManager::SFML_TextureManager()
{
    path_list.push_back("./"); // Default search directory
}

SFML_TextureManager::~SFML_TextureManager()
{
    ClearAllTextures();
}

SFML_TextureManager& SFML_TextureManager::getSingleton()
{
    static SFML_TextureManager singleton;
    return singleton;
}

void SFML_TextureManager::AddSearchDirectory( string dir )
{ 
    path_list.push_back( dir );
}
    
void SFML_TextureManager::ClearSearchDirectories()
{
    path_list.clear();
    path_list.push_back("./");
}

bool SFML_TextureManager::AddTexture( string path )
{
    Texture* texture = new Texture();
    bool success = false;
    for ( list<string>::iterator it = path_list.begin();
            it != path_list.end();
            ++it )
    {
        // Try to load from this path
        string full_path( *it );
        full_path.append( path );

        if ( texture->LoadFromFile( full_path ) )
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

bool SFML_TextureManager::AddTexture( string internal_path, Texture* texture )
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

Texture* SFML_TextureManager::GetTexture( string path )
{
    map<string, Texture*>::iterator it = texture_map.find( path );
    if ( it != texture_map.end() ) {
        // Found it
        return it->second;
    }
    else
    {
        // Attempt to create it
        if ( AddTexture( path ) )
        {
            return texture_map[path];
        }
        else
        {
            return NULL; // No good
        }
    }
}

bool SFML_TextureManager::ClearTexture( string path )
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

void SFML_TextureManager::ClearAllTextures()
{
    map<string, Texture*>::iterator it = texture_map.begin();
    while ( it != texture_map.end() ) {
        if (it->second != NULL)
            delete (it->second);
        
        ++it;
    }
    texture_map.clear();
} 
