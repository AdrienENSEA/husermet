#include "ChangePokemonCommand.h"
#include <iostream>


namespace engine {

    ChangePokemonCommand::ChangePokemonCommand (int pokemon, int pokemon_target) {
        this->pokemon = pokemon;
        this->pokemon_target = pokemon_target;
    }
    void ChangePokemonCommand::execute (state::State& state) {
        int player = 0;
        state.changeTeam(pokemon, pokemon_target, player);
        std::cout << "changement de pokémon" << std::endl;
        }


};
