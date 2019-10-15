#include "PokemonFactory.h"

namespace state {

PokemonFactory::PokemonFactory() {

}

Pokemon createPokemon(IdPokemon id_pokemon) {

    Pokemon pokemon;
    Object none(NONE_O, "", "", effect_stats, NORMAL, NONE);
    std::vector <Attack> attacks = {};

    switch (id_pokemon) 
    {
        case GROUDON :
            std::vector <Type> types = {FIRE}; //SOL
            StatsPokemon stats_pokemon = {100, 150, 140, 100, 90, 90};
            pokemon = new Pokemon groudon(GROUDON, "Groudon", none, attacks, 1, types, NORMAL, stats_pokemon, 0);
            break;
        case KYOGRE :
            break;
        case RAYQUAZA :
            break;
        case LEVEINARD :
            break;
        case VOLTORBE :
            break;
        case ECTOPLASMA :
            break;
        case LEVIATHAN :
            break;
        case STAROSS :
            break;
        case GARDEVOIR :
            break;


}


}
