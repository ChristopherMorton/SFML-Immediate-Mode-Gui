#include "IMGuiManager.hpp"

#include "IMGuiWidget.hpp"

#include <iostream>

IMGuiManager::IMGuiManager() :
    id_map(),
    widget_vector(),
    render_stack(),
    curr_id(0),
    r_window(NULL)
{
    widget_vector.push_back( NULL ); // pre-padded with a null to block the 0 index for error passing
}

IMGuiManager::IMGuiManager(RenderWindow* renderer) :
    id_map(),
    widget_vector(),
    render_stack(),
    curr_id(0),
    r_window(renderer)
{
    widget_vector.push_back( NULL ); // pre-padded with a null to block the 0 index for error passing
}

IMGuiManager::~IMGuiManager()
{
    // Deletes any outstanding IMGuiWidgets
    vector<IMGuiWidget*>::iterator it, it_end;
    it = widget_vector.begin();
    it_end = widget_vector.end();
    while (it != it_end)
    {
        if ((*it)) {
            delete (*it);
            (*it) = NULL;
        }
        ++it;
    }
    widget_vector.clear();
}

IMGuiManager& IMGuiManager::getSingleton()
{
    static IMGuiManager singleton;
    return singleton;
}

///////////////////////////////////////////////////////////////////////////
/* MouseListener to update state
bool IMGuiManager::mouseMoved( const Event::MouseMoveEvent &mouse_move )
{
    //cout << "Mouse moved: X=" << mouse_move.X << " Y=" << mouse_move.Y << endl;
    state.mouse_x = mouse_move.X;
    state.mouse_y = mouse_move.Y;
    return true; 
}

bool IMGuiManager::mouseButtonPressed( const Event::MouseButtonEvent &mouse_button_press )
{
    if (mouse_button_press.Button == Mouse::Left)
        state.mouse_down = 1;
    return true; 
}

bool IMGuiManager::mouseButtonReleased( const Event::MouseButtonEvent &mouse_button_release )
{
    if (mouse_button_release.Button == Mouse::Left)
        state.mouse_down = 0;
    return true; 
}

bool IMGuiManager::mouseWheelMoved( const Event::MouseWheelEvent &mouse_wheel_move )
{ 
    return true;
}
*//////////////////////////////////////////////////////////////////////////

void IMGuiManager::setRenderWindow(RenderWindow* renderer)
{
    r_window = renderer;
}

RenderWindow* IMGuiManager::getRenderWindow()
{
    return r_window;
}

void IMGuiManager::begin()
{
    if (NULL == r_window) return; // Can't do a GUI without a window, dummy

    state.hot_widget = NULL;
    // Get mouse state from sf::Mouse
    state.mouse_down = sf::Mouse::isButtonPressed( sf::Mouse::Left );
    state.mouse_pos = sf::Mouse::getPosition( *r_window );

    // std::cout << state.mouse_pos.x << ", " << state.mouse_pos.y << ": " << state.mouse_down << std::endl;
}

void IMGuiManager::pushSprite( Sprite* sprite )
{
    if (sprite)
        render_stack.push( sprite );
}

void IMGuiManager::end()
{
    if (NULL == r_window) {
        // Don't have a RenderWindow! 
        render_stack.empty();
        return; 
    }

    // Draw the stuff!
    while (!render_stack.empty()) {
        Sprite* sprite = render_stack.top();
        render_stack.pop();
        if (sprite) {
            r_window->draw( *sprite );
            delete sprite;
        }
    }

    if (NULL != state.active_widget && 0 == state.mouse_down) {
        // That is to say, the mouse is not clicked, so clear active stuff
        state.active_widget = NULL;
    }
}

int IMGuiManager::runWidget( string name )
{
    return runWidget( getID( name ) );
}

int IMGuiManager::runWidget( unsigned int id )
{
    IMGuiWidget* widget = getWidget( id );
    if (!widget)
        return 0; // no associated widget

    return widget->doWidget();
}

const unsigned int IMGuiManager::registerWidget( string name, IMGuiWidget* widgetItem )
{

    if (id_map.count( name ) // already at least one widget with this name
            || widgetItem == NULL) // not a valid widget
        return false;

    widget_vector.push_back( widgetItem );
    return id_map[name] = widget_vector.size();
}

IMGuiWidget* IMGuiManager::getWidget( string name )
{
    return getWidget( getID( name ) );
}

IMGuiWidget* IMGuiManager::getWidget( unsigned int id )
{
    if ( !id || id >= widget_vector.size())
        return NULL;
    else 
        return widget_vector[id];
}

unsigned int IMGuiManager::getID( string name )
{
    map<string, unsigned int>::iterator it;
    it = id_map.find( name );

    if (it != id_map.end())
        return it->second;
    else
        return 0; // error code for widget ids
}
