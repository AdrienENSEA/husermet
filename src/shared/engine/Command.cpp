#include "Command.h"

namespace engine {

    Command::Command () {
        state::Pokemon pokemon;
        state::Pokemon pokemon_target;
        priority = 0;
    }
    void Command::execute (state::State& state) {
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
