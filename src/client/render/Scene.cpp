#include "Scene.h"
#include <iostream>
#include <unistd.h>

#define LENGTH_SPRITE 98
#define LENGTH_TERRAIN 290
#define HEIGHT_TERRAIN 174
#define LENGTH_WINDOW 512

using namespace std;
using namespace sf;

namespace render {

Scene::Scene () : height {512}, length {512} {
}

void Scene::draw (state::State& state) {
    sf::RenderWindow window(sf::VideoMode(height, length), "Fight");
    int x, y;
    int tmp=0;

    tbackground.loadFromFile("../res/spritesheet_terrain.png", sf::IntRect(LENGTH_TERRAIN*(state.getTypeTerrain()-1), 0, LENGTH_TERRAIN*state.getTypeTerrain(), HEIGHT_TERRAIN));

    
    background.setTexture(tbackground);
    background.setScale(2.1f,2.1f);    
    
    //interface.setTexts({"Que faire?", "Attaquer", "Pokemon", "Sac", "Fuite"});
    initPokemon(state);
    initInterface(state,window);

    // on dessine l'état
    window.clear(sf::Color(255, 255, 255, 255));
    window.draw(background);

    interface.drawRect(window);
    interface.drawTexts(window);
    pokemon1.draw(window);
    pokemon2.draw(window);
    pokemon3.draw(window);
    pokemon4.draw(window);

    if(!interface.setFont("../res/fontpokemon.ttf")) cout << "Echec chargement font" << endl;

    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        engine::Engine e;
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
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    x = event.mouseButton.x;
                    y = event.mouseButton.y;
                    //std::cout << x << y << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    setCommand(state, e, x, y);
                    DrawRefresh(window, state);
                }
            }
        }
        initInterface(state, window);

        window.display();

