#include "Command.h"

namespace engine {

    Command::Command () {
    }
    void Command::execute (state::State& state) {
    }

    // Setters and Getters
    const Command::Pokemon& getPokemon() const {
        return pokemon;
    }
    void Command::setPokemon(const Pokemon& pokemon) {
        this->pokemon = pokemon;
    }
    const Command::Pokemon& getPokemon_target() const {
        return pokemon_target;
    }
    void Command::setPokemon_target(const Pokemon& pokemon_target) {
        this->pokemon_target = pokemon_target;
    }
    int Command::getPriority() const {
        return priority;
    }
    void Command::setPriority(int priority) {
        this->priority = priority;
    }

};
