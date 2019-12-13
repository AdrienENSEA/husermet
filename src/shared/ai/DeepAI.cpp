#include "DeepAI.h"
#include <iostream>
#include <unistd.h>

using namespace std;
int rmax=2;
namespace ai {
    void DeepAI::run(engine::Engine& e, state::State& state, sf::RenderWindow& window, int player) {
        int target_done = -1, pokemon_done = -1;
        int target;
        int r=0;
        if (check_pv(state, window, player)==0) {

            int damages_opt[6];
            int attacks_opt[6];
            int targets_opt[6];
            int i1=-1, i2;

            for (int pokemon=6*player; pokemon<2+6*player;pokemon++) {
                if (state.getPokemon(pokemon).getPV()!=0 && pokemon!=pokemon_done) {
                    for (int attack=0; attack<4; attack++) {
                        if (state.getPokemon(pokemon).getAttack(attack).getPP()!=0) {
                            for (int target=6*(1-player); target<2+6*(1-player);target++){
                                if (state.getPokemon(target).getPV()!=0 && target!=target_done) {
                                    int d=damage(state.getPokemon(pokemon).getAttack(attack), state.getPokemon(pokemon), state.getPokemon(target));
                                    if (d >=state.getPokemon(target).getPV()) {
                                        int other_p = 6*player+1-pokemon+6*player;
                                        if (state.getPokemon(pokemon).getStats().speed>state.getPokemon(other_p).getStats().speed) {
                                            engine::Command a(2);
                                            a.setPriority(state.getPokemon(pokemon).getAttack(attack).getStatsAttack().priority);
                                            a.setPokemon(pokemon);
                                            a.setPokemon_target(target);
                                            a.setAttack(attack);
                                            e.addCommand(a, state);
                                            damages_opt[pokemon-6*player] = d;
                                            attacks_opt[pokemon-6*player] = attack;
                                            targets_opt[pokemon-6*player] = target;
                                            target_done = target;
                                            pokemon_done = pokemon;
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
                if ( (pokemon_opt1==6*player && state.getPokemon(6*player).getPV()!=0) || (pokemon_opt1==1+6*player && state.getPokemon(1+6*player).getPV()!=0) ) {
                    engine::Command a(2);
                    a.setPriority(state.getPokemon(pokemon_opt1).getAttack(attacks_opt[i1]).getStatsAttack().priority);
                    a.setPokemon(pokemon_opt1);
                    a.setPokemon_target(targets_opt[i1]);
                    a.setAttack(attacks_opt[i1]);
                    e.addCommand(a, state);
                    if(++r==rmax) return;
                }
                else {
                    engine::Command c(1);
                    target = pokemon_opt1;
                    int pokemon;
                    if (damages_opt[0]>damages_opt[1]) pokemon = 1+player*6;
                    else pokemon = player*6;
                    c.setPriority(6);
                    c.setPokemon(pokemon);
                    c.setPokemon_target(target);
                    e.addCommand(c, state);
                    if(++r==rmax) return;
                }
            }
            i2 = max2(damages_opt,6,i1);
            int pokemon_opt2 = -1;
            if (i2!=-1) pokemon_opt2 = i2 + player*6;
            
            if ( (pokemon_opt2==6*player && state.getPokemon(6*player).getPV()!=0) || (pokemon_opt2==1+6*player && state.getPokemon(1+6*player).getPV()!=0) ) {
                engine::Command a(2);
                a.setPriority(state.getPokemon(pokemon_opt2).getAttack(attacks_opt[i2]).getStatsAttack().priority);
                a.setPokemon(pokemon_opt2);
                a.setPokemon_target(targets_opt[i2]);
                a.setAttack(attacks_opt[i2]);
                e.addCommand(a, state);
                if(r==rmax) return;
            }
            else if (pokemon_opt2!=-1) {
                engine::Command c(1);
                target = pokemon_opt2;
                int pokemon;
                if (damages_opt[0]>damages_opt[1]) pokemon = 1+player*6;
                else pokemon = player*6;
                c.setPriority(6);
                c.setPokemon(pokemon);
                c.setPokemon_target(target);
                e.addCommand(c, state);
                if(r==rmax) return;
            }
        }     
    }

    void DeepAI::opt(state::State& state, int damages_opt[], int attacks_opt[], int targets_opt[], int player, int pokemon_done, int target_done) {
        int d;
        for (int pokemon=player*6; pokemon<player*6+6; pokemon++) {
            if (state.getPokemon(pokemon).getPV() != 0 && pokemon!=pokemon_done) {
                int d_max = 0;
                int attack_opt = 0;
                int target_opt = 0;
                for (int attack=0; attack<4; attack++) {
                    if (state.getPokemon(pokemon).getAttack(attack).getPP()!=0) {
                        int player_target = 1-player;
                        for (int target=player_target*6; target<2+player_target*6; target++) {
                            if (state.getPokemon(target).getPV()!=0 && target!=target_done) {
                                d = damage(state.getPokemon(pokemon).getAttack(attack), state.getPokemon(pokemon), state.getPokemon(target));
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
            else if (pokemon!=pokemon_done) {
                damages_opt[pokemon-6*player]=0;
                attacks_opt[pokemon-6*player]=0;
                targets_opt[pokemon-6*player]=0;
            }
        }
    }
    int DeepAI::damage(state::Attack& attack, state::Pokemon& pokemon, state::Pokemon& target) {
        int d = 0;
        if (attack.getStatsAttack().category == 1) {
            float cm = 5*sw(attack.getType(),target.getType()) * stab(attack.getType(),pokemon.getType()); //1.5 si STAB + 0.5 si resistance + 1.5 si faiblesse + effet objet/climat
            d = (pokemon.getStats().attack*attack.getStatsAttack().power/target.getStats().defense/50+2)*cm;
            return d;
        }
        else if (attack.getStatsAttack().category == 2) {
            float cm = 5*sw(attack.getType(),target.getType()) * stab(attack.getType(),pokemon.getType()); //1.5 si STAB + 0.5 si resistance + 1.5 si faiblesse + effet objet/climat
            d = (pokemon.getStats().sp_attack*attack.getStatsAttack().power/target.getStats().sp_defense/50+2)*cm;
            return d;
        }
        else if (attack.getStatsAttack().category == 3) {
            return d;
        }
        return 0;
    }

    float DeepAI::stab(state::Type a, std::vector<state::Type> p) {
        for (uint i = 0; i<p.size(); i++) {
            if (p.at(i) == a) return 1.5;
        }
        return 1;
    }
    
    float DeepAI::sw(state::Type at, std::vector<state::Type> df) {
        float coeff = 1;
        bool im = false;
        switch (at) {
            case state::Type::FIRE :
                for (uint i =0 ; i<df.size(); i++ ){
                    switch (df.at(i)) {
                        case state::Type::GRASS : 
                        case state::Type::ICE : 
                        case state::Type::STEEL : 
                        case state::Type::BUG : 
                            coeff += 0.5;
                            break;
                        case state::Type::FIRE : 
                        case state::Type::WATER : 
                        case state::Type::DRAGON : 
                        case state::Type::ROCK :
                            coeff -= 0.5;
                            break;
                        default : break;
                    }
                }
                break;
            case state::Type::WATER :
                for (uint i =0 ; i<df.size(); i++ ){
                    switch (df.at(i)) {
                        case state::Type::FIRE : 
                        case state::Type::ROCK : 
                        case state::Type::GROUND :
                            coeff += 0.5;
                            break;
                        case state::Type::WATER : 
                        case state::Type::GRASS : 
                        case state::Type::DRAGON :
                            coeff -= 0.5;
                            break;
                        default : break;
                    }
                }
                break;
            case state::Type::GRASS :
                for (uint i =0 ; i<df.size(); i++ ){
                    switch (df.at(i)) {
                        case state::Type::WATER : 
                        case state::Type::ROCK : 
                        case state::Type::GROUND : 
                            coeff += 0.5;
                            break;
                        case state::Type::FIRE : 
                        case state::Type::GRASS : 
                        case state::Type::DRAGON : 
                        case state::Type::STEEL :
                        case state::Type::BUG :
                        case state::Type::POISON : 
                        case state::Type::FLY :
                            coeff -= 0.5;
                            break;
                        default : break;
                    }
                }
                break;
            case state::Type::ELECTRIC:
                for (uint i =0 ; i<df.size(); i++ ){
                    switch (df.at(i)) {
                        case state::Type::WATER : 
                        case state::Type::FLY : 
                            coeff += 0.5;
                            break;
                        case state::Type::GRASS : 
                        case state::Type::ELECTRIC : 
                        case state::Type::DRAGON :
                            coeff -= 0.5;
                            break;
                        case state::Type::GROUND :
                            im = true;
                            break;
                        default : break;
                    }
                }
                break;
            default:
                break;
        }
        if (im) coeff = 0;
        return coeff;
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
                                d = damage(state.getPokemon(pokemon).getAttack(attack), state.getPokemon(pokemon), state.getPokemon(target));
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

    int DeepAI::check_pv(state::State& state, sf::RenderWindow& window, int player) {
        if (state.getPokemon(2+6*player).getPV()==0 && state.getPokemon(3+6*player).getPV()==0 && state.getPokemon(4+6*player).getPV()==0 && state.getPokemon(5+6*player).getPV()==0) { 
            if (state.getPokemon(6*player).getPV()==0 && state.getPokemon(1+6*player).getPV()==0) {
                if (player==1) cout << "IA a perdu" << endl;
                else cout << "IA joueur a perdu" << endl;
                window.close();
                return 1;
            }
            if (state.getPokemon(6*player).getPV()==0 || state.getPokemon(1+6*player).getPV()==0) rmax = 1;
            return 0;
        }
        else {
            int target;
            std::vector<int> order = {};
            for (int i=0; i<2; i++) {
                if (state.getPokemon(6*player+i).getPV()==0) {
                    if (player) cout << state.getPokemon(6*player+i).getName() << " ennemi est KO" << endl;
                    if (!player) cout << state.getPokemon(6*player+i).getName() << " est KO" << endl;
                    engine::Engine engine;
                    engine::Command c(1);
                    target = change(state, player);
                    c.setPriority(6);
                    c.setPokemon(6*player+i);
                    c.setPokemon_target(target);
                    engine.addCommand(c, state); 
                    engine.runCommands(state,order);
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




