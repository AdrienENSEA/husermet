#include "Scene.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>


#define LENGTH_SPRITE 98
#define LENGTH_TERRAIN 290
#define HEIGHT_TERRAIN 174
#define LENGTH_WINDOW 512

using namespace std;
using namespace sf;

namespace render {

    Scene::Scene () : height {512}, length {512}, player(0){
    }
    Scene::Scene (uint h, uint l, int player) : height(h), length(l), player(player){
    }

    static int p, a, r, c;

    void Scene::draw (engine::Engine& e, sf::RenderWindow& window, int ai_type) {
        p=0;
        a=0;
        r=0;
        c=0;
        std::vector<int> order = {};

        tbackground.loadFromFile("../res/spritesheet_terrain.png", sf::IntRect(LENGTH_TERRAIN*(e.getState().getTypeTerrain()-1), 0, LENGTH_TERRAIN*e.getState().getTypeTerrain(), HEIGHT_TERRAIN));

        background.setTexture(tbackground);
        background.setScale(2.1f,2.1f);    
        
        //interface.setTexts({"Que faire?", "Attaquer", "Pokemon", "Sac", "Fuite"});
        initPokemon(e.getState());
        initInterface(e.getState(),window,p,r);

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
        if (ai_type!=0) run(window,e,ai_type, order);
    }

