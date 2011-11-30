#ifndef SFML_LISTENER_H__
#define SFML_LISTENER_H__

#include <SFML/Window/Event.hpp>

class My_SFML_MouseListener
{
public:
    virtual bool mouseMoved( const sf::Event::MouseMoveEvent &mouse_move ) = 0;
    virtual bool mouseButtonPressed( const sf::Event::MouseButtonEvent &mouse_button_press ) = 0;
    virtual bool mouseButtonReleased( const sf::Event::MouseButtonEvent &mouse_button_release ) = 0;
    virtual bool mouseWheelMoved( const sf::Event::MouseWheelEvent &mouse_wheel_move ) = 0;
};

class My_SFML_KeyListener
{
public:
    virtual bool keyPressed( const sf::Event::KeyEvent &key_press ) = 0;
    virtual bool keyReleased( const sf::Event::KeyEvent &key_release ) = 0;
};

class My_SFML_JoystickListener
{
public:
    virtual bool joystickMoved( const sf::Event::JoystickMoveEvent &joystick_move ) = 0;
    virtual bool joystickButtonPressed( const sf::Event::JoystickButtonEvent &joystick_button_pressed ) = 0;
    virtual bool joystickButtonReleased( const sf::Event::JoystickButtonEvent &joystick_button_released ) = 0;
    /* Connection/disconnection is all taken care of by SFML_WindowEventManager */
    //virtual bool joystickConnected( const sf::Event::JoystickConnectEvent &joystick_connect ) = 0;
    //virtual bool joystickDisconnected( const sf::Event::JoystickConnectEvent &joystick_disconnect ) = 0;
};

class My_SFML_WindowListener
{
public:
    virtual bool windowClosed( ) = 0;
    virtual bool windowResized( const sf::Event::SizeEvent &resized ) = 0;
    virtual bool windowLostFocus( ) = 0;
    virtual bool windowGainedFocus( ) = 0;
};

#endif
