#include "ChangePokemonCommand.h"
#include <iostream>

namespace engine {

    ChangePokemonCommand::ChangePokemonCommand () {
        priority = 6;
        commandID = 1;
    }
    void ChangePokemonCommand::execute (state::State* state) {
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
    }


};
