#include "SFML_WindowEventManager.hpp"
#include "SFML_TextureManager.hpp"
#include "IMGuiManager.hpp"
#include "IMCursorManager.hpp"
#include "IMButton.hpp"
#include "IMInstantButton.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow app(sf::VideoMode(1000, 1000, 32), "SFML Window");//, sf::Style::Fullscreen); 

    IMGuiManager& gManager = IMGuiManager::getSingleton();
    IMCursorManager& cManager = IMCursorManager::getSingleton();
    SFML_TextureManager& tManager = SFML_TextureManager::getSingleton();
    SFML_WindowEventManager& weManager = SFML_WindowEventManager::getSingleton(); 

    weManager.initialise( &app );

    cManager.createCursor( IMCursorManager::DEFAULT, tManager.getTexture( "UglyBlueMouse.png" ));//, 30, 30 );

    IMButton* myButton = new IMInstantButton();
    myButton->setNormalTexture( tManager.getTexture( "Button.png" ) );
    myButton->setHoverTexture( tManager.getTexture( "Button2.png" ) );
    myButton->setPressedTexture( tManager.getTexture( "Button3.png" ) );
    myButton->setPosition( 10, 10 );
    myButton->setSize( 200, 200 );
    IMGuiManager::getSingleton().registerWidget( "Button", myButton );

    IMButton* myButton2 = new IMButton();
    myButton2->setNormalTexture( tManager.getTexture( "Button.png" ) );
    myButton2->setHoverTexture( tManager.getTexture( "Button2.png" ) );
    myButton2->setPressedTexture( tManager.getTexture( "Button3.png" ) );
    myButton2->setPosition( 100, 50 );
    myButton2->setSize( 300, 200 );
    IMGuiManager::getSingleton().registerWidget( "Button2", myButton2 );



    while (app.isOpen())
    {
        weManager.handleEvents();

        app.clear( sf::Color::White );

        gManager.begin();

        if (myButton2->doWidget())
            myButton2->setPosition( 300, 300 );

        if (myButton->doWidget())
            app.close(); 

        gManager.end();

        cManager.drawCursor();
        app.display();
    }
}
