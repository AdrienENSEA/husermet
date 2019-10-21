/*
g++ -c testpokemon.cpp
g++ testpokemon.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
*/

/*
Notes :
    remember to make trigger touch
             make toString, compare
    put coordonates sprites in csv
    
*/


#include <SFML/Graphics.hpp>

#define LENGTH_SPRITE 96
#define LENGTH_WINDOW 512
#define SCALE_SPRITE 1.3f

int main()
{
    // on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(LENGTH_WINDOW, LENGTH_WINDOW), "Tilemap");

    sf::Texture texture1;
    texture1.loadFromFile("spritesheet.png", sf::IntRect(0, 0, LENGTH_SPRITE, LENGTH_SPRITE));
    sf::Texture texture2;
    texture2.loadFromFile("spritesheet.png", sf::IntRect(LENGTH_SPRITE*3, 0, LENGTH_SPRITE, LENGTH_SPRITE));
    texture1.setSmooth(true);
    texture2.setSmooth(true);

    sf::Sprite pokemon1;
    sf::Sprite pokemon2;
    pokemon1.setTexture(texture1);
    pokemon2.setTexture(texture2);
    pokemon1.setPosition(sf::Vector2f(400.f, 10.f));
    pokemon2.setPosition(sf::Vector2f(10.f, 150.f));
    pokemon1.setScale(SCALE_SPRITE, SCALE_SPRITE);
    pokemon2.setScale(SCALE_SPRITE, SCALE_SPRITE);
    
    sf::Font font;
    std::string filefont = "fontpokemon.ttf";
    font.loadFromFile(filefont);
    
    sf::Text text;
    text.setFont(font);
    text.setString("Attaquer");
    text.setCharacterSize(18);
    text.setPosition(200, 400);
    text.setColor(sf::Color::Black);
    
    sf::RectangleShape rectangle(sf::Vector2f(LENGTH_WINDOW-175, LENGTH_WINDOW-375));
    rectangle.setPosition(175-10, 375-10);
    rectangle.setOutlineThickness(10);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));
        

    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // on dessine le niveau
        window.clear(sf::Color(255, 255, 255, 255));
        window.draw(pokemon1);
        window.draw(pokemon2);
        window.draw(rectangle);
        window.draw(text);
        window.display();
    }

    return 0;
}

//
