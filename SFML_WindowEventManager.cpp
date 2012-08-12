#include "SFML_Listeners.hpp"
#include "SFML_WindowEventManager.hpp"
#include "SFML_GlobalRenderWindow.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <set>
#include <map>
#include <string>
 
#include <iostream>

SFML_WindowEventManager::SFML_WindowEventManager( void )
{ }
 
SFML_WindowEventManager::~SFML_WindowEventManager( void ) {
    /* 
     * I don't -think- any of this is necessary for SFML, but let's keep it here just in case
     
    if( mInputSystem ) {
        if( mMouse ) {
            mInputSystem->destroyInputObject( mMouse );
            mMouse = 0;
        }
 
        if( mKeyboard ) {
            mInputSystem->destroyInputObject( mKeyboard );
            mKeyboard = 0;
        }
 
        if( mJoystickIDs.size() > 0 ) {
            itJoystick    = mJoystickIDs.begin();
            itJoystickEnd = mJoystickIDs.end();
            for(; itJoystick != itJoystickEnd; ++itJoystick ) {
                mInputSystem->destroyInputObject( *itJoystick );
            }
 
            mJoystickIDs.clear();
        }
 
        // If you use OIS1.0RC1 or above, uncomment this line
        // and comment the line below it
        mInputSystem->destroyInputSystem( mInputSystem );
        //mInputSystem->destroyInputSystem();
        mInputSystem = 0;
 
        // Clear Listeners
        mKeyListeners.clear();
        mMouseListeners.clear();
        mJoystickListeners.clear();
    }
    */
}
 
void SFML_WindowEventManager::initialise( sf::RenderWindow* renderWindow ) {
    SFML_GlobalRenderWindow::set(renderWindow);
}

sf::RenderWindow* SFML_WindowEventManager::getRenderWindow() {
    return SFML_GlobalRenderWindow::get();
}
 
bool SFML_WindowEventManager::handleEvents( void ) {
    sf::RenderWindow* r_window = getRenderWindow();
    if (!r_window)
        return false;

    sf::Event event;
    while ( r_window->pollEvent(event) )
    {
        switch (event.type) {
            case sf::Event::KeyPressed:
                keyPressed( event.key );
                break;

            case sf::Event::KeyReleased:
                keyReleased( event.key );
                break;

            case sf::Event::MouseMoved:
                mouseMoved( event.mouseMove );
                break;

            case sf::Event::MouseButtonPressed:
                mouseButtonPressed( event.mouseButton );
                break;

            case sf::Event::MouseButtonReleased:
                mouseButtonReleased( event.mouseButton );
                break;

            case sf::Event::MouseWheelMoved:
                mouseWheelMoved( event.mouseWheel );
                break;

            //case sf::Event::JoystickMoved: etc.
            case sf::Event::Closed:
                windowClosed();
                break;

            case sf::Event::Resized:
                windowResized( event.size );
                break;

            case sf::Event::LostFocus:
                windowLostFocus();
                break;

            case sf::Event::GainedFocus:
                windowGainedFocus();
                break;
                // There are several other ones, so no default gives a warning at compile time.
        }
    }

    return true;

    /* Old stuff
    // Need to capture / update each device every frame
    if( mMouse ) {
        mMouse->capture();
    }
 
    if( mKeyboard ) {
        mKeyboard->capture();
    }
 
    if( mJoystickIDs.size() > 0 ) {
        itJoystick    = mJoystickIDs.begin();
        itJoystickEnd = mJoystickIDs.end();
        for(; itJoystick != itJoystickEnd; ++itJoystick ) {
            (*itJoystick)->capture();
        }
    }
    */
}
 
void SFML_WindowEventManager::addKeyListener( My_SFML_KeyListener *keyListener, const std::string& instanceName ) {
    // Check for duplicate items
    itKeyListener = mKeyListeners.find( instanceName );
    if( itKeyListener == mKeyListeners.end() ) {
        mKeyListeners[ instanceName ] = keyListener;
    }
    else {
        // Duplicate Item
    }
}
 
void SFML_WindowEventManager::addMouseListener( My_SFML_MouseListener *mouseListener, const std::string& instanceName ) {
    // Check for duplicate items
    itMouseListener = mMouseListeners.find( instanceName );
    if( itMouseListener == mMouseListeners.end() ) {
        mMouseListeners[ instanceName ] = mouseListener;
    }
    else {
        // Duplicate Item
    }
    
}
 
