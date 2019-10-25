#include "Scene.h"
#include <iostream>

#define LENGTH_SPRITE 96
#define LENGTH_TERRAIN 290
#define HEIGHT_TERRAIN 174

using namespace std;

namespace render {

Scene::Scene () : height {512}, length {512}{
}

void Scene::draw (state::State& state) {
    sf::RenderWindow window(sf::VideoMode(height, length), "Tilemap");
    /*std::string filefont = "../res/fontpokemon.ttf";
    font.loadFromFile(filefont);
	sf::Image image;
	image.loadFromFile("../res/sand.png");
    // rendre le blanc (255,255,255) transparent (0)
	//image.createMaskFromColor(sf::Color(255, 255, 255), 0);

    sf::Texture back;
    back.loadFromImage(image); 
    sf::Sprite p;
        p.setTexture(back);
    p.setScale(2.1f,2.1f); 
// rendre image transparente (0) ou légèrement (150)
    p.setColor(sf::Color(255, 255, 255, 220));    
     */

    
    tbackground.loadFromFile("../res/spritesheet_terrain.png", sf::IntRect(LENGTH_TERRAIN*(state.getTypeTerrain()-1), 0, LENGTH_TERRAIN*state.getTypeTerrain(), HEIGHT_TERRAIN));

    
    background.setTexture(tbackground);
    background.setScale(2.1f,2.1f); 
// rendre image transparente (0) ou légèrement (150)
    background.setColor(sf::Color(255, 255, 255, 250));    
    
    window.clear(sf::Color(255, 255, 255, 255));
    window.draw(background);

    interface.drawRect(window);
    
    interface.setFont("../res/fontpokemon.ttf");
    interface.setText("Attaquer", 200, 410);
    interface.drawText(window);
    interface.setText("Pokemon", 350, 410);
    interface.drawText(window);
    interface.setText("Sac", 200, 460);
    interface.drawText(window);
    interface.setText("Fuite", 350, 460);
    interface.drawText(window);
    interface.setText("Que faire ?", 5, 415);
    interface.drawText(window);
   
    
    pokemon.setBack(true);
    int idpokemon=state.getPokemon(0).getID();
    pokemon.setTexture("../res/spritesheet.png", idpokemon);
    pokemon.setSprite();
    pokemon.draw(window);

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


    }
}

