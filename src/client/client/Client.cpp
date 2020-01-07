#include "Client.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>

#include <SFML/Graphics.hpp>

using namespace std;
static int ai_type = 3;
static int p, a, r, c;
static std::vector<int> order = {};

int convertP(int x, int y) {
    if (x< 450 && x> 390 && y<460 && y >420) return 2;
    else if (x< 510 && x> 450 && y<460 && y >420) return 3;
    else if (x< 450 && x> 390 && y >460) return 4;
    else if (x< 510 && x> 450 && y >460) return 5;
    return -1;
}

int convertA(int x, int y) {
    if (x< 200 && y<440 && y >370) return 0;
    else if (x<390 && x> 200 && y<440 && y >370) return 1;
    else if (x< 200 && y >440) return 2;
    else if (x<390 && x> 200 && y >440) return 3;
    return -1;
}
void setCommand(state::State& state, engine::Engine& e, int x, int y, int ai_type, int target, int prio=0);
void setCommand(state::State& state, engine::Engine& e, int x, int y, int ai_type, int target, int prio) {
    if (y>380 && x<=390) {
        int att = convertA(x,y);
        if (state.getPokemon(p).getAttack(att).getPP()==0) return;
        if (state.getPokemon(p).getPV()==0) return;
        engine::Command a(2);
        a.setPokemon(p);
        a.setPokemon_target(target);
        a.setAttack(att);
        a.setPriority(state.getPokemon(p).getAttack(att).getStatsAttack().priority);
        e.addCommand(a);
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
        if (prio==1) {
            engine::Command c(3);
            c.setPokemon(p);
            c.setPokemon_target(poke);
            c.setPriority(6);
            c.execute(state);
            e.setPastCommands(c);
        }
        else {
            engine::Command c(1);
            c.setPokemon(p);
            c.setPokemon_target(poke);
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
        //e.runCommands(order);
        //setCommand_Adv(e, state);
        sleep(0.5);
        r=0;
        a=0;
        p=0;
    }
}

void thread_engine(void* ptr){
    while (1) {
        if (r==2) {
        //cout << "test" << endl;

        //joueur.run(*ptr, ptr->getState(),window,0);
        engine::Engine* ptr_e=(engine::Engine*)ptr;

        ptr_e->runCommands(order);
        usleep(5000);
        r=0;
        }
    }
}

namespace client {

    Client::Client () {

    }

    void Client::run() {
        //int x, y;
        sf::RenderWindow window(sf::VideoMode(512, 512), "Fight");
        render::Scene s;
        engine::Engine e;
        ai::HeuristicAI joueur;
        ai::RandomAI ia1;
        ai::HeuristicAI ia2;
        ai::DeepAI ia3;
        int x, y;
        s.draw(window);
        std::thread t1(thread_engine, &e);
        while (window.isOpen()) {
            sf::Event event;
            int target;
            
            if(e.getState().getPokemon(0).getPV()==0 && r==0) {
                    std::cout << e.getState().getPokemon(0).getName() << " est KO" << std::endl;
                    if (e.getState().getPokemon(2).getPV()==0 && e.getState().getPokemon(3).getPV()==0 && e.getState().getPokemon(4).getPV()==0 && e.getState().getPokemon(5).getPV()==0) {
                        if (e.getState().getPokemon(0).getPV()<=0 && e.getState().getPokemon(1).getPV()<=0) {
                            std::cout << "Défaite" << std::endl;
                            window.close();
                        }
                        r=1;
                        p=1;
                    }
                    else {
                        while (r==0) {
                            while (window.pollEvent(event) && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x>390 && event.mouseButton.y>410 && e.getState().getPokemon(convertP(event.mouseButton.x,event.mouseButton.y)).getPV()!=0) {
                                //std::cout << "while waitEvent" << e.getState().getPokemon(convertP(event.mouseButton.x,event.mouseButton.y)).getPV() << std::endl;
                                setCommand(e.getState(),e,event.mouseButton.x,event.mouseButton.y, ai_type, target,1);
                                //r=2;
                            }
                        }
                        r=0;
                        p=0;
                        a=0;
                        s.initInterface(e.getState(), window,p);
                        s.DrawRefresh(window, e.getState(),order);
                        window.display();
                    }
                }
                if(e.getState().getPokemon(1).getPV()==0 && r==0) {
                    std::cout << e.getState().getPokemon(1).getName() << " est KO" << std::endl;
                    if (e.getState().getPokemon(2).getPV()==0 && e.getState().getPokemon(3).getPV()==0 && e.getState().getPokemon(4).getPV()==0 && e.getState().getPokemon(5).getPV()==0) {
                        //std::cout << "Défaite" << std::endl;
                        if (e.getState().getPokemon(0).getPV()<=0 && e.getState().getPokemon(1).getPV()<=0) {
                            std::cout << "Défaite" << std::endl;
                            window.close();
                        }
                        r=1;
                        p=0;
                    }
                    else {
                        while (r==0) {
                            while (window.pollEvent(event) && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x>390 && event.mouseButton.y>410 && e.getState().getPokemon(convertP(event.mouseButton.x,event.mouseButton.y)).getPV()!=0) {
                                //std::cout << "while waitEvent" << e.getState().getPokemon(convertP(event.mouseButton.x,event.mouseButton.y)).getPV() << std::endl;
                                p=1;
                                setCommand(e.getState(),e,event.mouseButton.x,event.mouseButton.y, ai_type, target,1);
                                //r=2;
                            }
                        }
                        r=0;
                        p=0;
                        a=0;
                        s.initInterface(e.getState(), window,p);
                        s.DrawRefresh(window, e.getState(),order);
                        window.display();
                    }
                }
                if(e.getState().getPokemon(6).getPV()==0) {
                    if (c==0) std::cout << e.getState().getPokemon(6).getName() << " ennemi est KO" << std::endl;
                    if (e.getState().getPokemon(8).getPV()<=0 && e.getState().getPokemon(9).getPV()<=0 && e.getState().getPokemon(10).getPV()<=0 && e.getState().getPokemon(11).getPV()<=0) {
                        c=1;
                        if (e.getState().getPokemon(6).getPV()<=0 && e.getState().getPokemon(7).getPV()<=0) {
                            std::cout << "Victoire" << std::endl;
                            window.close();
                        }
                    }
                    else {
                        int i=8;
                        while(e.getState().getPokemon(i).getPV()<=0) {
                            if (i==11) {
                                break;
                            }
                            i++;
                        }
                        engine::Command c(3);
                        c.setPriority(6);
                        c.setPokemon(6);
                        c.setPokemon_target(i);
                        e.addCommand(c); 
                        //r=2;
                        p=0;
                        a=0;
                        s.DrawRefresh(window, e.getState(),order);
                        window.display();
                    }
                }
                if(e.getState().getPokemon(7).getPV()==0) {
                    if (c==0) std::cout << e.getState().getPokemon(7).getName() << " ennemi est KO" << std::endl;
                    if (e.getState().getPokemon(8).getPV()==0 && e.getState().getPokemon(9).getPV()==0 && e.getState().getPokemon(10).getPV()==0 && e.getState().getPokemon(11).getPV()==0) {
                        c=1;
                        if (e.getState().getPokemon(6).getPV()<=0 && e.getState().getPokemon(7).getPV()<=0) {
                            std::cout << "Victoire" << std::endl;
                            window.close();
                        }
                    }
                    else {
                        int i=8;
                        while(e.getState().getPokemon(i).getPV()<=0) {
                            if (i==11) {
                                break;
                            }
                            i++;
                        }
                        engine::Command c(3);
                        c.setPriority(6);
                        c.setPokemon(7);
                        c.setPokemon_target(i);
                        e.addCommand(c); 
                        //r=2;
                        p=0;
                        a=0;
                        s.DrawRefresh(window, e.getState(),order);
                        window.display();
                    }
                }

            if((e.getState().getPokemon(0).getPV() !=0 && e.getState().getPokemon(1).getPV()!=0 && e.getState().getPokemon(6).getPV()!=0 && e.getState().getPokemon(7).getPV()!=0) || c==1 || r==1) {
                
            while (window.pollEvent(event)) {
                s.DrawRefresh(window, e.getState(),order);
                if(event.type == sf::Event::Closed) {
                    std::cout << "Vous avez fermer la fenetre" << endl;
                    
                    e.writeJSON(e.getPastCommands());
                    window.close();
                    return;
                }

                if(event.type == sf::Event::KeyPressed && ai_type<4 && ai_type>0) {
                    if(event.key.code == sf::Keyboard::Return) {
                        if (joueur.check_pv(e,window,0)==0) {
                            joueur.run(e, e.getState(),0);
                            //r=2;
                        }
                        if (ai_type==1 && ia1.check_pv(e, window, 1)==0) {
                            ia1.run(e,e.getState(),1);
                            r=2;
                            s.DrawRefresh(window, e.getState(),order);
                            if (ia1.check_pv(e,window,1)==1) return;
                        }
                        else if (ai_type==2 && ia2.check_pv(e, window, 1)==0) {
                            ia2.run(e,e.getState(),1);
                            r=2;
                            s.DrawRefresh(window, e.getState(),order);
                            if (ia2.check_pv(e,window,1)==1) return;
                        }
                        else if (ai_type==3 && ia3.check_pv(e, window, 1)==0) {
                            ia3.run(e,e.getState(),1);
                            r=2;
                            s.DrawRefresh(window, e.getState(),order);
                            if (ia3.check_pv(e,window,1)==1) return;
                        }
                        if (joueur.check_pv(e,window,0)==1 || ia1.check_pv(e,window,1)==1 || ia2.check_pv(e,window,1)==1 || ia3.check_pv(e,window,1)==1) {
                            return;
                        }
                        s.DrawRefresh(window, e.getState(),order);
                        for (int i =0; i<2; i++) {
                            if (e.getState().getPokemon(6+i).getPV()==0) std::cout << e.getState().getPokemon(6+i).getName() << " ennemi est KO" << endl;
                            if (e.getState().getPokemon(i).getPV()==0) std::cout << e.getState().getPokemon(i).getName() << " est KO" << endl;
                        }
                        cout << "--------Prochain tour--------" << endl;
                    }
                    s.initInterface(e.getState(), window, p);
                }
                        
                if(event.type == sf::Event::KeyPressed) {
                    if(event.key.code == sf::Keyboard::Left) {
                        //std::cout << "<-" << std::endl;
                        if (a%2 ==1) {
                            target = 6;
                            a++;
                            //std::cout << "g" << a << std::endl;
                            setCommand(e.getState(), e, x, y, ai_type, target);
                        }
                    }
                    if(event.key.code == sf::Keyboard::Right) {
                        //std::cout << "->" << std::endl;
                        if (a%2 ==1) {
                            target = 7;
                            a++ ;
                            //std::cout << "d" << a << std::endl;
                            setCommand(e.getState(), e, x, y, ai_type, target);
                        }
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        x = event.mouseButton.x;
                        y = event.mouseButton.y;
                        std::cout << "mouse x: " << x << std::endl;
                        std::cout << "mouse y: " << y << std::endl;
                        if (y>380 && x<=390) {
                            if (e.getState().getPokemon(p).getAttack(convertA(x, y)).getStatsAttack().scope==-1) {
                                if (e.getState().getPokemon(p).getPV()!=0) setCommand(e.getState(), e, x, y, ai_type, target);
                            }
                            else {
                                if (a%2 == 0) a++;
                                //std::cout << "xy" << a << std::endl;
                                std::cout << "<- ou ->" << std::endl;
                            }
                            
                        }
                        if (x>390 && y>380) {
                            if (e.getState().getPokemon(p).getPV()!=0) setCommand(e.getState(), e, x, y, ai_type, target);
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
                    s.initInterface(e.getState(), window, p);
                }
                s.initInterface(e.getState(), window, p);
            }
            s.initInterface(e.getState(), window, p);
            window.display();
            }
        }
        t1.join();
    }

    void Client::play() {
        sf::RenderWindow window(sf::VideoMode(512, 512), "Fight");
        render::Scene s;
        engine::Engine e;
        engine::Command command(0);
        s.draw(window);
        int k=0;
        std::thread t1(thread_engine, &e);
        while (window.isOpen()) {
            sf::Event event;
            s.DrawRefresh(window,e.getState(),order);
            s.initInterface(e.getState(),window,p);
            window.display();
            while (window.pollEvent(event)){
                if(event.type == sf::Event::Closed) {
                    std::cout << "Vous avez fermer la fenetre" << endl;
                    window.close();
                }
            }
            while(k<10){
                command.readJSON(command);
                e.addCommand(command);
                r=2;
                k++;/*
                s.DrawRefresh(window,e.getState(),order);
                s.initInterface(e.getState(),window,p);
                window.display();*/
            }
            
        }
        t1.join();
    }
    
    // Setters and Getters

};