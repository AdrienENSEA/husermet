#include "Command.h"
#include <iostream>

namespace engine {

    Command::Command (int commandID) : commandID(commandID) {

    }

    void Command::execute (state::State& state) {
        if (commandID==1) {
            ChangePokemonCommand c(pokemon, pokemon_target);
            c.execute(state);
        }
        if (commandID==2) {
            AttackCommand a(pokemon, pokemon_target, attack);
            a.execute(state);
        }
    }

    // Setters and Getters
    int Command::getPokemon() const {
        return pokemon;
    }
    void Command::setPokemon(int pokemon) {
        this->pokemon = pokemon;
    }
    int Command::getPokemon_target() const {
        return pokemon_target;
    }
    void Command::setPokemon_target(int pokemon_target) {
        this->pokemon_target = pokemon_target;
    }
    int Command::getAttack() const {
        return attack;
    }
    void Command::setAttack(int attack) {
        this->attack = attack;
    }
    int Command::getPriority() const {
        return priority;
    }
    void Command::setPriority(int priority) {
        this->priority = priority;
    }


};