    void Scene::run(sf::RenderWindow& window, engine::Engine& e, int ai_type, std::vector<int>& order) {
        int x, y;

        ai::HeuristicAI joueur;
        ai::RandomAI ia1;
        ai::HeuristicAI ia2;
        ai::DeepAI ia3;

        while (window.isOpen())
        {
            // on gère les évènements
            sf::Event event;
            int target;
            //window.setVerticalSyncEnabled(false);
            
                if(e.getState().getPokemon(0+6*player).getPV()==0 && r==0) {
                    std::cout << e.getState().getPokemon(0+6*player).getName() << " est KO" << std::endl;
                    if (e.getState().getPokemon(2+6*player).getPV()==0 && e.getState().getPokemon(3+6*player).getPV()==0 && e.getState().getPokemon(4+6*player).getPV()==0 && e.getState().getPokemon(5+6*player).getPV()==0) {
                        if (e.getState().getPokemon(0+6*player).getPV()<=0 && e.getState().getPokemon(1+6*player).getPV()<=0) {
                            std::cout << "Défaite" << std::endl;
                            window.close();
                        }
                        r=1;
                        p=1;
                        initInterface(e.getState(), window,p,r);
                        DrawRefresh(window, e.getState(),order);
                        window.display();
                    }
                    else {
                        while (r==0) {
                            while (window.pollEvent(event) && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x>390 && event.mouseButton.y>410 && e.getState().getPokemon(convertP(event.mouseButton.x,event.mouseButton.y)+6*player).getPV()!=0) {
                                //std::cout << "while waitEvent" << e.getState().getPokemon(convertP(event.mouseButton.x,event.mouseButton.y)).getPV() << std::endl;
                                setCommand(e.getState(),e,window,event.mouseButton.x,event.mouseButton.y, ai_type,order,target,1);
                                e.runCommands(order, player);
                                initInterface(e.getState(), window,p,r);
                                DrawRefresh(window, e.getState(),order);
                                window.display();
                            }
                        }
                        r=0;
                        p=0;
                        a=0;
                        initInterface(e.getState(), window,p,r);
                        DrawRefresh(window, e.getState(),order);
                        window.display();
                    }
                }
                if(e.getState().getPokemon(1+6*player).getPV()==0 && r==0) {
                    std::cout << e.getState().getPokemon(1+6*player).getName() << " est KO" << std::endl;
                    if (e.getState().getPokemon(2+6*player).getPV()==0 && e.getState().getPokemon(3+6*player+6*player).getPV()==0 && e.getState().getPokemon(4+6*player).getPV()==0 && e.getState().getPokemon(5+6*player).getPV()==0) {
                        //std::cout << "Défaite" << std::endl;
                        if (e.getState().getPokemon(0+6*player).getPV()<=0 && e.getState().getPokemon(1+6*player).getPV()<=0) {
                            std::cout << "Défaite" << std::endl;
                            window.close();
                        }
                        r=1;
                        p=0;
                        initInterface(e.getState(), window,p,r);
                        DrawRefresh(window, e.getState(),order);
                        window.display();
                    }
                    else {
                        while (r==0) {
                            while (window.pollEvent(event) && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x>390 && event.mouseButton.y>410 && e.getState().getPokemon(convertP(event.mouseButton.x,event.mouseButton.y)+6*player).getPV()!=0) {
                                //std::cout << "while waitEvent" << e.getState().getPokemon(convertP(event.mouseButton.x,event.mouseButton.y)).getPV() << std::endl
                                p=1;
                                setCommand(e.getState(),e,window,event.mouseButton.x,event.mouseButton.y, ai_type,order,target,1);
                                e.runCommands(order, player);
                                initInterface(e.getState(), window,p,r);
                                DrawRefresh(window, e.getState(),order);
                                window.display();
                            }
                        }
                        r=0;
                        p=0;
                        a=0;
                        initInterface(e.getState(), window,p,r);
                        DrawRefresh(window, e.getState(),order);
                        window.display();
                    }
                }
                if(e.getState().getPokemon(6-6*player).getPV()==0) {
                    if (c==0) std::cout << e.getState().getPokemon(6-6*player).getName() << " ennemi est KO" << std::endl;
                    if (e.getState().getPokemon(8-6*player).getPV()<=0 && e.getState().getPokemon(9-6*player).getPV()<=0 && e.getState().getPokemon(10-6*player).getPV()<=0 && e.getState().getPokemon(11-6*player).getPV()<=0) {
                        c=1;
                        if (e.getState().getPokemon(6-6*player).getPV()<=0 && e.getState().getPokemon(7-6*player).getPV()<=0) {
                            std::cout << "Victoire" << std::endl;
                            window.close();
                        }
                    }
                    else {
                        int i=8-6*player;
                        while(e.getState().getPokemon(i).getPV()<=0) {
                            if (i==11-6*player) {
                                break;
                            }
                            i++;
                        }
                        engine::Command c(3);
                        c.setPriority(6);
                        c.setPokemon(6-6*player);
                        c.setPokemon_target(i);
                        e.addCommand(c); 
                        e.runCommands(order, player); 
                        r=0;
                        p=0;
                        a=0;
                        DrawRefresh(window, e.getState(),order);
                        initInterface(e.getState(), window,p,r);
                        window.display();
                    }
                }
                if(e.getState().getPokemon(7-6*player).getPV()==0) {
                    if (c==0) std::cout << e.getState().getPokemon(7-6*player).getName() << " ennemi est KO" << std::endl;
                    if (e.getState().getPokemon(8-6*player).getPV()==0 && e.getState().getPokemon(9-6*player).getPV()==0 && e.getState().getPokemon(10-6*player).getPV()==0 && e.getState().getPokemon(11-6*player).getPV()==0) {
                        c=1;
                        if (e.getState().getPokemon(6-6*player).getPV()<=0 && e.getState().getPokemon(7-6*player).getPV()<=0) {
                            std::cout << "Victoire" << std::endl;
                            window.close();
                        }
                    }
                    else {
                        int i=8-6*player;
                        while(e.getState().getPokemon(i).getPV()<=0) {
                            if (i==11-6*player) {
                                break;
                            }
                            i++;
                        }
                        engine::Command c(3);
                        c.setPriority(6);
                        c.setPokemon(7-6*player);
                        c.setPokemon_target(i);
                        e.addCommand(c); 
                        e.runCommands(order, player); 
                        r=0;
                        p=0;
                        a=0;
                        DrawRefresh(window, e.getState(),order);
                        initInterface(e.getState(), window,p,r);
                        window.display();
                    }
                }

                if((e.getState().getPokemon(0).getPV() !=0 && e.getState().getPokemon(1).getPV()!=0 && e.getState().getPokemon(6).getPV()!=0 && e.getState().getPokemon(7).getPV()!=0) || c==1 || r==1) {
                
                    while (window.pollEvent(event))
                    {
                        
                        if(event.type == sf::Event::Closed) {
                            std::cout << "Vous avez fermer la fenetre" << endl;
                            window.close();
                        }

                        if(event.type == sf::Event::KeyPressed && ai_type<4 && ai_type>0) {
                            if(event.key.code == sf::Keyboard::Return) {
                                if (joueur.check_pv(e,window,0)==0) 
                                    joueur.run(e, e.getState(),0);
                                if (ai_type==1 && ia1.check_pv(e, window, 1)==0) {
                                    ia1.run(e,e.getState(),1);
                                    e.runCommands(order, player);
                                    DrawRefresh(window, e.getState(),order);
                                    if (ia1.check_pv(e,window,1)==1) return;
                                    DrawRefresh(window, e.getState(), order);
                                }
                                else if (ai_type==2 && ia2.check_pv(e, window, 1)==0) {
                                    ia2.run(e,e.getState(),1);
                                    e.runCommands(order, player);
                                    DrawRefresh(window, e.getState(),order);
                                    if (ia2.check_pv(e,window,1)==1) return;
                                    DrawRefresh(window, e.getState(), order);
                                }
                                else if (ai_type==3 && ia3.check_pv(e, window, 1)==0) {
                                    ia3.run(e,e.getState(),1);
                                    e.runCommands(order, player);
                                    DrawRefresh(window, e.getState(),order);
                                    if (ia3.check_pv(e,window,1)==1) return;
                                    DrawRefresh(window, e.getState(), order);
                                }
                                if (joueur.check_pv(e,window,0)==1) return;
                                DrawRefresh(window, e.getState(),order);
                                for (int i =0; i<2; i++) {
                                    if (e.getState().getPokemon(6+i-6*player).getPV()==0) std::cout << e.getState().getPokemon(6+i-6*player).getName() << " ennemi est KO" << endl;
                                    if (e.getState().getPokemon(i+6*player).getPV()==0) std::cout << e.getState().getPokemon(i+6*player).getName() << " est KO" << endl;
                                }
                                cout << "--------Prochain tour--------" << endl;
                            }
                            initInterface(e.getState(), window, p,r);
                        }
                        
                        if(event.type == sf::Event::KeyPressed) {
                            if(event.key.code == sf::Keyboard::Space) {
                                pokemon1.displayDamage(e.getState(), window, 20, p);
                            }
                            if(event.key.code == sf::Keyboard::Left) {
                                //std::cout << "<-" << std::endl;
                                if (a%2 ==1) {
                                    target = 6;
                                    a++;
                                    //std::cout << "g" << a << std::endl;
                                    setCommand(e.getState(), e, window, x, y, ai_type,order, target);
                                }
                            }
                            if(event.key.code == sf::Keyboard::Right) {
                                //std::cout << "->" << std::endl;
                                if (a%2 ==1) {
                                    target = 7;
                                    a++ ;
                                    //std::cout << "d" << a << std::endl;
                                    setCommand(e.getState(), e, window, x, y, ai_type,order, target);
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
                                    if (e.getState().getPokemon(p+6*player).getAttack(convertA(x, y)).getStatsAttack().scope==-1) {
                                        if (e.getState().getPokemon(p+6*player).getPV()==0) setCommand(e.getState(), e, window, x, y, ai_type,order, target);
                                    }
                                    else {
                                        if (a%2 == 0) a++;
                                        //std::cout << "xy" << a << std::endl;
                                        std::cout << "<- ou ->" << std::endl;
                                    }
                                    
                                }
                                if (x>390 && y>380) {
                                    if (e.getState().getPokemon(p+6*player).getPV()!=0) setCommand(e.getState(), e, window, x, y, ai_type,order,target);
                                }
                                /*
                                if (y>380 && x<=390) {
                                    std::cout << "if" << std::endl;
                                    while (window.waitEvent(ev)&& ev.mouseButton.button == sf::Mouse::Left && ev.mouseButton.x>285 && ev.mouseButton.x < 395 && ev.mouseButton.y<145) {
                                        std::cout << "ok" <<std::endl;
                                        setCommandA(e.getState(), e, x, y, ev.mouseButton.x,ev.mouseButton.y);
                                        DrawRefresh(window, e.getState());
                                    }
                                    std::cout << "if" << std::endl;
                                }
                                */
                            }
                            initInterface(e.getState(), window, p,r);
                        }
                        //initInterface(e.getState(), window, p,r);
                    }
                    initInterface(e.getState(), window, p,r);
                    window.display();
                }      

    /*/////////////////////  Affichage des différents états \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
            if (ai_type==-1) {
                ai_type = -2;
                sleep(3);
                setCommand(e.getState(), e, window, 425,430, 0,order,target);
                DrawRefresh(window, e.getState(),order);
                initInterface(e.getState(), window, p,r);
                //std::cout << "Echange avec le 3e pokémon" << std::endl;
                setCommand(e.getState(), e, window, 478,430, 0,order,target);
                DrawRefresh(window, e.getState(),order);
                initInterface(e.getState(), window, p,r);
                //std::cout << "Echange avec le 4e pokémon" << std::endl;
            }
    /*///////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
        }
    }
    
