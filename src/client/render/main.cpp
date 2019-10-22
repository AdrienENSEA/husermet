#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "../render.h"
#include <string.h>

using namespace std;
using namespace render;

int main(int argc, char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);
	
    Scene scene;
    sf::RenderWindow window(sf::VideoMode(512, 512), "Tilemap");
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
        window.display();
    }
    return 0;
}
