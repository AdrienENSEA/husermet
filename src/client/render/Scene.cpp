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
static int p, a, r, c;
static std::vector<int> order = {};
void Scene::draw (state::State& state, int ai_type) {
    sf::RenderWindow window(sf::VideoMode(height, length), "Fight");
    int x, y;
    p=0;
    a=0;
    r=0;
    c=0;
    //int tmp=0;
    engine::Engine e;

    tbackground.loadFromFile("../res/spritesheet_terrain.png", sf::IntRect(LENGTH_TERRAIN*(state.getTypeTerrain()-1), 0, LENGTH_TERRAIN*state.getTypeTerrain(), HEIGHT_TERRAIN));

    
    background.setTexture(tbackground);
    background.setScale(2.1f,2.1f);    
    
    //interface.setTexts({"Que faire?", "Attaquer", "Pokemon", "Sac", "Fuite"});
    initPokemon(state);
    initInterface(state,window,p);

    // on dessine l'état
    window.clear(sf::Color(255, 255, 255, 255));
    window.draw(background);

    //interface.drawRect(window);
    //interface.drawTexts(window);
    pokemon1.draw(window);
    pokemon2.draw(window);
    pokemon3.draw(window);
    pokemon4.draw(window);


    if(!interface.setFont("../res/fontpokemon.ttf")) cout << "Echec chargement font" << endl;

    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        int target;
        //window.setVerticalSyncEnabled(false);
/*
        if(state.getPokemon(0).getPV()==0 && r==0) {
            std::cout << state.getPokemon(0).getName() << " est KO" << std::endl;
            if (state.getPokemon(2).getPV()==0 && state.getPokemon(3).getPV()==0 && state.getPokemon(4).getPV()==0 && state.getPokemon(5).getPV()==0) {
                if (state.getPokemon(0).getPV()<=0 && state.getPokemon(1).getPV()<=0) {
                    std::cout << "Défaite" << std::endl;
                    window.close();
                }
                r=1;
                p=1;
            }
            else {
                while (r==0) {
                    while (window.pollEvent(event) && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x>390 && event.mouseButton.y>410 && state.getPokemon(convertP(event.mouseButton.x,event.mouseButton.y)).getPV()!=0) {
                        //std::cout << "while waitEvent" << state.getPokemon(convertP(event.mouseButton.x,event.mouseButton.y)).getPV() << std::endl;
                        setCommand(state,e,window,event.mouseButton.x,event.mouseButton.y, ai_type);
                        e.runCommands(state, order);
                    }
                }
                r=0;
                p=0;
                a=0;
                initInterface(state, window,p);
                DrawRefresh(window, state);
                window.display();
            }
        }
        if(state.getPokemon(1).getPV()==0 && r==0) {
            std::cout << state.getPokemon(1).getName() << " est KO" << std::endl;
            if (state.getPokemon(2).getPV()==0 && state.getPokemon(3).getPV()==0 && state.getPokemon(4).getPV()==0 && state.getPokemon(5).getPV()==0) {
                //std::cout << "Défaite" << std::endl;
                if (state.getPokemon(0).getPV()<=0 && state.getPokemon(1).getPV()<=0) {
                    std::cout << "Défaite" << std::endl;
                    window.close();
                }
                r=1;
                p=0;
            }
            else {
                while (r==0) {
                    while (window.pollEvent(event) && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x>390 && event.mouseButton.y>410 && state.getPokemon(convertP(event.mouseButton.x,event.mouseButton.y)).getPV()!=0) {
                        //std::cout << "while waitEvent" << state.getPokemon(convertP(event.mouseButton.x,event.mouseButton.y)).getPV() << std::endl;
                        p=1;
                        setCommand(state,e,window,event.mouseButton.x,event.mouseButton.y, ai_type);
                        e.runCommands(state, order);
                    }
                }
                r=0;
                p=0;
                a=0;
                initInterface(state, window,p);
                DrawRefresh(window, state);
                window.display();
            }
        }
        if(state.getPokemon(6).getPV()==0) {
            if (c==0) std::cout << state.getPokemon(6).getName() << " ennemi est KO" << std::endl;
            if (state.getPokemon(8).getPV()<=0 && state.getPokemon(9).getPV()<=0 && state.getPokemon(10).getPV()<=0 && state.getPokemon(11).getPV()<=0) {
                c=1;
                if (state.getPokemon(6).getPV()<=0 && state.getPokemon(7).getPV()<=0) {
                    std::cout << "Victoire" << std::endl;
                    window.close();
                }
            }
            else {
                int i=8;
                while(state.getPokemon(i).getPV()<=0) {
                    if (i==11) {
                        break;
                    }
                    i++;
                }
                engine::Command c(1);
                c.setPriority(6);
                c.setPokemon(6);
                c.setPokemon_target(i);
                e.addCommand(c, state); 
                e.runCommands(state, order); 
                r=0;
                p=0;
                a=0;
                DrawRefresh(window, state);
                window.display();
            }
        }
        if(state.getPokemon(7).getPV()==0) {
            if (c==0) std::cout << state.getPokemon(7).getName() << " ennemi est KO" << std::endl;
            if (state.getPokemon(8).getPV()==0 && state.getPokemon(9).getPV()==0 && state.getPokemon(10).getPV()==0 && state.getPokemon(11).getPV()==0) {
                c=1;
                if (state.getPokemon(6).getPV()<=0 && state.getPokemon(7).getPV()<=0) {
                    std::cout << "Victoire" << std::endl;
                    window.close();
                }
            }
            else {
                int i=8;
                while(state.getPokemon(i).getPV()<=0) {
                    if (i==11) {
                        break;
                    }
                    i++;
                }
                engine::Command c(1);
                c.setPriority(6);
                c.setPokemon(7);
                c.setPokemon_target(i);
                e.addCommand(c, state); 
                e.runCommands(state, order); 
                r=0;
                p=0;
                a=0;
                DrawRefresh(window, state);
                window.display();
            }
        }
*/
        //if((state.getPokemon(0).getPV() !=0 && state.getPokemon(1).getPV()!=0 && state.getPokemon(6).getPV()!=0 && state.getPokemon(7).getPV()!=0) || c==1 || r==1) {
         
            while (window.pollEvent(event))
            {
            //setCommand_Adv(e, state);
                DrawRefresh(window, state);
                if(event.type == sf::Event::Closed) {
                    std::cout << "Vous avez fermer la fenetre" << endl;
                    window.close();
                }
                if(event.type == sf::Event::KeyPressed) {
                    if(event.key.code == sf::Keyboard::Return) {
                        ai::HeuristicAI joueur;
                        joueur.run(e, state,window,0);
                        if (ai_type==0) {
                            ai::RandomAI ia;
                            ia.run(e,state,window,1);
                            e.runCommands(state, order);
                            DrawRefresh(window, state);
                            if (ia.check_pv(state,window,1)==1) return;
                        }
                        else if (ai_type==1) {
                            ai::HeuristicAI ia;
                            ia.run(e,state,window,1);
                            e.runCommands(state, order);
                            DrawRefresh(window, state);
                            if (ia.check_pv(state,window,1)==1) return;
                        }
                        else if (ai_type==2) {
                            ai::DeepAI ia;
                            ia.run(e,state,window,1);
                            e.runCommands(state, order);
                            DrawRefresh(window, state);
                            if (ia.check_pv(state,window,1)==1) return;
                        }
                        if (joueur.check_pv(state,window,0)==1) return;
                        DrawRefresh(window, state);
                        for (int i =0; i<2; i++) {
                            if (state.getPokemon(6+i).getPV()==0) std::cout << state.getPokemon(6+i).getName() << " ennemi est KO" << endl;
                            if (state.getPokemon(i).getPV()==0) std::cout << state.getPokemon(i).getName() << " est KO" << endl;
                        }
                        cout << "--------Prochain tour--------" << endl;
                    }
                }
                if(event.type == sf::Event::KeyPressed) {
                    if(event.key.code == sf::Keyboard::Space) {
                        pokemon1.displayDamage(state, window, 20, p);
                    }
                    if(event.key.code == sf::Keyboard::Left) {
                        //std::cout << "<-" << std::endl;
                        if (a%2 ==1) {
                            target = 6;
                            a++;
                            //std::cout << "g" << a << std::endl;
                            setCommand(state, e, window, x, y, ai_type, target);
                        }
                    }
                    if(event.key.code == sf::Keyboard::Right) {
                        //std::cout << "->" << std::endl;
                        if (a%2 ==1) {
                            target = 7;
                            a++ ;
                            //std::cout << "d" << a << std::endl;
                            setCommand(state, e, window, x, y, ai_type, target);
                        }
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        x = event.mouseButton.x;
                        y = event.mouseButton.y;
                        //std::cout << "mouse x: " << x << std::endl;
                        //std::cout << "mouse y: " << y << std::endl;
                        if (y>380 && x<=390) {
                            if (state.getPokemon(p).getAttack(convertA(x, y)).getStatsAttack().scope==-1) {
                                if (state.getPokemon(p).getPV()==0) setCommand(state, e, window, x, y, ai_type, target);
                            }
                            else {
                                if (a%2 == 0) a++;
                                //std::cout << "xy" << a << std::endl;
                                std::cout << "<- ou ->" << std::endl;
                            }
                            
                        }
                        if (x>390 && y>380) {
                            if (state.getPokemon(p).getPV()!=0) setCommand(state, e, window, x, y, ai_type);
                        }
                        /*
                        if (y>380 && x<=390) {
                            std::cout << "if" << std::endl;
                            while (window.waitEvent(ev)&& ev.mouseButton.button == sf::Mouse::Left && ev.mouseButton.x>285 && ev.mouseButton.x < 395 && ev.mouseButton.y<145) {
                                std::cout << "ok" <<std::endl;
                                setCommandA(state, e, x, y, ev.mouseButton.x,ev.mouseButton.y);
                                DrawRefresh(window, state);
                            }
                            std::cout << "if" << std::endl;
                        }
                        */
                    }
                }
                
            }
            initInterface(state, window, p);

            window.display();
        //}

                    

/*/////////////////////  Affichage des différents états \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
/*
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
       */
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
    
    void Scene::initInterface(state::State& state, sf::RenderWindow& window, int p) {
        interface.drawRect(window);
        interface.drawSelect(window, p);

        // Affichage des pokémon de l'équipe
        for (int i=0; i<6; i++) {
            if (state.getPokemon(i).getID() != 0) {
                
                interface.setIdPokemon(state.getPokemon(i).getID());
                interface.setTPokemon("../res/spritesheet2.png");
                if (state.getPokemon(i).getPV()==0) interface.setPokemon(LENGTH_WINDOW-110+(i%2)*50, 370+(i/2)*40, 1);
                else interface.setPokemon(LENGTH_WINDOW-110+(i%2)*50, 370+(i/2)*40);
                interface.drawPokemon(window);
            }
        }
        // Affichage des attaques avec leur pp et type
        std::string name;
        state::Attack att;
    
        for (int i=0; i<4; i++) {
            att = state.getPokemon(p).getAttack(i);
            if (att.getType() != 0) {
                interface.setIdType(att.getType());
                interface.setTType("../res/typesheet.png");
                interface.setType(20+(i%2)*170, 415+(i/2)*50);
                interface.drawType(window);
            }
            name = att.getName();
            if (name != "name") {
                interface.setText(name, 20+(i%2)*180, 395+(i/2)*50, 16);
                interface.drawText(window);
            }
            interface.setText(std::to_string(state.getPokemon(p).getAttack(i).getPP())+'/'+std::to_string(att.getStatsAttack().pp), 90+(i%2)*170, 420+(i/2)*50, 14);
            interface.drawText(window);
        }
        if (r!=0) {
            interface.setText("OK",405+((1-p)%2)*50,385,18,1.8);
            interface.drawText(window);
        }
    }

    void Scene::setCommand(state::State& state, engine::Engine& e, sf::RenderWindow& window, int x, int y, int ai_type, int target) {
        if (y>380 && x<=390) {
            int att = convertA(x,y);
            if (state.getPokemon(p).getAttack(att).getPP()==0) return;
            if (state.getPokemon(p).getPV()==0) return;
            engine::Command a(2);
            a.setPokemon(p);
            a.setPokemon_target(target);
            a.setAttack(att);
            a.setPriority(state.getPokemon(p).getAttack(att).getStatsAttack().priority);
            e.addCommand(a, state);
            r++;
            p=1-p;
        }
        
        else if (x< 450 && x> 390 && y<420 && y >380) {
            if (p==1) {
                p = 0;
                a=0;
                r=0;
                e.undoCommand();
            }
            return;
        }
        else if (x< 510 && x> 450 && y<420 && y >380) {
            if (p==0) {
                p=1;
                a=0;
                r=0;
                e.undoCommand();
            }
            return;
        }
        else if (y>380 && x> 390) {
            int poke = convertP(x,y);
            if (state.getPokemon(poke).getPV()==0) return;
            engine::Command c(1);
            c.setPokemon(p);
            c.setPokemon_target(poke);
            c.setPriority(6);
            e.addCommand(c,state);
            r++;
            p=1-p;
        }
        if (r==2) {
            //std::cout << "adv" << r << std::endl;
            if (ai_type==0) {
                ai::RandomAI ia;
                ia.run(e,state,window,1);
            }
            else if (ai_type==1) {
                ai::HeuristicAI ia;
                ia.run(e,state,window,1);
            }
            else if (ai_type==2) {
                ai::DeepAI ia;
                ia.run(e,state,window,1);
            }
            e.runCommands(state, order);
            //setCommand_Adv(e, state);
            DrawRefresh(window, state);
            r=0;
            a=0;
            p=0;
        }

    }

    void Scene::DrawRefresh(sf::RenderWindow& window, state::State& state) {

        window.clear(sf::Color(255, 255, 255, 255));
        pokemon1.setTexture(state.getPokemon(0).getID(), 1);
        pokemon2.setTexture(state.getPokemon(1).getID(), 1);
        pokemon3.setTexture(state.getPokemon(6).getID(), 0);
        pokemon4.setTexture(state.getPokemon(7).getID(), 0);
        pokemon1.setInfo(state.getPokemon(0));
        pokemon2.setInfo(state.getPokemon(1));
        pokemon3.setInfo(state.getPokemon(6),1);
        pokemon4.setInfo(state.getPokemon(7),1);
        
        window.draw(background);
        pokemon1.drawP(window);
        pokemon2.drawP(window);
        pokemon3.drawP(window);
        pokemon4.drawP(window);
        for (uint i=0; i<order.size(); i++) {
            switch(order.at(i)){
                case 0:
                    pokemon1.displayDamage(state, window, 0, 0);
                    break;
                case 1:
                    pokemon2.displayDamage(state, window, 50, 1);
                    break;
                case 6:
                    pokemon3.displayDamage(state, window, 50, 6);
                    break;
                case 7:
                    pokemon4.displayDamage(state, window, 50, 7);
                    break;
                default:
                    break;
            }
            window.draw(background);
            pokemon1.drawP(window);
            pokemon2.drawP(window);
            pokemon3.drawP(window);
            pokemon4.drawP(window);
        }
        order = {};
        pokemon1.draw(window);
        pokemon2.draw(window);
        pokemon3.draw(window);
        pokemon4.draw(window);
    }

    int Scene::convertP(int x, int y) {
        if (x< 450 && x> 390 && y<460 && y >420) return 2;
        else if (x< 510 && x> 450 && y<460 && y >420) return 3;
        else if (x< 450 && x> 390 && y >460) return 4;
        else if (x< 510 && x> 450 && y >460) return 5;
        return -1;
    }

    int Scene::convertA(int x, int y) {
        if (x< 200 && y<440 && y >370) return 0;
        else if (x<390 && x> 200 && y<440 && y >370) return 1;
        else if (x< 200 && y >440) return 2;
        else if (x<390 && x> 200 && y >440) return 3;
        return -1;
    }

    void Scene::setCommand_Adv(engine::Engine& e, state::State& state) {
        for (int i=6;i<8; i++) {
            int action = rand() % 2;
            if (action) {
                int att = rand()%4;
                int target = rand()%2;
                engine::Command a(2);
                a.setPriority(state.getPokemon(i).getAttack(att).getStatsAttack().priority);
                a.setPokemon(i);
                a.setPokemon_target(target);
                a.setAttack(att);
                e.addCommand(a, state);
            }
            else {
                engine::Command c(1);
                int target = rand()%4+8;
                c.setPriority(6);
                c.setPokemon(i);
                c.setPokemon_target(target);
                e.addCommand(c, state); 
            }
        }
        e.runCommands(state, order);   
    }
       
}

