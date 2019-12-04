#include "HeuristicAI.h"
#include <iostream>
#include <unistd.h>

using namespace std;

namespace ai {

    void HeuristicAI::run(engine::Engine& e, state::State& state) {
        int d = 0;
        int attack, target;
        for (int pokemon=6; pokemon<8; pokemon++) {
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
    }



    int HeuristicAI::change(state::State& state) {
        int d;
        //int attack_opt = 0;
        //int target_opt = 0;
        int d_max = 0;
        int pokemon_opt = 8;
        for (int pokemon=8; pokemon<12; pokemon++) {
            if (state.getPokemon(pokemon).getPV()!=0) {
                for (int attack=0; attack<4; attack++) {
                    if (state.getPokemon(pokemon).getAttack(attack).getPP()!=0) {
                        for (int target=0; target<2; target++) {
                            if (state.getPokemon(target).getPV()!=0) {
                                d = damage(state.getPokemon(pokemon).getAttack(attack), state.getPokemon(pokemon), state.getPokemon(target));
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

    int HeuristicAI::damage(state::Attack& attack, state::Pokemon& pokemon, state::Pokemon& target) {
        int d = 0;
        if (attack.getStatsAttack().category == 1) {
            //std::cout << "attaque physique" << std::endl;
            float cm = sw(attack.getType(),target.getType()) * stab(attack.getType(),pokemon.getType()); //1.5 si STAB + 0.5 si resistance + 1.5 si faiblesse + effet objet/climat
            //std::cout << "cm" << cm << std::endl;
            d = (pokemon.getStats().attack*attack.getStatsAttack().power/target.getStats().defense/50+2)*cm;
            return d;
        }
        else if (attack.getStatsAttack().category == 2) {
            //std::cout << "attaque spéciale" << std::endl;
            float cm = sw(attack.getType(),target.getType()) * stab(attack.getType(),pokemon.getType()); //1.5 si STAB + 0.5 si resistance + 1.5 si faiblesse + effet objet/climat
            //std::cout << "cm" << cm << std::endl;
            d = (pokemon.getStats().sp_attack*attack.getStatsAttack().power/target.getStats().sp_defense/50+2)*cm;
            return d;
        }
        else if (attack.getStatsAttack().category == 3) {
            //std::cout << "attaque de statut" << std::endl;
            return d;
        }
        return 0;
    }

    float HeuristicAI::stab(state::Type a, std::vector<state::Type> p) {
        for (uint i = 0; i<p.size(); i++) {
            if (p.at(i) == a) return 1.5;
        }
        return 1;
    }
    
    float HeuristicAI::sw(state::Type at, std::vector<state::Type> df) {
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
                        //std::cout << "se" << coeff << std::endl; 
                            coeff += 0.5;
                            break;
                        case state::Type::WATER : 
                        case state::Type::GRASS : 
                        case state::Type::DRAGON :
                        //std::cout << "pe" << coeff << std::endl; 
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
        //std::cout << "coeff" << coeff << std::endl;
        return coeff;
    }
       
}