    void Scene::initPokemon(state::State& state) {
        pokemon1.setTexture(state.getPokemon(0+6*player).getID(), 1);
        pokemon1.setInfo(state.getPokemon(0+6*player));
        pokemon1.setSprite(0);
        
        pokemon2.setTexture(state.getPokemon(1+6*player).getID(), 1);
        pokemon2.setInfo(state.getPokemon(1+6*player));
        pokemon2.setSprite(1);
        
        pokemon3.setTexture(state.getPokemon(6-6*player).getID(), 0);
        pokemon3.setInfo(state.getPokemon(6-6*player));
        pokemon3.setSprite(2);
        
        pokemon4.setTexture(state.getPokemon(7-6*player).getID(), 0);
        pokemon4.setInfo(state.getPokemon(7-6*player));
        pokemon4.setSprite(3);
        
    }
    
    void Scene::initInterface(state::State& state, sf::RenderWindow& window, int p, int r) {
        interface.drawRect(window);
        interface.drawSelect(window, p);

        // Affichage des pokémon de l'équipe
        for (int i=0; i<6; i++) {
            if (state.getPokemon(i+6*player).getID() != 0) {
                
                interface.setIdPokemon(state.getPokemon(i+6*player).getID());
                interface.setTPokemon("../res/spritesheet2.png");
                if (state.getPokemon(i+6*player).getPV()==0) interface.setPokemon(LENGTH_WINDOW-110+(i%2)*50, 370+(i/2)*40, 1);
                else interface.setPokemon(LENGTH_WINDOW-110+(i%2)*50, 370+(i/2)*40);
                interface.drawPokemon(window);
            }
        }
        // Affichage des attaques avec leur pp et type
        std::string name;
        state::Attack att;
    
        for (int i=0; i<4; i++) {
            att = state.getPokemon(p+6*player).getAttack(i);
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
            interface.setText(std::to_string(state.getPokemon(p+6*player).getAttack(i).getPP())+'/'+std::to_string(att.getStatsAttack().pp), 90+(i%2)*170, 420+(i/2)*50, 14);
            interface.drawText(window);
        }
        if (r!=0) {
            interface.setText("OK",405+((1-p)%2)*50,385,18,1.8);
            interface.drawText(window);
        }
    }