void SFML_WindowEventManager::addJoystickListener( My_SFML_JoystickListener *joystickListener, const std::string& instanceName ) {
    if( mJoystickIDs.size() > 0 ) {
        // Check for duplicate items
        itJoystickListener = mJoystickListeners.find( instanceName );
        if( itJoystickListener == mJoystickListeners.end() ) {
            mJoystickListeners[ instanceName ] = joystickListener;
        }
        else {
            // Duplicate Item
        }
    }
}
    
void SFML_WindowEventManager::addWindowListener( My_SFML_WindowListener *windowListener, const std::string& instanceName )
{
    itWindowListener = mWindowListeners.find( instanceName );
    if( itWindowListener == mWindowListeners.end() ) {
        mWindowListeners[ instanceName ] = windowListener;
    }
    else {
        // Duplicate Item
    }
}
 
void SFML_WindowEventManager::removeKeyListener( const std::string& instanceName ) {
    // Check if item exists
    itKeyListener = mKeyListeners.find( instanceName );
    if( itKeyListener != mKeyListeners.end() ) {
        mKeyListeners.erase( itKeyListener );
    }
    else {
        // Doesn't Exist
    }
}
 
void SFML_WindowEventManager::removeMouseListener( const std::string& instanceName ) {
    // Check if item exists
    itMouseListener = mMouseListeners.find( instanceName );
    if( itMouseListener != mMouseListeners.end() ) {
        mMouseListeners.erase( itMouseListener );
    }
    else {
        // Doesn't Exist
    }
}
 
void SFML_WindowEventManager::removeJoystickListener( const std::string& instanceName ) {
    // Check if item exists
    itJoystickListener = mJoystickListeners.find( instanceName );
    if( itJoystickListener != mJoystickListeners.end() ) {
        mJoystickListeners.erase( itJoystickListener );
    }
    else {
        // Doesn't Exist
    }
}

void SFML_WindowEventManager::removeWindowListener( const std::string& instanceName ) {
    // Check if item exists
    itWindowListener = mWindowListeners.find( instanceName );
    if( itWindowListener != mWindowListeners.end() ) {
        mWindowListeners.erase( itWindowListener );
    }
    else {
        // Doesn't Exist
    }
}
 
void SFML_WindowEventManager::removeKeyListener( My_SFML_KeyListener *keyListener ) {
    itKeyListener = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if( itKeyListener->second == keyListener ) {
            mKeyListeners.erase( itKeyListener );
            break;
        }
    }
}
 
void SFML_WindowEventManager::removeMouseListener( My_SFML_MouseListener *mouseListener ) {
    itMouseListener = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if( itMouseListener->second == mouseListener ) {
            mMouseListeners.erase( itMouseListener );
            break;
        }
    }
}
 
void SFML_WindowEventManager::removeJoystickListener( My_SFML_JoystickListener *joystickListener ) {
    itJoystickListener = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        if( itJoystickListener->second == joystickListener ) {
            mJoystickListeners.erase( itJoystickListener );
            break;
        }
    }
}

void SFML_WindowEventManager::removeWindowListener( My_SFML_WindowListener *windowListener ) {
    itWindowListener = mWindowListeners.begin();
    itWindowListener = mWindowListeners.end();
    for(; itWindowListener != itWindowListenerEnd; ++itWindowListener ) {
        if( itWindowListener->second == windowListener ) {
            mWindowListeners.erase( itWindowListener );
            break;
        }
    }
}
 
void SFML_WindowEventManager::removeAllListeners( void ) {
    removeAllKeyListeners();
    removeAllMouseListeners();
    removeAllJoystickListeners();
    removeAllWindowListeners();
}
 
void SFML_WindowEventManager::removeAllKeyListeners( void ) {
    mKeyListeners.clear();
}
 
void SFML_WindowEventManager::removeAllMouseListeners( void ) {
    mMouseListeners.clear();
}
 
void SFML_WindowEventManager::removeAllJoystickListeners( void ) {
    mJoystickListeners.clear();
}

void SFML_WindowEventManager::removeAllWindowListeners( void ) {
    mWindowListeners.clear();
}
 
/*
void SFML_WindowEventManager::setWindowExtents( int width, int height ) {
    // Set mouse region (if window resizes, we should alter this to reflect as well)
    const OIS::MouseState &mouseState = mMouse->getMouseState();
    mouseState.width  = width;
    mouseState.height = height;
}
*/
 
/*
OIS::Mouse* SFML_WindowEventManager::getMouse( void ) {
    return mMouse;
}
 
OIS::Keyboard* SFML_WindowEventManager::getKeyboard( void ) {
    return mKeyboard;
}
 
OIS::JoyStick* SFML_WindowEventManager::getJoystick( unsigned int index ) {
    // Make sure it's a valid index
    if( index < mJoystickIDs.size() ) {
        return mJoystickIDs[ index ];
    }
 
    return 0;
}
*/
 
