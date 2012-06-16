#ifndef IMGUI_MANAGER_HPP__
#define IMGUI_MANAGER_HPP__

/*
 * Basically, this is a class that maintains UI state
 * and gives an immediate-mode interface to Gui widgets.
 *
 * However, this class only organizes the widgets, and so
 * they need to be constructed and loaded before they can be used.
 * This may not appear very immediate-mode, but it simply makes
 * the interface more flexible.  Rather than passing in a render
 * texture every time you need a widget, or, for instance,
 * having different rendering techniques for different classes,
 * with this, textures can be built and loaded beforehand
 * to allow for efficient and flexible rendering.
 *
 * This also makes the interface very simple.
 * Just call runWidget( "WidgetName" ) and the correct widget will
 * be drawn, interacted with, and will return the correct result.
 * Of course, each type of widget will have its own specific
 * ways to set itself up, which the user needs to do on their own.
 *
 * Also, if you like, you can access the internal widget ID of a given widget,
 * and call runWidget( id_num ).  There might be a small speedup
 * from doing this if the number of widgets is large.
 *
 * NOTE: You don't -have- to register widgets here at all.
 * The primary function of this class is to maintain the UI state.
 * If desired, you can instantiate and keep track of IMGuiWidgets
 * and manually call their doWidget() functions yourself.
 * In fact, this is recommended, as you don't need to cast from
 * IMGuiWidget* to, say, IMGuiButton* in order to do button-specific things.
 *
 * BUT: You still need to call begin() and end() regardless.
 *
 *
 * IMPORTANT:
 * This class functions only in conjunction with SFML_WindowEventHandler.
 * It registers as a listener and renders to the same window that is
 * tied to SFML_WindowEventHandler's singleton.  You only have to register 
 * the RenderWindow through SFML_WindowEventHandler's initialise function.
 *
 *
 * Author: Christopher Morton
 * Date: September 15, 2011
 */

//#include "SFML_Listeners.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <map>
#include <vector>
#include <stack>
#include <string>

class IMGuiWidget;

using namespace std;
using namespace sf;

class IMGuiManager // : public My_SFML_MouseListener
{
    map<string, unsigned int> id_map;
    vector<IMGuiWidget*> widget_vector;
    stack<sf::Sprite*> render_stack;
    unsigned int curr_id;

    IMGuiManager();
    // Note: on destruction, IMGuiManager will delete all mapped Widgets.
    ~IMGuiManager();
public:

    static IMGuiManager& getSingleton();

    /* MouseListener functions -- UNNEEDED
    virtual bool mouseMoved( const Event::MouseMoveEvent &mouse_move );
    virtual bool mouseButtonPressed( const Event::MouseButtonEvent &mouse_button_press );
    virtual bool mouseButtonReleased( const Event::MouseButtonEvent &mouse_button_release );
    virtual bool mouseWheelMoved( const Event::MouseWheelEvent &mouse_wheel_move );
    */

    void begin();
    void pushSprite( sf::Sprite* sprite );
    void end();
    int runWidget( string name );
    int runWidget( unsigned int id_num );

    const unsigned int registerWidget( string name, IMGuiWidget* widgetItem );

    IMGuiWidget* getWidget( string name );
    IMGuiWidget* getWidget( unsigned int id_num );
    unsigned int getID( string name );

    struct UIState {
        IMGuiWidget* hot_widget;
        IMGuiWidget* active_widget;

        sf::Vector2i mouse_pos;
        int mouse_down;
        // This doesn't include keyboard stuff yet, because I don't need it yet
    };

    UIState state;
};

#endif