    void Scene::setCommand(state::State& state, engine::Engine& e, sf::RenderWindow& window, int x, int y, int ai_type, std::vector<int>& order, int target, int prio) {
        if (y>380 && x<=390) {
            int att = convertA(x,y);
            if (state.getPokemon(p+6*player).getAttack(att).getPP()==0) return;
            if (state.getPokemon(p+6*player).getPV()==0) return;
            if (state.getPokemon(p+6*player).getAttack(att).getStatsAttack().scope==3) {
                engine::Command a1(2);
                a1.setPokemon(p+6*player);
                a1.setPokemon_target(1-p+6*player);
                a1.setAttack(att);
                a1.setPriority(state.getPokemon(p+6*player).getAttack(att).getStatsAttack().priority);
                e.addCommand(a1);
                engine::Command a2(2);
                a2.setPokemon(p+6*player);
                a2.setPokemon_target(6-6*player);
                a2.setAttack(att);
                a2.setPriority(state.getPokemon(p+6*player).getAttack(att).getStatsAttack().priority);
                e.addCommand(a2);
                engine::Command a3(2);
                a3.setPokemon(p+6*player);
                a3.setPokemon_target(7-6*player);
                a3.setAttack(att);
                a3.setPriority(state.getPokemon(p+6*player).getAttack(att).getStatsAttack().priority);
                e.addCommand(a3);
            }
            else {
                engine::Command a(2);
                a.setPokemon(p+6*player);
                a.setPokemon_target(target-6*player);
                a.setAttack(att);
                a.setPriority(state.getPokemon(p+6*player).getAttack(att).getStatsAttack().priority);
                e.addCommand(a);
            }
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
            if (state.getPokemon(poke+6*player).getPV()==0) return;
            if (prio==1) {
                engine::Command c(3);
                c.setPokemon(p+6*player);
                c.setPokemon_target(poke+6*player);
                c.setPriority(6);
                c.execute(state,player);
                e.setPastCommands(c);
            }
            else {
                engine::Command c(1);
                c.setPokemon(p+6*player);
                c.setPokemon_target(poke+6*player);
                c.setPriority(6);
                e.addCommand(c);
            }
            r++;
            p=1-p;
        }
        if (r==2) {
            //std::cout << "adv" << r << std::endl;
            if (ai_type==1) {
                ai::RandomAI ia;
                ia.run(e,state,1);
            }
            else if (ai_type==2) {
                ai::HeuristicAI ia;
                ia.run(e,state,1);
            }
            else if (ai_type==3) {
                ai::DeepAI ia;
                ia.run(e,state,1);
            }
            else if (ai_type==4) {
                // Envoie JSON et r2cup Json puis lqnce;ent co;;qnd
            }
            
            e.runCommands(order, player);
            //setCommand_Adv(e, state);
            DrawRefresh(window, state,order);
            r=0;
            a=0;
            p=0;
        }

    }

