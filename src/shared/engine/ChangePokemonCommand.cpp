#include "ChangePokemonCommand.h"
#include <iostream>


namespace engine {

    ChangePokemonCommand::ChangePokemonCommand (int pokemon, int pokemon_target) {
        this->pokemon = pokemon;
        this->pokemon_target = pokemon_target;
    }
    void ChangePokemonCommand::execute (state::State* state) {
        int player = 0;
        std::vector<int> pps = {
                state->getPokemon(pokemon_target).getAttack().at(0).getPP(),
                state->getPokemon(pokemon_target).getAttack().at(1).getPP(),
                state->getPokemon(pokemon_target).getAttack().at(2).getPP(),
                state->getPokemon(pokemon_target).getAttack().at(3).getPP()};
        state->setPPs(pps);
        //state->setPV(state->getPokemon(pokemon_target).getStats().pv);
        state->changeTeam(pokemon, pokemon_target, player);
        
        }


};
