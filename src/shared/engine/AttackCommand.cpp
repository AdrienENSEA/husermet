#include "AttackCommand.h"
#include <unistd.h>
#include <iostream>


namespace engine {

    AttackCommand::AttackCommand (int pokemon, int pokemon_target, int attack) {
        this->pokemon = pokemon;
        this->pokemon_target = pokemon_target;
        this->attack = attack;
        
    }
    
    void AttackCommand::execute (state::State* state) {
        state::Pokemon p = state->getPokemon(pokemon);
        state::Pokemon p_t = state->getPokemon(pokemon_target);
        state::Attack a = state->getPokemon(pokemon).getAttack().at(attack);
        int d = damage(state);

        a.modifPP(-1);
        state->modifPP(-1,attack);
        std::cout << "pp"<<a.getPP() << std::endl;

        std::cout << "avant pv"<<p.getPV() << std::endl;
        int pv = p.getPV()-d;
        state->modifPV(-d);
        p.setPV(pv);
        std::cout << "apres pv"<<p.getPV() << std::endl;
    }
    
    int AttackCommand::damage(state::State* state) {
        int d = 0;
        float cm = sw(state->getPokemon(pokemon).getAttack().at(attack).getType(),state->getPokemon(pokemon_target).getType()) * stab(state->getPokemon(pokemon).getAttack().at(attack).getType(),state->getPokemon(pokemon).getType() ); //1.5 si STAB + 0.5 si resistance + 1.5 si faiblesse + effet objet/climat
        //std::cout << "cm" << cm << std::endl;
        d = (state->getPokemon(pokemon).getStats().attack*state->getPokemon(pokemon).getAttack().at(attack).getStatsAttack().power/state->getPokemon(pokemon_target).getStats().defense/50+2)*cm;
        return d;
    }
    
    float AttackCommand::stab(state::Type a, std::vector<state::Type> p) {
        for (uint i = 0; i<p.size(); i++) {
            if (p.at(i) == a) return 1.5;
        }
        return 1;
    }
    
    float AttackCommand::sw(state::Type at, std::vector<state::Type> df) {
        float coeff = 1;
        bool im = false;
        switch (at) {
            case state::Type::FIRE :
            std::cout << "feu"<< std::endl;
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
            std::cout << "eau"<< std::endl;
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
            std::cout << "plante" << std::endl;
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
                std::cout << "elec" << std::endl;
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
// Setters and Getters

};
