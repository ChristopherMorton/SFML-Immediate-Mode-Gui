#include "SFML_WindowEventManager.hpp"
#include "SFML_TextureManager.hpp"
#include "IMGuiManager.hpp"
#include "IMCursorManager.hpp"
#include "IMButton.hpp"
#include "IMInstantButton.hpp"
#include "IMImageButton.hpp"
#include "IMTextButton.hpp"
#include "IMEdgeButton.hpp"
#include "IMEdgeTextButton.hpp"

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

    cManager.createCursor( IMCursorManager::DEFAULT, tManager.getTexture( "resources/UglyBlueMouse.png" ), 0, 0, 64, 32 );

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

    IMImageButton* myImageButton = new IMImageButton();
    myImageButton->setNormalTexture( tManager.getTexture( "resources/Button.png" ) );
    myImageButton->setHoverTexture( tManager.getTexture( "resources/Button2.png" ) );
    myImageButton->setPressedTexture( tManager.getTexture( "resources/Button3.png" ) );
    myImageButton->setImage( tManager.getTexture( "resources/Button2.png" ) );
    myImageButton->setPosition( 500, 500 );
    myImageButton->setSize( 100, 100 );
    myImageButton->setImageOffset( 10, 20 );
    myImageButton->setImageSize( 40, 20 );
    IMGuiManager::getSingleton().registerWidget( "ImageButton", myImageButton );

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/TTF/LiberationMono-Regular.ttf"))
        return EXIT_FAILURE;

    std::string t = "Testing Testing 123";

    IMTextButton* myTextButton = new IMTextButton();
    myTextButton->setNormalTexture( tManager.getTexture( "resources/Button.png" ) );
    myTextButton->setHoverTexture( tManager.getTexture( "resources/Button2.png" ) );
    myTextButton->setPressedTexture( tManager.getTexture( "resources/Button3.png" ) );
    myTextButton->setText( &t );
    myTextButton->setFont( &font );
    myTextButton->setPosition( 10, 10 );
    myTextButton->setSize( 280, 70 );
    myTextButton->setTextSize( 16 );
    myTextButton->setTextColor( sf::Color::Black );
    myTextButton->centerText();
    IMGuiManager::getSingleton().registerWidget( "TextButton", myTextButton );

    std::string t2 = "\"Test q and p ||";

    IMEdgeTextButton* myTextButton2 = new IMEdgeTextButton();
    myTextButton2->setCornerAllTextures( tManager.getTexture( "resources/Button.png" ) );
    myTextButton2->setEdgeAllTextures( tManager.getTexture( "resources/Button2.png" ) );
    myTextButton2->setNormalTexture( tManager.getTexture( "resources/Button.png" ) );
    myTextButton2->setHoverTexture( tManager.getTexture( "resources/Button2.png" ) );
    myTextButton2->setPressedTexture( tManager.getTexture( "resources/Button3.png" ) );
    myTextButton2->setText( &t2 );
    myTextButton2->setFont( &font );
    myTextButton2->setPosition( 300, 10 );
    myTextButton2->setSize( 280, 40 );
    myTextButton2->setTextSize( 16 );
    myTextButton2->setTextColor( sf::Color::Black );
    myTextButton2->setEdgeWidth( 12 );
    myTextButton2->centerText();
    IMGuiManager::getSingleton().registerWidget( "TextButton", myTextButton2 );

    IMEdgeButton* myEdgeButton = new IMEdgeButton();
    myEdgeButton->setCornerAllTextures( tManager.getTexture( "resources/Button.png" ) );
    myEdgeButton->setEdgeAllTextures( tManager.getTexture( "resources/Button2.png" ) );
    myEdgeButton->setNormalTexture( tManager.getTexture( "resources/Button.png" ) );
    myEdgeButton->setHoverTexture( tManager.getTexture( "resources/Button2.png" ) );
    myEdgeButton->setPressedTexture( tManager.getTexture( "resources/Button3.png" ) );
    myEdgeButton->setEdgeWidth( 10 );
    myEdgeButton->setPosition( 600, 100 );
    myEdgeButton->setSize( 100, 100 );


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

        if (myImageButton->doWidget())
            part1 = true;

        if (myTextButton->doWidget())
           app.close();

        if (myTextButton2->doWidget())
           app.close();

        if (myEdgeButton->doWidget())
           app.close();

        if (move_y > 250) dy = -0.2;
        if (move_y < 50) dy = 0.2;

        move_y += dy;

        gManager.end();

        cManager.drawCursor();
        app.display();
    }
}
