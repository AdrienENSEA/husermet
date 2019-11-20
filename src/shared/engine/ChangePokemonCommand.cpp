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
        if (pokemon<6) std::cout << state.getPokemon(pokemon).getName() << " échange avec " << state.getPokemon(pokemon_target).getName() << std::endl;
        if (pokemon>5) std::cout << state.getPokemon(pokemon).getName() << " ennemi échange avec " << state.getPokemon(pokemon_target).getName() << " ennemi" << std::endl;
        }


};
