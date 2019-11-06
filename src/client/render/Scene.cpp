#include "Scene.h"
#include <iostream>
#include <unistd.h>
#include <string>

#define LENGTH_SPRITE 96
#define LENGTH_TERRAIN 290
#define LENGTH_WINDOW 512
#define HEIGHT_TERRAIN 174

using namespace std;

namespace render {

Scene::Scene () : height {LENGTH_WINDOW}, length {LENGTH_WINDOW}{
}

Scene::~Scene () {
    window.close();
}

void Scene::draw (state::State& state) {
    sf::RenderWindow window(sf::VideoMode(height, length), "Fight");

    tbackground.loadFromFile("../res/spritesheet_terrain.png", sf::IntRect(LENGTH_TERRAIN*(state.getTypeTerrain()-1), 0, LENGTH_TERRAIN*state.getTypeTerrain(), HEIGHT_TERRAIN));

    
    background.setTexture(tbackground);
    background.setScale(2.1f,2.1f);
    

    //while (window.isOpen()) {
        // on gère les évènements
        sf::Event event;
        //window.setVerticalSyncEnabled(false);
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // on dessine l'état
        window.clear(sf::Color(255, 255, 255, 255));
        window.draw(background);

        interface.drawRect(window);
        
        if(!interface.setFont("../res/fontpokemon.ttf")) cout << "Echec chargement font" << endl;
        // Affichage des pokémon de l'équipe
        for (int i=0; i<6; i++) {
            if (state.getPokemon(i).getID() != 0) {
                interface.setIdPokemon(state.getPokemon(i).getID());
                interface.setTPokemon("../res/spritesheet.png");
                interface.setPokemon(LENGTH_WINDOW-170+(i%2)*60, 360+(i/2)*60);
                interface.drawPokemon(window);
            }
        }
        // Affichage des attaques avec leur pp et type
        std::string att;
        std::string pp;
        for (int i=0; i<4; i++) {
            if (state.getPokemon(0).getAttack().at(i).getType() != 0) {
                interface.setIdType(state.getPokemon(0).getAttack().at(i).getType());
                interface.setTType("../res/typesheet.png");
                interface.setType(30+(i%2)*170, 415+(i/2)*50);
                interface.drawType(window);
            }
            att = state.getPokemon(0).getAttack().at(i).getName();
            if (att != "name") {
                interface.setText(att, 30+(i%2)*170, 395+(i/2)*50, 16);
                interface.drawText(window);
            }
            pp = std::to_string(state.getPPs().at(i))+'/'+std::to_string(state.getPokemon(0).getAttack().at(i).getStatsAttack().ppmax);
            if (pp != "0") {
                interface.setText(pp, 95+(i%2)*170, 420+(i/2)*50, 14);
                interface.drawText(window);
            }
        }
        // Afichage des pokémon actif et adverse
        for (int i=0; i<12; i++) {
            if (state.getPokemon(i).getID() != 0 && (i==0 || i==6)) {
                if (i<6) pokemon.setBack(true);
                else pokemon.setBack(false);
                pokemon.setIdPokemon(state.getPokemon(i).getID());
                pokemon.setTexture("../res/spritesheet.png");
                pokemon.setSprite();
                //cout << "Affichage de " << state.getPokemon(i).getName() << endl;
                pokemon.draw(window);
            }
        }
        window.display();
        sleep(5);
    //}


    }
}

