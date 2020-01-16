#include "AttackCommand.h"
#include <unistd.h>
#include <iostream>

#define LEVEL 100

namespace engine {

    AttackCommand::AttackCommand (int pokemon, int pokemon_target, int attack) {
        this->pokemon = pokemon;
        this->pokemon_target = pokemon_target;
        this->attack = attack;
    }
    
    void AttackCommand::execute (state::State& state) {
        state::Pokemon p = state.getPokemon(pokemon);
        state::Pokemon p_t = state.getPokemon(pokemon_target);
        state::Attack a = state.getPokemon(pokemon).getAttack(attack);
        int d = damage(state);

        state.getPokemon(pokemon).getAttack(attack).modifPP(-1);
        state.getPokemon(pokemon_target).modifPV(-d);
        if (pokemon<6) std::cout << p.getName() << " attaque " << a.getName() << " sur " << p_t.getName() << " ennemi " << std::endl;
        if (pokemon>5) std::cout << p.getName() << " ennemi attaque " << a.getName() << " sur " << p_t.getName() << std::endl;
    }
    
    int AttackCommand::damage(state::State &state) {
        int d = 0;
        float level, power, att, def, coeff, r, cc, coeff_stab, sw_type;
        level = LEVEL*2/5+2;
        power = state.getPokemon(pokemon).getAttack(attack).getStatsAttack().power*state.getPokemon(pokemon).getAbility();
        sw_type = sw(state.getPokemon(pokemon).getAttack(attack).getType(),state.getPokemon(pokemon_target).getType()); // 0.5 si resistance + 1.5 si faiblesse
        coeff_stab = stab(state.getPokemon(pokemon).getAttack(attack).getType(),state.getPokemon(pokemon).getType());
        srand (time(NULL));
        r = (float)(rand()%38+217)/255;
        cc = crit();
        if (state.getPokemon(pokemon).getAttack(attack).getStatsAttack().category == 1) {
            //std::cout << "attaque physique" << std::endl;
            att = state.getPokemon(pokemon).getStats().attack;
            coeff = burn(state.getPokemon(pokemon).getState())*tvt(state.getPokemon(pokemon).getAttack(attack).getStatsAttack().scope)*weather(state.getPokemon(pokemon).getAttack(attack).getType(),state.getTypeWeather())*terrain(state.getPokemon(pokemon).getAttack(attack).getType(),state.getTypeTerrain());
            def = state.getPokemon(pokemon_target).getStats().defense;
            d = (level*power*att/50/def*coeff+2)*cc*r*coeff_stab*sw_type;
            //std::cout <<"level" << level << "power" << power << "att" << att << "def"<<def<<"coeff"<<coeff<<"cc"<<cc<<"r"<<r<<"coefstat"<<coeff_stab<<"sw"<<sw_type<<std::endl ;
            return d;
        }
        else if (state.getPokemon(pokemon).getAttack(attack).getStatsAttack().category == 2) {
            //std::cout << "attaque spéciale" << std::endl;
            att = state.getPokemon(pokemon).getStats().sp_attack;
            coeff = tvt(state.getPokemon(pokemon).getAttack(attack).getStatsAttack().scope)*weather(state.getPokemon(pokemon).getAttack(attack).getType(),state.getTypeWeather())*terrain(state.getPokemon(pokemon).getAttack(attack).getType(),state.getTypeTerrain());
            def = state.getPokemon(pokemon_target).getStats().sp_defense;
            d = (level*power*att/50/def*coeff+2)*cc*r*coeff_stab*sw_type;
            return d;
        }
        else if (state.getPokemon(pokemon).getAttack(attack).getStatsAttack().category == 3) {
            //std::cout << "attaque de statut" << std::endl;
            return d;
        }
        return 0;
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

    float AttackCommand::burn(state::TypeState state) {
        if (state==state::BURNED) return 0.5;
        return 1;
    }

    float AttackCommand::tvt(int scope) {
        if (scope == 2) return 0.75;
        return 1;
    }

    float AttackCommand::weather(state::Type type, state::TypeWeather weather) {
        switch (weather) {
            case state::TypeWeather::RAIN:
                if (type==state::Type::WATER) return 1.5;
                if (type==state::Type::FIRE) return 0.5;
                break;
            case state::TypeWeather::SUN:
                if (type==state::Type::WATER) return 0.5;
                if (type==state::Type::FIRE) return 1.5;
                if (type==state::Type::GRASS) return 1.5;
                break;
            case state::TypeWeather::SNOW:
                if (type==state::Type::ICE) return 1.5;
                break;
            case state::TypeWeather::FOG:
                if (type==state::Type::NORMAL) return 1.5;
                break;
            case state::TypeWeather::SAND:
                if (type==state::Type::GROUND) return 1.5;
                if (type==state::Type::ROCK) return 1.5;
                break;
            case state::TypeWeather::WIND:
                if (type==state::Type::DRAGON) return 1.5;
                if (type==state::Type::FLY) return 1.5;
                if (type==state::Type::BUG) return 0.5;
                break;
            default:
                break;
        }
        
        return 1;
    }

    float AttackCommand::terrain(state::Type type, state::TypeTerrain terrain) {
        switch (terrain) {
            case state::TypeTerrain::GRASSY :
                if (type==state::Type::GRASS) return 1.5;
                if (type==state::Type::BUG) return 1.5;
                if (type==state::Type::GROUND) return 0.5;
                break;
            case state::TypeTerrain::ELECTRIK :
                if (type==state::Type::ELECTRIC) return 1.5;
                break;
            case state::TypeTerrain::PSYCHIC :
                if (type==state::Type::PSY) return 1.5;
                break;
            case state::TypeTerrain::MISTY :
                if (type==state::Type::FAIRY) return 1.5;
                if (type==state::Type::DRAGON) return 0.5;
                break;
            default:
                break;
        }
        return 1;
    }

    int AttackCommand::crit() {
        srand(time(NULL));
        int r=rand()%24;
        if (r==3) return 2;
        return 1;
    }
// Setters and Getters

};
