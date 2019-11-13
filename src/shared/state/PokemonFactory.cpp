#include "PokemonFactory.h"

namespace state {

Pokemon PokemonFactory::createPokemon(IdPokemon id_pokemon) {

    Pokemon *pokemon;
    Item none = ItemFactory::createItem(NONE_I);
    std::vector <Type> types = {};
    StatsPokemon stats_pokemon;

    switch (id_pokemon) 
    {
        case GROUDON :
            types.push_back(GROUND);
            stats_pokemon = {100, 150, 140, 100, 90, 90};
            pokemon = new Pokemon(GROUDON, "Groudon", none, FRAPPE_ATLAS, E_COQUE, E_COQUE, E_COQUE, 1, types, NONE_S, stats_pokemon, 0, 100);
            break;
        case KYOGRE :
            types.push_back(WATER);
            stats_pokemon = {100, 100, 90, 150, 140, 90};
            pokemon = new Pokemon(KYOGRE, "Kyogre", none, CHANGE_ECLAIR, TOXIK, ABRI, FRAPPE_ATLAS, 1, types, NONE_S, stats_pokemon, 0,100);
            break;
        case RAYQUAZA :
            types.push_back(DRAGON);
            stats_pokemon = {100, 100, 90, 150, 140, 90};
            pokemon = new Pokemon(RAYQUAZA, "Rayquaza", none, TONNERRE, ABRI, CHANGE_ECLAIR, DANSE_PLUIE, 1, types, NONE_S, stats_pokemon, 0,100);
            break;
        case LEVEINARD :
            types.push_back(NORMAL);
            stats_pokemon = {100, 100, 90, 150, 140, 90};
            pokemon = new Pokemon(LEVEINARD, "Leveinard", none, E_COQUE, E_COQUE, E_COQUE, E_COQUE, 1, types, NONE_S, stats_pokemon, 0,100);
            break;
        case ECTOPLASMA :
            break;
        case STAROSS :
            break;
        case GARDEVOIR :
            break;
        default:
            break;
    }

    return *pokemon;

}

}
