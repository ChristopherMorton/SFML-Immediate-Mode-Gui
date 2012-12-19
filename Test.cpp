#include "SFML_WindowEventManager.hpp"
#include "SFML_TextureManager.hpp"
#include "IMGuiManager.hpp"
#include "IMCursorManager.hpp"
#include "IMButton.hpp"
#include "IMInstantButton.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

int main()
{
    sf::RenderWindow app(sf::VideoMode(1000, 1000, 32), "SFML Window");//, sf::Style::Fullscreen); 

    IMGuiManager& gManager = IMGuiManager::getSingleton();
    IMCursorManager& cManager = IMCursorManager::getSingleton();
    SFML_TextureManager& tManager = SFML_TextureManager::getSingleton();
    SFML_WindowEventManager& weManager = SFML_WindowEventManager::getSingleton(); 

    gManager.setRenderWindow( &app );
    weManager.initialise( &app );

    cManager.createCursor( IMCursorManager::DEFAULT, tManager.getTexture( "resources/UglyBlueMouse.png" ));//, 30, 30 );

    IMButton* myButton = new IMInstantButton();
    myButton->setNormalTexture( tManager.getTexture( "resources/Button.png" ) );
    myButton->setHoverTexture( tManager.getTexture( "resources/Button2.png" ) );
    myButton->setPressedTexture( tManager.getTexture( "resources/Button3.png" ) );
    myButton->setPosition( 10, 10 );
    myButton->setSize( 200, 200 );
    IMGuiManager::getSingleton().registerWidget( "Button", myButton );

    IMButton* myButton2 = new IMButton();
    myButton2->setNormalTexture( tManager.getTexture( "resources/Button.png" ) );
    myButton2->setHoverTexture( tManager.getTexture( "resources/Button2.png" ) );
    myButton2->setPressedTexture( tManager.getTexture( "resources/Button3.png" ) );
    myButton2->setPosition( 100, 100 );
    myButton2->setSize( 300, 300 );
    IMGuiManager::getSingleton().registerWidget( "Button2", myButton2 );

    bool part1 = true;
    float move_x = 200, move_y = 50, dy = .2;

    while (app.isOpen())
    {
        weManager.handleEvents();

        app.clear( sf::Color::White );

        gManager.begin();

        if (part1 && myButton2->doWidget())
            part1 = false;

        if (myButton->doMove(move_x, move_y, false))
            app.close(); 

        if (move_y > 250) dy = -0.2;
        if (move_y < 50) dy = 0.2;

        move_y += dy;

        gManager.end();

        cManager.drawCursor();
        app.display();
    }
}
