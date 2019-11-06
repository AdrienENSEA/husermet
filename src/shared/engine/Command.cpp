#include "Command.h"
#include <iostream>

namespace engine {

    Command::Command () {
        state::Pokemon pokemon;
        state::Pokemon pokemon_target;
        priority = 0;
    }

    void Command::execute (state::State* state) {
        if (commandID == 1) {
        int fighter;
        int back;
        for (int i =0; i<12; i++) {
            if (state->getPokemon(i).getID() == pokemon.getID() ) {
                fighter = i;
            }
            if (state->getPokemon(i).getID() == pokemon_target.getID() ) {
                back = i;
            }
        }
        int player = 0;
        state->changeTeam(fighter, back, player);
        std::vector<int> pps = {
            state->getPokemon(0).getAttack().at(0).getStatsAttack().pp, 
            state->getPokemon(0).getAttack().at(1).getStatsAttack().pp, 
            state->getPokemon(0).getAttack().at(2).getStatsAttack().pp, 
            state->getPokemon(0).getAttack().at(3).getStatsAttack().pp  };
        state->setPPs(pps);
        }

        if (commandID == 2) {
            std::vector<int> pps = {
            state->getPokemon(0).getAttack().at(0).getStatsAttack().pp-1, 
            state->getPokemon(0).getAttack().at(1).getStatsAttack().pp, 
            state->getPokemon(0).getAttack().at(2).getStatsAttack().pp, 
            state->getPokemon(0).getAttack().at(3).getStatsAttack().pp  };
        state->setPPs(pps);
        }
    }

    // Setters and Getters
    const state::Pokemon& Command::getPokemon() const {
        return pokemon;
    }
    void Command::setPokemon(const state::Pokemon& pokemon) {
        this->pokemon = pokemon;
    }
    const state::Pokemon& Command::getPokemon_target() const {
        return pokemon_target;
    }
    void Command::setPokemon_target(const state::Pokemon& pokemon_target) {
        this->pokemon_target = pokemon_target;
    }
    int Command::getPriority() const {
        return priority;
    }
    void Command::setPriority(int priority) {
        this->priority = priority;
    }


};
