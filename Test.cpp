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

    cManager.CreateCursor( IMCursorManager::DEFAULT, tManager.GetTexture( "UglyBlueMouse.png" ));//, 30, 30 );

    IMButton* myButton = new IMInstantButton();
    myButton->SetNormalTexture( tManager.GetTexture( "Button.png" ) );
    myButton->SetHoverTexture( tManager.GetTexture( "Button2.png" ) );
    myButton->SetPressedTexture( tManager.GetTexture( "Button3.png" ) );
    myButton->SetPosition( 10, 10 );
    myButton->SetSize( 200, 200 );
    IMGuiManager::getSingleton().registerWidget( "Button", myButton );

    IMButton* myButton2 = new IMButton();
    myButton2->SetNormalTexture( tManager.GetTexture( "Button.png" ) );
    myButton2->SetHoverTexture( tManager.GetTexture( "Button2.png" ) );
    myButton2->SetPressedTexture( tManager.GetTexture( "Button3.png" ) );
    myButton2->SetPosition( 100, 50 );
    myButton2->SetSize( 300, 200 );
    IMGuiManager::getSingleton().registerWidget( "Button2", myButton2 );



    while (app.IsOpen())
    {
        weManager.handleEvents();

        app.Clear( sf::Color::White );

        gManager.Begin();

        if (myButton2->Do())
            myButton2->SetPosition( 300, 300 );

        if (myButton->Do())
            app.Close(); 

        gManager.End();

        cManager.DrawCursor();
        app.Display();
    }
}