int SFML_WindowEventManager::getNumOfJoysticks( void ) {

    return mJoystickIDs.size();
}
 
bool SFML_WindowEventManager::keyPressed( const sf::Event::KeyEvent &e ) {
    itKeyListener = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if(!itKeyListener->second->keyPressed( e ))
            break;
    }
 
    return true;
}
 
bool SFML_WindowEventManager::keyReleased( const sf::Event::KeyEvent &e ) {
    itKeyListener = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if(!itKeyListener->second->keyReleased( e ))
            break;
    }
 
    return true;
}
 
bool SFML_WindowEventManager::mouseMoved( const sf::Event::MouseMoveEvent &e ) {
    itMouseListener = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if(!itMouseListener->second->mouseMoved( e ))
            break;
    }
 
    return true;
}
 
bool SFML_WindowEventManager::mouseButtonPressed( const sf::Event::MouseButtonEvent &e ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if(!itMouseListener->second->mouseButtonPressed( e ))
            break;
    }
 
    return true;
}
 
bool SFML_WindowEventManager::mouseButtonReleased( const sf::Event::MouseButtonEvent &e ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if(!itMouseListener->second->mouseButtonReleased( e ))
            break;
    }
 
    return true;
}

bool SFML_WindowEventManager::mouseWheelMoved( const sf::Event::MouseWheelEvent &mouse_wheel_move ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if(!itMouseListener->second->mouseWheelMoved( mouse_wheel_move ))
            break;
    }
 
    return true;
}
 
bool SFML_WindowEventManager::joystickMoved( const sf::Event::JoystickMoveEvent &e ) {
    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        if(!itJoystickListener->second->joystickMoved( e ))
            break;
    }
 
    return true;
}

bool SFML_WindowEventManager::joystickButtonPressed( const sf::Event::JoystickButtonEvent &e ) {
    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        if(!itJoystickListener->second->joystickButtonPressed( e ))
            break;
    }
 
    return true;
}
 
bool SFML_WindowEventManager::joystickButtonReleased( const sf::Event::JoystickButtonEvent &e ) {
    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        if(!itJoystickListener->second->joystickButtonReleased( e ))
            break;
    }
 
    return true;
}
 
bool SFML_WindowEventManager::joystickConnected( const sf::Event::JoystickConnectEvent &e ) {
    // This one is different, we don't pass it on, we use it to register a new joystick

    const unsigned int joystickID = e.joystickId;
    mJoystickIDs.insert( joystickID );
 
    return true;
}

bool SFML_WindowEventManager::joystickDisconnected( const sf::Event::JoystickConnectEvent &e ) {
    // This one is different, we don't pass it on, we use it to unregister a new joystick
    const unsigned int joystickID = e.joystickId;
    mJoystickIDs.erase( joystickID );
 
    return true;
}

bool SFML_WindowEventManager::windowClosed( )
{
    itWindowListener    = mWindowListeners.begin();
    itWindowListenerEnd = mWindowListeners.end();
    for(; itWindowListener != itWindowListenerEnd; ++itWindowListener ) {
        if(!itWindowListener->second->windowClosed( ))
            break;
    }
 
    return true;
}

bool SFML_WindowEventManager::windowResized( const sf::Event::SizeEvent &resized )
{
    itWindowListener    = mWindowListeners.begin();
    itWindowListenerEnd = mWindowListeners.end();
    for(; itWindowListener != itWindowListenerEnd; ++itWindowListener ) {
        if(!itWindowListener->second->windowResized( resized ))
            break;
    }
 
    return true;

}

bool SFML_WindowEventManager::windowLostFocus( )
{
    itWindowListener    = mWindowListeners.begin();
    itWindowListenerEnd = mWindowListeners.end();
    for(; itWindowListener != itWindowListenerEnd; ++itWindowListener ) {
        if(!itWindowListener->second->windowLostFocus( ))
            break;
    }
 
    return true;

}

bool SFML_WindowEventManager::windowGainedFocus( )
{
    itWindowListener    = mWindowListeners.begin();
    itWindowListenerEnd = mWindowListeners.end();
    for(; itWindowListener != itWindowListenerEnd; ++itWindowListener ) {
        if(!itWindowListener->second->windowGainedFocus( ))
            break;
    }
 
    return true;

}
 
SFML_WindowEventManager& SFML_WindowEventManager::getSingleton( void ) {
    static SFML_WindowEventManager singleton;
    return singleton;
}
