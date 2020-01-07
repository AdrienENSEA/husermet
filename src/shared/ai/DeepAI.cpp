#include "DeepAI.h"
#include <iostream>
#include <unistd.h>

using namespace std;
int rmax=2;
namespace ai {
    void DeepAI::run(engine::Engine& e, state::State& state, int player) {
        std::vector<int> target_done = {}, pokemon_done = {};
        int target;
        int r=0;
        

            int damages_opt[6];
            int attacks_opt[6];
            int targets_opt[6];
            int i1=-1, i2;

            for (int pokemon=6*player; pokemon<2+6*player;pokemon++) {
                if (state.getPokemon(pokemon).getPV()!=0 && find(pokemon_done.begin(), pokemon_done.end(), pokemon)==pokemon_done.end()) { // si le pokémon a encore des PV et n'a pas encore attaqué
                    for (int attack=0; attack<4; attack++) {
                        if (state.getPokemon(pokemon).getAttack(attack).getPP()!=0) {
                            for (int target=6*(1-player); target<2+6*(1-player);target++){
                                if (state.getPokemon(target).getPV()!=0 && find(target_done.begin(), target_done.end(), target)==target_done.end() && find(pokemon_done.begin(), pokemon_done.end(), pokemon)==pokemon_done.end()) {
                                    engine::AttackCommand ac(pokemon, target, attack);
                                    int d=ac.damage(state);
                                    if (d >=state.getPokemon(target).getPV()) {
                                        //int other_p = 6*player+1-pokemon+6*player;
                                        if (state.getPokemon(pokemon).getStats().speed>state.getPokemon(target).getStats().speed) {
                                            engine::Command a(2);
                                            a.setPriority(state.getPokemon(pokemon).getAttack(attack).getStatsAttack().priority);
                                            a.setPokemon(pokemon);
                                            a.setPokemon_target(target);
                                            a.setAttack(attack);
                                            e.addCommand(a);
                                            cout << "1";
                                            damages_opt[pokemon-6*player] = d;
                                            attacks_opt[pokemon-6*player] = attack;
                                            targets_opt[pokemon-6*player] = target;
                                            target_done.push_back(target);
                                            pokemon_done.push_back(pokemon);
                                            i1=pokemon-6*player;
                                            if(++r==rmax) return;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            
            
            opt(state, damages_opt, attacks_opt, targets_opt, player, pokemon_done, target_done);
            if (i1==-1) {
                i1 = max(damages_opt,6);
                int pokemon_opt1 = i1 + player*6;
                if ( (pokemon_opt1==6*player && state.getPokemon(pokemon_opt1).getPV()!=0) || (pokemon_opt1==1+6*player && state.getPokemon(pokemon_opt1).getPV()!=0) ) {
                    engine::Command a(2);
                    a.setPriority(state.getPokemon(pokemon_opt1).getAttack(attacks_opt[i1]).getStatsAttack().priority);
                    a.setPokemon(pokemon_opt1);
                    a.setPokemon_target(targets_opt[i1]);
                    a.setAttack(attacks_opt[i1]);
                    e.addCommand(a);
                    cout << "2";
                    if(++r==rmax) return;
                }
                else {
                    engine::Command c(1);
                    target = pokemon_opt1;
                    int pokemon;
                    if (damages_opt[0]>damages_opt[1] || find(pokemon_done.begin(), pokemon_done.end(), player*6)!=pokemon_done.end()) pokemon = 1+player*6;
                    else pokemon = player*6;
                    c.setPriority(6);
                    c.setPokemon(pokemon);
                    c.setPokemon_target(target);
                    e.addCommand(c);
                    cout<<"3";
                    if(++r==rmax) return;
                }
            }cout <<"i1"<<i1<<endl;
            i2 = max2(damages_opt,6,i1);cout<<"i2"<<i2<<endl;
            int pokemon_opt2 = -1;
            if (i2!=-1) pokemon_opt2 = i2 + player*6;
            
            if ( (pokemon_opt2==6*player && state.getPokemon(pokemon_opt2).getPV()!=0) || (pokemon_opt2==1+6*player && state.getPokemon(pokemon_opt2).getPV()!=0) ) {
                engine::Command a(2);
                a.setPriority(state.getPokemon(pokemon_opt2).getAttack(attacks_opt[i2]).getStatsAttack().priority);
                a.setPokemon(pokemon_opt2);
                a.setPokemon_target(targets_opt[i2]);
                a.setAttack(attacks_opt[i2]);
                e.addCommand(a);
                cout<<"4";
                if(r==rmax) return;
            }
            else if (pokemon_opt2!=-1) {
                engine::Command c(1);
                target = pokemon_opt2;
                int pokemon;
                if (damages_opt[0]>damages_opt[1] || find(pokemon_done.begin(), pokemon_done.end(), player*6)!=pokemon_done.end()) pokemon = 1+player*6;
                else pokemon = player*6;
                c.setPriority(6);
                c.setPokemon(pokemon);
                c.setPokemon_target(target);
                e.addCommand(c);
                cout<<"5";
                if(r==rmax) return;
            }
            
    }

    void DeepAI::opt(state::State& state, int damages_opt[], int attacks_opt[], int targets_opt[], int player, std::vector<int> pokemon_done, std::vector<int> target_done) {
        int d;
        for (int pokemon=player*6; pokemon<player*6+6; pokemon++) {
            if (state.getPokemon(pokemon).getPV() != 0 && find(pokemon_done.begin(), pokemon_done.end(), pokemon)==pokemon_done.end()) {
                int d_max = 0;
                int attack_opt = 0;
                int target_opt = 0;
                for (int attack=0; attack<4; attack++) {
                    if (state.getPokemon(pokemon).getAttack(attack).getPP()!=0) {
                        int player_target = 1-player;
                        for (int target=player_target*6; target<2+player_target*6; target++) {
                            if (state.getPokemon(target).getPV()!=0 && find(target_done.begin(), target_done.end(), target)==target_done.end()) {
                                engine::AttackCommand ac(pokemon, target, attack);
                                int d=ac.damage(state);
                                //cout << state.getPokemon(pokemon).getName() << d << endl;
                                if (d > d_max) {
                                    d_max = d;
                                    attack_opt = attack;
                                    target_opt = target;
                                }
                            }
                        }
                    }
                }
                damages_opt[pokemon-6*player]=d_max;
                attacks_opt[pokemon-6*player]=attack_opt;
                targets_opt[pokemon-6*player]=target_opt;
            }
            else if (find(pokemon_done.begin(), pokemon_done.end(), pokemon)==pokemon_done.end()) {
                damages_opt[pokemon-6*player]=0;
                attacks_opt[pokemon-6*player]=0;
                targets_opt[pokemon-6*player]=0;
            }
        }
        cout << damages_opt[0] <<" " << damages_opt[1] <<" " <<damages_opt[2]<<" "  <<damages_opt[3]<<" "  <<damages_opt[4]<<" "  <<damages_opt[5] << endl;
        if (pokemon_done.size()>0) cout <<"done"<< pokemon_done[0] << endl;
        if (pokemon_done.size()>1) cout <<"done"<< pokemon_done[1] << endl;
    }
    
    int DeepAI::change(state::State& state, int player) {
        int d;
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
                                d = ac.damage(state);
                                if (d > d_max) {
                                    d_max = d;
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

    int DeepAI::max(int tab[], int size) {
        int max=tab[0], i_max=0;
        int i=1;
        if (tab[i]>max) {
            max =tab[i];
            i_max = i;
        }
        for (int i=2; i<size; i++) {
            if (tab[i]>2*max) {
                max =tab[i];
                i_max = i;
            }
        }
        return i_max;
    }

    int DeepAI::max2(int tab[], int size, int i_max) {
        int i_max2=-1, max2=0;
        for (int i=0; i<2; i++) {
            if (tab[i]>max2 && i!=i_max) {
                max2 =tab[i];
                i_max2 = i;
            }
        }
        for (int i=2; i<size; i++) {
            if (tab[i]>2*max2 && i!=i_max) {
                max2 =tab[i];
                i_max2 = i;
            }
        }
        return i_max2;
    }

    int DeepAI::check_pv(engine::Engine& e, sf::RenderWindow& window, int player) {
        if (e.getState().getPokemon(2+6*player).getPV()==0 && e.getState().getPokemon(3+6*player).getPV()==0 && e.getState().getPokemon(4+6*player).getPV()==0 && e.getState().getPokemon(5+6*player).getPV()==0) { 
            if (e.getState().getPokemon(6*player).getPV()==0 && e.getState().getPokemon(1+6*player).getPV()==0) {
                if (player==1) cout << "IA a perdu" << endl;
                else cout << "IA joueur a perdu" << endl;
                window.close();
                return 1;
            }
            if (e.getState().getPokemon(6*player).getPV()==0 || e.getState().getPokemon(1+6*player).getPV()==0) rmax = 1;
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
                    c.execute(e.getState());
                    e.setPastCommands(c);
                }
            }
            return 0;
        }
    }

    
       
}
/*
    void DeepAI::max(state::State& state) {
        int d = 0;
        int attack, target;
        for (int pokemon=6; pokemon<11; pokemon++) {
            int attack_opt = 0;
            int target_opt = 0;
            int d_max = 0;
            for (attack=0; attack<4; attack++) {
                if (state.getPokemon(pokemon).getAttack(attack).getPP()!=0) {
                    for (target=0; target<2; target++) {
                        d = damage(state.getPokemon(pokemon).getAttack(attack), state.getPokemon(pokemon), state.getPokemon(target));
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
            
            if (state.getPokemon(pokemon).getAttack(0).getPP()==0 && state.getPokemon(pokemon).getAttack(1).getPP()==0 && state.getPokemon(pokemon).getAttack(2).getPP()==0 && state.getPokemon(pokemon).getAttack(3).getPP()==0) {
                engine::Command c(1);
                target = 8;
                while (state.getPokemon(target).getPV()==0) {
                    if (target<12) target++;
                    else break;
                }
                c.setPriority(6);
                c.setPokemon(pokemon);
                c.setPokemon_target(target);
                e.addCommand(c, state); 
            }
            engine::Command a(2);
            a.setPriority(state.getPokemon(pokemon).getAttack(attack_opt).getStatsAttack().priority);
            a.setPokemon(pokemon);
            a.setPokemon_target(target_opt);
            a.setAttack(attack_opt);
            e.addCommand(a, state);
        }  
        */ 




