#include "RandomAI.h"
#include <iostream>
#include <unistd.h>

using namespace std;

namespace ai {

    void RandomAI::run(engine::Engine& e, state::State& state) {
        int action, att, target;
        for (int i=6;i<8; i++) {
            srand (time(NULL));
            action = rand() % 2;
            if (action) {
                do {
                    att = rand()%4;
                } while (state.getPokemon(i).getAttack(att).getPP()==0);
                srand (time(NULL));
                target = rand()%2;
                engine::Command a(2);
                a.setPriority(state.getPokemon(i).getAttack(att).getStatsAttack().priority);
                a.setPokemon(i);
                a.setPokemon_target(target);
                a.setAttack(att);
                e.addCommand(a, state);
            }
            else {
                engine::Command c(1);
                srand (time(NULL));
                do {
                    target = rand()%4+8;
                } while (state.getPokemon(target).getPV()==0);
                c.setPriority(6);
                c.setPokemon(i);
                c.setPokemon_target(target);
                e.addCommand(c, state); 
            }
        }   
    }
       
}

