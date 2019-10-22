#include "Scene.h"

namespace render {

Scene::Scene () {
    height = 512;
    length = 512;
}

void Scene::drawScene () {
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
        window.clear(sf::Color(255, 255, 255, 255));
        window.display();
    }
}

}

