#include "Scene.h"
#include <iostream>

#define LENGTH_SPRITE 96
#define LENGTH_TERRAIN 290
#define HEIGHT_TERRAIN 174

using namespace std;
using namespace sf;

namespace render {

Scene::Scene () : height {512}, length {512}{
}

void Scene::draw (state::State& state) {
    sf::RenderWindow window(sf::VideoMode(height, length), "Fight");

    tbackground.loadFromFile("../res/spritesheet_terrain.png", sf::IntRect(LENGTH_TERRAIN*(state.getTypeTerrain()-1), 0, LENGTH_TERRAIN*state.getTypeTerrain(), HEIGHT_TERRAIN));

    
    background.setTexture(tbackground);
    background.setScale(2.1f,2.1f);    
    
    interface.setTexts({"Que faire?", "Attaquer", "Pokemon", "Sac", "Fuite"});
    this->initPokemon(state);

    // on dessine l'état
    window.clear(sf::Color(255, 255, 255, 255));
    window.draw(background);

    interface.drawRect(window);
    interface.drawTexts(window);
    pokemon1.draw(window);
    pokemon2.draw(window);
    pokemon3.draw(window);
    pokemon4.draw(window);

    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        //window.setVerticalSyncEnabled(false);
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Space) {
                    pokemon1.displayDamage(state, window);
                }
            }
        }  
        
        window.display();
    }


    }
    
    void Scene::initPokemon(state::State& state) {
        pokemon1.setTexture(state.getPokemon(0).getID(), 1);
        pokemon1.setInfo(state.getPokemon(0));
        pokemon1.setSprite(0);
        
        pokemon2.setTexture(state.getPokemon(1).getID(), 1);
        pokemon2.setInfo(state.getPokemon(1));
        pokemon2.setSprite(1);
        
        pokemon3.setTexture(state.getPokemon(6).getID(), 0);
        pokemon3.setInfo(state.getPokemon(6));
        pokemon3.setSprite(2);
        
        pokemon4.setTexture(state.getPokemon(7).getID(), 0);
        pokemon4.setInfo(state.getPokemon(7));
        pokemon4.setSprite(3);
        
    }
       
}

