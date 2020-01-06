#include "HeuristicAI.h"
#include <iostream>
#include <unistd.h>

using namespace std;

namespace ai {

    void HeuristicAI::run(engine::Engine& e, state::State& state, int player) {
        int d = 0;
        int attack, target;
        std::vector<int> order = {};
            for (int pokemon=6*player; pokemon<2+6*player; pokemon++) {
                if (state.getPokemon(pokemon).getPV()!=0) {
                    if (state.getPokemon(pokemon).getAttack(0).getPP()==0 && state.getPokemon(pokemon).getAttack(1).getPP()==0 && state.getPokemon(pokemon).getAttack(2).getPP()==0 && state.getPokemon(pokemon).getAttack(3).getPP()==0) {
                        engine::Command c(1);
                        target = change(state, player);
                        c.setPriority(6);
                        c.setPokemon(pokemon);
                        c.setPokemon_target(target);
                        e.addCommand(c); 
                    }
                    else {
                        int attack_opt = 0;
                        int target_opt = 0;
                        int d_max = 0;
                        for (attack=0; attack<4; attack++) {
                            if (state.getPokemon(pokemon).getAttack(attack).getPP()!=0) {
                                int player_target = 1-player;
                                for (target=6*player_target; target<2+6*player_target; target++) {
                                    if (state.getPokemon(target).getPV()!=0) {
                                        engine::AttackCommand ac(pokemon, target, attack);
                                        d = ac.damage(state);
                                        //cout << "pokemon"<<pokemon<<"attack"<< attack<<"target"<<target<<"d" << d << endl;
                                        if (d > d_max) {
                                            d_max = d;
                                            attack_opt = attack;
                                            target_opt = target;
                                            //cout << "pokemon"<<pokemon<<"attack_opt"<< attack_opt<<"target_opt"<<target_opt << "dmax" << d_max << endl;
                                        }
                                    }
                                }
                            }
                        }
                        if (d_max == 0) return;
                        engine::Command a(2);
                        a.setPriority(state.getPokemon(pokemon).getAttack(attack_opt).getStatsAttack().priority);
                        a.setPokemon(pokemon);
                        a.setPokemon_target(target_opt);
                        a.setAttack(attack_opt);
                        e.addCommand(a);
                    }
                }
            }  
    }

    int HeuristicAI::change(state::State& state, int player) {
        int d;
        //int attack_opt = 0;
        //int target_opt = 0;
        int d_max = 0;
        int pokemon_opt = 2+6*player;

        for (int pokemon=2+6*player; pokemon<6+6*player; pokemon++) {
            if (state.getPokemon(pokemon).getPV()!=0) {
                for (int attack=0; attack<4; attack++) {
                    if (state.getPokemon(pokemon).getAttack(attack).getPP()!=0) {
                        int player_target = 1-player;
                        for (int target=6*player_target; target<2+6*player_target; target++) {
                            if (state.getPokemon(target).getPV()!=0) {
                                engine::AttackCommand ac(pokemon, target, attack);
                                d=ac.damage(state);
                                if (d > d_max) {
                                    d_max = d;
                                    //attack_opt = attack;
                                    //target_opt = target;
                                    pokemon_opt = pokemon;
                                }
                            }
                        }
                    }
                }
            }
        }
        return pokemon_opt;
    }

    int HeuristicAI::check_pv(engine::Engine& e, sf::RenderWindow& window, int player) {
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
                    target = change(e.getState(), player);
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

