#ifndef SFML_GLOBALRENDERWINDOW_HPP__
#define SFML_GLOBALRENDERWINDOW_HPP__

// As it says.  This is a small header file that grants global render window access

namespace sf { class RenderWindow; };

struct GlobalRenderWindow
{
    static sf::RenderWindow*& GetWindow() {
        static sf::RenderWindow* pointer;
        return pointer;
    }

    static void SetWindow( sf::RenderWindow* window) {
        GetWindow() = window;
    }
};

#endif
