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
    sf::RenderWindow window(sf::VideoMode(height, length), "Fight");

    tbackground.loadFromFile("../res/spritesheet_terrain.png", sf::IntRect(LENGTH_TERRAIN*(state.getTypeTerrain()-1), 0, LENGTH_TERRAIN*state.getTypeTerrain(), HEIGHT_TERRAIN));

    
    background.setTexture(tbackground);
    background.setScale(2.1f,2.1f);    
    
    

    while (window.isOpen())
    {
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
/*
        std::string att = state.getPokemon(0).getAttack().at(0).getName();
        interface.setText(att, 200, 410);
        interface.drawText(window);
        att = state.getPokemon(0).getAttack().at(1).getName();
        interface.setText(att, 350, 410);
        interface.drawText(window);
        att = state.getPokemon(0).getAttack().at(2).getName();
        interface.setText(att, 200, 460);
        interface.drawText(window);
        att = state.getPokemon(0).getAttack().at(3).getName();
        interface.setText(att, 350, 460);
        interface.drawText(window);
        interface.setText("Retour", 5, 415);
        interface.drawText(window);
*/
        
        for (int i=0; i<12; i++) {
            if (state.getPokemon(i).getID() != 0) {
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
    }


    }
}

