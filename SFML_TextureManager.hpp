#ifndef SFML_TEXTUREMANAGER_HPP__
#define SFML_TEXTUREMANAGER_HPP__

/*
 * The purpose of this manager is to create needed textures at load time and
 * then make them accessible at run time, while avoiding duplication of resources.
 *
 * To use:
 * First, use addSearchDirectory( string dir ) for any directories other than ./
 * from which resources will need to be loaded.  This can be skipped if you're
 * dead sure where each resource will be, in which case you should fully qualify
 * each path name, but doing it this way adds very little overhead and makes
 * your code much more flexible.
 * Add these in the order you expect them to be searched.
 *
 * Second, call addTexture( string path ), or getTexture( ... ) which will call
 * addTexture if the texture isn't there.  Do this for any textures you will need
 * during run time, BEFORE run time comes around, to avoid slowdown.
 *
 * Alternatively, call addTexture( string internal_path, Texture* texture ) to add
 * textures that were generated programatically.
 *
 * Third, when a Texture is needed, call getTexture( string path ) to retrieve it.
 *
 * That is all the steps.  Textures will be deleted at program end
 * (when the SFML_TextureManager singleton is deleted),
 * or they can be cleared with clearAllTextures() or clearTexture( string path )
 * if you want to cut down on memory usage.
 */

#include <map>
#include <deque>
#include <string>

// Forward declarations
namespace sf { 
    class Texture; 
};

using namespace std;
using namespace sf;

// Class
class SFML_TextureManager
{
    map<string, Texture*> texture_map;
    deque<string> path_list;

    SFML_TextureManager();
    ~SFML_TextureManager();

public:
    static SFML_TextureManager& getSingleton();

    void addSearchDirectory( string dir );
    void clearSearchDirectories();

    // Returns false if file can't be found
    bool addTexture( string path );
    // Returns false if passed Texture* is null
    bool addTexture( string internal_path, Texture* texture );

    Texture* getTexture( string path );

    bool clearTexture( string path );
    void clearAllTextures();
};
#endif
