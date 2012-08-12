#ifndef SFML_WindowEventManager_H__
#define SFML_WindowEventManager_H__
 
#include <map>
#include <set>

#include "SFML_Listeners.hpp"
#include "SFML_WindowEventManager.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class My_SFML_KeyListener;
class My_SFML_MouseListener;
class My_SFML_JoystickListener;
class My_SFML_WindowListener;

/* This class does not definitely support joysticks, because I have no need for them. */

class SFML_WindowEventManager
{
public:
    virtual ~SFML_WindowEventManager( void );
 
    void initialise( sf::RenderWindow *renderWindow );
    sf::RenderWindow* getRenderWindow( void );

    bool handleEvents( void );
 
    void addKeyListener( My_SFML_KeyListener *keyListener, const std::string& instanceName );
    void addMouseListener( My_SFML_MouseListener *mouseListener, const std::string& instanceName );
    void addJoystickListener( My_SFML_JoystickListener *joystickListener, const std::string& instanceName );
    void addWindowListener( My_SFML_WindowListener *windowListener, const std::string& instanceName );
 
    void removeKeyListener( const std::string& instanceName );
    void removeMouseListener( const std::string& instanceName );
    void removeJoystickListener( const std::string& instanceName );
    void removeWindowListener( const std::string& instanceName );
 
    void removeKeyListener( My_SFML_KeyListener *keyListener );
    void removeMouseListener( My_SFML_MouseListener *mouseListener );
    void removeJoystickListener( My_SFML_JoystickListener *joystickListener );
    void removeWindowListener( My_SFML_WindowListener *windowListener );
 
    void removeAllListeners( void );
    void removeAllKeyListeners( void );
    void removeAllMouseListeners( void );
    void removeAllJoystickListeners( void );
    void removeAllWindowListeners( void );
 
    /* As far as I know, this isn't needed in SFML
    void setWindowExtents( int width, int height );
    */
 
    int getNumOfJoysticks( void );
 
    static SFML_WindowEventManager& getSingleton( void );
private:
    SFML_WindowEventManager( void );
    SFML_WindowEventManager( const SFML_WindowEventManager& ) { }
    SFML_WindowEventManager & operator = ( const SFML_WindowEventManager& );
 
    bool keyPressed( const sf::Event::KeyEvent &key_press );
    bool keyReleased( const sf::Event::KeyEvent &key_release );
 
    bool mouseMoved( const sf::Event::MouseMoveEvent &mouse_move );
    bool mouseButtonPressed( const sf::Event::MouseButtonEvent &mouse_button_press );
    bool mouseButtonReleased( const sf::Event::MouseButtonEvent &mouse_button_release );
    bool mouseWheelMoved( const sf::Event::MouseWheelEvent &mouse_wheel_move );
 
    bool joystickMoved( const sf::Event::JoystickMoveEvent &joystick_move );
    bool joystickButtonPressed( const sf::Event::JoystickButtonEvent &joystick_button_pressed );
    bool joystickButtonReleased( const sf::Event::JoystickButtonEvent &joystick_button_released );
    bool joystickConnected( const sf::Event::JoystickConnectEvent &joystick_connect );
    bool joystickDisconnected( const sf::Event::JoystickConnectEvent &joystick_disconnect );
 
    bool windowClosed( );
    bool windowResized( const sf::Event::SizeEvent &resized );
    bool windowLostFocus( );
    bool windowGainedFocus( );

    /*
    OIS::Mouse        *mMouse;
    OIS::Keyboard     *mKeyboard;
    OIS::InputManager *mInputSystem;
    */
 
    std::set<unsigned int> mJoystickIDs;
    std::set<unsigned int>::iterator itJoystick;
    std::set<unsigned int>::iterator itJoystickEnd;
 
    std::map<std::string, My_SFML_KeyListener*> mKeyListeners;
    std::map<std::string, My_SFML_MouseListener*> mMouseListeners;
    std::map<std::string, My_SFML_JoystickListener*> mJoystickListeners;
    std::map<std::string, My_SFML_WindowListener*> mWindowListeners;
 
    std::map<std::string, My_SFML_KeyListener*>::iterator itKeyListener;
    std::map<std::string, My_SFML_MouseListener*>::iterator itMouseListener;
    std::map<std::string, My_SFML_JoystickListener*>::iterator itJoystickListener;
    std::map<std::string, My_SFML_WindowListener*>::iterator itWindowListener;
 
    std::map<std::string, My_SFML_KeyListener*>::iterator itKeyListenerEnd;
    std::map<std::string, My_SFML_MouseListener*>::iterator itMouseListenerEnd;
    std::map<std::string, My_SFML_JoystickListener*>::iterator itJoystickListenerEnd;
    std::map<std::string, My_SFML_WindowListener*>::iterator itWindowListenerEnd;
};
#endif
