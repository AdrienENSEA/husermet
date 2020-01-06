#include "RandomAI.h"
#include <iostream>
#include <unistd.h>

using namespace std;

namespace ai {

    void RandomAI::run(engine::Engine& e, state::State& state, int player) {
        int action, att, target;
            for (int i=6*player;i<2+6*player; i++) {
                srand (time(NULL));
                action = rand() % 2;
                if (action) {
                    do {
                        srand (time(NULL));
                        att = rand()%4;
                    } while (state.getPokemon(i).getAttack(att).getPP()==0);
                    int player_target = 1-player;
                    srand (time(NULL));
                    target = rand()%2+6*player_target;
                    if (state.getPokemon(target).getPV()!=0) target = 1-target;
                    engine::Command a(2);
                    a.setPriority(state.getPokemon(i).getAttack(att).getStatsAttack().priority);
                    a.setPokemon(i);
                    a.setPokemon_target(target);
                    a.setAttack(att);
                    e.addCommand(a);
                }
                else {
                    engine::Command c(1);
                    do {
                        srand (time(NULL));
                        target = rand()%4+2+6*player;
                    } while (state.getPokemon(target).getPV()==0);
                    c.setPriority(6);
                    c.setPokemon(i);
                    c.setPokemon_target(target);
                    e.addCommand(c); 
                }
            } 
          
    }

    int RandomAI::check_pv(engine::Engine& e, sf::RenderWindow& window, int player) {
        if (e.getState().getPokemon(2+6*player).getPV()==0 && e.getState().getPokemon(3+6*player).getPV()==0 && e.getState().getPokemon(4+6*player).getPV()==0 && e.getState().getPokemon(5+6*player).getPV()==0) { 
            if (e.getState().getPokemon(6*player).getPV()==0 && e.getState().getPokemon(1+6*player).getPV()==0) {
                if (player==1) cout << "IA adverse a perdu" << endl;
                else cout << "IA joueur a perdu" << endl;
                window.close();
                return 1;
            }
            return 0;
        }
        else {
            int target;
            std::vector<int> order = {};
            for (int i=0; i<2; i++) {
                if (e.getState().getPokemon(6*player+i).getPV()==0) {
                    if (player) cout << e.getState().getPokemon(6*player+i).getName() << " ennemi est KO" << endl;
                    if (!player) cout << e.getState().getPokemon(6*player+i).getName() << " est KO" << endl;
                    engine::Command c(3);
                    do {
                        srand (time(NULL));
                        target = rand()%4+2+6*player;
                    } while (e.getState().getPokemon(target).getPV()==0);
                    c.setPriority(6);
                    c.setPokemon(6*player+i);
                    c.setPokemon_target(target);
                    e.addCommand(c); 
                    e.runCommands(order);
                }
            }
            return 0;
        }
    }
       
}

