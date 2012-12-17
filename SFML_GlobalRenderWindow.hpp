#ifndef SFML_GLOBALRENDERWINDOW_HPP__
#define SFML_GLOBALRENDERWINDOW_HPP__

// As it says.  This is a small header file that grants global render window access

namespace sf { class RenderWindow; };

struct SFML_GlobalRenderWindow
{
    static sf::RenderWindow*& get() {
        static sf::RenderWindow* pointer;
        return pointer;
    }

    static void set( sf::RenderWindow* window) {
        get() = window;
    }
};

#endif