    void Scene::DrawRefresh(sf::RenderWindow& window, state::State& state, std::vector<int>& order) {

        //window.clear(sf::Color(255, 255, 255, 255));
        pokemon1.setTexture(state.getPokemon(0+6*player).getID(), 1);
        pokemon2.setTexture(state.getPokemon(1+6*player).getID(), 1);
        pokemon3.setTexture(state.getPokemon(6-6*player).getID(), 0);
        pokemon4.setTexture(state.getPokemon(7-6*player).getID(), 0);
        pokemon1.setInfo(state.getPokemon(0+6*player));
        pokemon2.setInfo(state.getPokemon(1+6*player));
        pokemon3.setInfo(state.getPokemon(6-6*player),1);
        pokemon4.setInfo(state.getPokemon(7-6*player),1);
        
        window.draw(background);
        pokemon1.drawP(window);
        pokemon2.drawP(window);
        pokemon3.drawP(window);
        pokemon4.drawP(window);
        for (uint i=0; i<order.size(); i++) {
            if (player ==0) {
                switch(order.at(i)){
                    case 0:
                        //interface.setText("test",10,400,20);
                        //interface.drawText(window);
                        pokemon1.displayDamage(state, window, 0, 0+6*player);
                        
                        break;
                    case 1:
                        pokemon2.displayDamage(state, window, 50, 1+6*player);
                        break;
                    case 6:
                        pokemon3.displayDamage(state, window, 50, 6-6*player);
                        break;
                    case 7:
                        pokemon4.displayDamage(state, window, 50, 7-6*player);
                        break;
                    default:
                        break;
                }
            }
            if (player ==1) {
                switch(order.at(i)){
                    case 0:
                        //interface.setText("test",10,400,20);
                        //interface.drawText(window);
                        pokemon3.displayDamage(state, window, 0, 0+6*player);
                        
                        break;
                    case 1:
                        pokemon4.displayDamage(state, window, 50, 1+6*player);
                        break;
                    case 6:
                        pokemon1.displayDamage(state, window, 50, 6-6*player);
                        break;
                    case 7:
                        pokemon2.displayDamage(state, window, 50, 7-6*player);
                        break;
                    default:
                        break;
                }
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

    
/*
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
                e.addCommand(a);
            }
            else {
                engine::Command c(1);
                int target = rand()%4+8;
                c.setPriority(6);
                c.setPokemon(i);
                c.setPokemon_target(target);
                e.addCommand(c); 
            }
        }
        e.runCommands(order);   
    }
    */   
}