/*/////////////////////  Affichage des différents états \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
        if(tmp==0) {
            sleep(5);
            setCommand(state, e, 425,430);
            DrawRefresh(window, state);
            std::cout << "Echange avec le 3e pokémon" << std::endl;
            tmp++;
        }
        else if(tmp==1) {
            sleep(5);
            setCommand(state, e, 63,409);
            DrawRefresh(window, state);
            std::cout << "Attaque Tonnerre de Rayquaza" << std::endl;
            tmp++;
        }
        else if(tmp==2) {
            sleep(5);
            pokemon1.displayDamage(state, window);
            std::cout << "Pokémon touché" << std::endl;
            tmp++;
        }
        else if(tmp==3) {
            sleep(5);
            setCommand(state, e, 63,409);
            setCommand(state, e, 63,409);
            setCommand(state, e, 63,409);
            setCommand(state, e, 63,409);
            setCommand(state, e, 63,409);
            DrawRefresh(window, state);
            std::cout << "PV du pokémon ennemi faible après de nombreuses attaques" << std::endl;
            tmp++;
        }
        
/*///////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
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
    
    void Scene::initInterface(state::State& state, sf::RenderWindow& window) {
        interface.drawRect(window);
        // Affichage des pokémon de l'équipe
        for (int i=0; i<6; i++) {
            if (state.getPokemon(i).getID() != 0) {
                interface.setIdPokemon(state.getPokemon(i).getID());
                interface.setTPokemon("../res/spritesheet2.png");
                interface.setPokemon(LENGTH_WINDOW-110+(i%2)*50, 370+(i/2)*40);
                interface.drawPokemon(window);
            }
        }
        // Affichage des attaques avec leur pp et type
        std::string att;
        state::Attack a;
    
        for (int i=0; i<4; i++) {
            a = state.getPokemon(0).getAttack(i);
            if (a.getType() != 0) {
                interface.setIdType(a.getType());
                interface.setTType("../res/typesheet.png");
                interface.setType(20+(i%2)*170, 415+(i/2)*50);
                interface.drawType(window);
            }
            att = a.getName();
            if (att != "name") {
                interface.setText(att, 20+(i%2)*180, 395+(i/2)*50, 16);
                interface.drawText(window);
            }
            interface.setText(std::to_string(state.getPokemon(0).getAttack(i).getPP())+'/'+std::to_string(a.getStatsAttack().pp), 90+(i%2)*170, 420+(i/2)*50, 14);
            interface.drawText(window);
        }
    }

    void Scene::setCommand(state::State& state, engine::Engine& e, int x, int y) {
        if (y>380) {
            if (x< 200 && y<440 && y >370) {
                if (state.getPokemon(0).getAttack(0).getPP()==0) return;
                engine::Command a(2);
                a.setPokemon(0);
                a.setPokemon_target(6);
                a.setAttack(0);
                a.setPriority(state.getPokemon(0).getAttack(0).getStatsAttack().priority);
                e.addCommand(a, state);
            }
            else if (x<390 && x> 200 && y<440 && y >370) {
                if (state.getPokemon(0).getAttack(1).getPP()==0) return;
                engine::Command a(2);
                a.setPokemon(0);
                a.setPokemon_target(6);
                a.setAttack(1);
                a.setPriority(state.getPokemon(0).getAttack(1).getStatsAttack().priority);
                e.addCommand(a, state);
            }
            else if (x< 200 && y >440) {
                if (state.getPokemon(0).getAttack(2).getPP()==0) return;
                engine::Command a(2);
                a.setPokemon(0);
                a.setPokemon_target(6);
                a.setAttack(2);
                a.setPriority(state.getPokemon(0).getAttack(2).getStatsAttack().priority);
                e.addCommand(a, state);
            }
            else if (x<390 && x> 200 && y >440) {
                if (state.getPokemon(0).getAttack(3).getPP()==0) return;
                engine::Command a(2);
                a.setPokemon(0);
                a.setPokemon_target(6);
                a.setAttack(3);
                a.setPriority(state.getPokemon(0).getAttack(3).getStatsAttack().priority);
                e.addCommand(a, state);
            }

            else if (x< 450 && x> 390 && y<420 && y >380) return;
            else if (x< 510 && x> 450 && y<420 && y >380) return;
            else if (x< 450 && x> 390 && y<460 && y >420) {
                //if (state.getPokemon(3).getPV()==0) return;
                engine::Command c(1);
                c.setPokemon(0);
                c.setPokemon_target(2);
                c.setPriority(6);
                e.addCommand(c,state);
            }
            else if (x< 510 && x> 450 && y<460 && y >420) {
                if (state.getPokemon(4).getPV()==0) return;
                engine::Command c(1);
                c.setPokemon(0);
                c.setPokemon_target(3);
                c.setPriority(6);
                e.addCommand(c,state);
            }
            else if (x< 450 && x> 390 && y >460) {
                if (state.getPokemon(3).getPV()==0) return;
                engine::Command c(1);
                c.setPokemon(0);
                c.setPokemon_target(4);
                c.setPriority(6);
                e.addCommand(c,state);
            }
            else if (x< 510 && x> 450 && y >460) {
                if (state.getPokemon(4).getPV()==0) return;
                engine::Command c(1);
                c.setPokemon(0);
                c.setPokemon_target(5);
                c.setPriority(6);
                e.addCommand(c,state);
            }
            engine::Command a1(2);
            std::cout << state.getPokemon(6).getName() << " ennemi attaque " << state.getPokemon(6).getAttack(0).getName() << std::endl;
            a1.setPriority(state.getPokemon(6).getAttack(0).getStatsAttack().priority);
            a1.setPokemon(6);
            a1.setPokemon_target(0);
            a1.setAttack(0);
            e.addCommand(a1, state);
            engine::Command a2(2);
            std::cout << state.getPokemon(7).getName() << " ennemi attaque " << state.getPokemon(7).getAttack(0).getName() << std::endl;
            a2.setPriority(state.getPokemon(7).getAttack(0).getStatsAttack().priority);
            a2.setPokemon(7);
            a2.setPokemon_target(1);
            a2.setAttack(1);
            e.addCommand(a2, state);    
        }
        e.runCommands(state); 
    }

    void Scene::DrawRefresh(sf::RenderWindow& window, state::State& state) {
        pokemon1.setTexture(state.getPokemon(0).getID(), 1);
        pokemon2.setTexture(state.getPokemon(1).getID(), 1);
        pokemon3.setTexture(state.getPokemon(6).getID(), 0);
        pokemon4.setTexture(state.getPokemon(7).getID(), 0);
        pokemon1.setInfo(state.getPokemon(0));
        pokemon2.setInfo(state.getPokemon(1));
        pokemon3.setInfo(state.getPokemon(6));
        pokemon4.setInfo(state.getPokemon(7));

        window.draw(background);
        //interface.drawTexts(window);
        pokemon1.draw(window);
        pokemon2.draw(window);
        pokemon3.draw(window);
        pokemon4.draw(window);
    }
       
}

