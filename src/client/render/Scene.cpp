#include "Scene.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <memory>

#define LENGTH_SPRITE 96
#define LENGTH_TERRAIN 290
#define LENGTH_WINDOW 512
#define HEIGHT_TERRAIN 174

using namespace std;

namespace render {

Scene::Scene () : height {LENGTH_WINDOW}, length {LENGTH_WINDOW} {
}
/*
Scene::~Scene () {
    window.close();
}
*/
void Scene::init(state::State &state, sf::RenderWindow& window) {
    
    tbackground.loadFromFile("../res/spritesheet_terrain.png", sf::IntRect(LENGTH_TERRAIN*(state.getTypeTerrain()-1), 0, LENGTH_TERRAIN*state.getTypeTerrain(), HEIGHT_TERRAIN));

    background.setTexture(tbackground);
    background.setScale(2.1f,2.1f);
    
    window.clear(sf::Color(255, 255, 255, 255));
        window.draw(background);

        interface.drawRect(window);
        
        if(!interface.setFont("../res/fontpokemon.ttf")) cout << "Echec chargement font" << endl;
        // Affichage des pokémon de l'équipe
        for (int i=0; i<6; i++) {
            if (state.getPokemon(i).getID() != 0) {
                interface.setIdPokemon(state.getPokemon(i).getID());
                interface.setTPokemon("../res/spritesheet2.png");
                interface.setPokemon(LENGTH_WINDOW-170+(i%2)*60, 360+(i/2)*60);
                interface.drawPokemon(window);
            }
        }
        // Affichage des attaques avec leur pp et type
        std::string att;
        state::Attack a;
        //int pp, pv;
        for (int i=0; i<4; i++) {
            a = state.getPokemon(0).getAttack(i);
            if (a.getType() != 0) {
                interface.setIdType(a.getType());
                interface.setTType("../res/typesheet.png");
                interface.setType(30+(i%2)*170, 415+(i/2)*50);
                interface.drawType(window);
            }
            att = a.getName();
            if (att != "name") {
                interface.setText(att, 30+(i%2)*170, 395+(i/2)*50, 16);
                interface.drawText(window);
            }
            /*
            pp = state.getPokemon(0).getAttack().at(i).getPP();
            interface.setText(std::to_string(pp)+'/'+std::to_string(a.getStatsAttack().ppmax), 95+(i%2)*170, 420+(i/2)*50, 14);
            */
            interface.setText(std::to_string(state.getPokemon(0).getAttack(i).getPP())+'/'+std::to_string(a.getStatsAttack().pp), 95+(i%2)*170, 420+(i/2)*50, 14);
            interface.drawText(window);
        }
        interface.setText(std::to_string(state.getPokemon(0).getPV())+'/'+std::to_string(state.getPokemon(0).getStats().pv), 190,250,14);
        interface.drawText(window);
        interface.setText(std::to_string(state.getPokemon(6).getPV())+'/'+std::to_string(state.getPokemon(6).getStats().pv), 150,150,14);
        interface.drawText(window);
        // Afichage des pokémon actif et adverse
        for (int i=0; i<12; i++) {
            if (state.getPokemon(i).getID() != 0 && (i==0 || i==6)) {
                if (i<6) pokemon.setBack(true);
                else pokemon.setBack(false);
                pokemon.setIdPokemon(state.getPokemon(i).getID());
                pokemon.setTexture("../res/spritesheet2.png");
                pokemon.setSprite();
                //cout << "Affichage de " << state.getPokemon(i).getName() << endl;
                pokemon.draw(window);
            }
        }
        window.display();
}

void Scene::draw (state::State &state) {
    int x;
    int y;
    sf::RenderWindow window(sf::VideoMode(height, length), "Fight");
    
    while (window.isOpen()) {
        // on gère les évènements
        sf::Event event;
        engine::Engine e;
        //window.setVerticalSyncEnabled(false);
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {/*
                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;*/
            }
            if (event.type == sf::Event::KeyPressed)
{
    if (event.key.code == sf::Keyboard::Escape)
    {
        std::cout << "the escape key was pressed" << std::endl;
        std::cout << "control:" << event.key.control << std::endl;
        std::cout << "alt:" << event.key.alt << std::endl;
        std::cout << "shift:" << event.key.shift << std::endl;
        std::cout << "system:" << event.key.system << std::endl;
    }
}
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    {
                    x = event.mouseButton.x;
                    y = event.mouseButton.y;
                    //std::cout << x << y << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    if (y>390)
                        {
                        if (x< 195 && y<440 && y >390) {
                            engine::Command a(2);
                            a.setPokemon(0);
                            a.setPokemon_target(6);
                            a.setAttack(0);
                            a.setPriority(state.getPokemon(0).getAttack(0).getStatsAttack().priority);
                            e.addCommand(a, state);
                        }
                        else if (x<342 && x> 195 && y<440 && y >390) {
                            engine::Command a(2);
                            a.setPokemon(0);
                            a.setPokemon_target(6);
                            a.setAttack(1);
                            a.setPriority(state.getPokemon(0).getAttack(1).getStatsAttack().priority);
                            e.addCommand(a, state);
                        }
                        else if (x< 195 && y >445) {
                            engine::Command a(2);
                            a.setPokemon(0);
                            a.setPokemon_target(6);
                            a.setAttack(2);
                            a.setPriority(state.getPokemon(0).getAttack(2).getStatsAttack().priority);
                            e.addCommand(a, state);
                        }
                        else if (x<342 && x> 195 && y >445) {
                            engine::Command a(2);
                            a.setPokemon(0);
                            a.setPokemon_target(6);
                            a.setAttack(3);
                            a.setPriority(state.getPokemon(0).getAttack(3).getStatsAttack().priority);
                            e.addCommand(a, state);
                        }
                        
                        if (x< 405 && x> 342 && y<420 && y >360) {
                            engine::Command c(1);
                            c.setPokemon(0);
                            c.setPokemon_target(1);
                            c.setPriority(6);
                            e.addCommand(c,state);
                            //std::unique_ptr<engine::Command> p (new engine::ChangePokemonCommand c(0,1,6));
                            //std::make_unique<engine::ChangePokemonCommand
                        }
                        engine::Command aa(2);
                        std::cout << state.getPokemon(6).getName() << " ennemi attaque " << state.getPokemon(6).getAttack(0).getName() << std::endl;
                        aa.setPriority(state.getPokemon(6).getAttack(0).getStatsAttack().priority);
                        //std::cout << "apres setP" << aa.getPriority() << std::endl;
                        aa.setPokemon(6);
                        aa.setPokemon_target(0);
                        aa.setAttack(0);
                        e.addCommand(aa, state);
                        e.runCommands(state);     
                    }
                }
            }
        }
        init(state, window);
    }
        
}

};
