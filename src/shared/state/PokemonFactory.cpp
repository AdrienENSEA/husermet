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
            pokemon = new Pokemon(GROUDON, "Groudon", none, FRAPPE_ATLAS, TONNERRE, TELLURIFORCE, DEFLAGRATION, 1, types, NONE_S, stats_pokemon, 0, 100);
            break;
        case KYOGRE :
            types.push_back(WATER);
            stats_pokemon = {100, 100, 90, 150, 140, 100};
            pokemon = new Pokemon(KYOGRE, "Kyogre", none, EBULLITION, TONNERRE, LASER_GLACE, HYDROCANON, 1, types, NONE_S, stats_pokemon, 0,100);
            break;
        case RAYQUAZA :
            types.push_back(DRAGON);
            stats_pokemon = {100, 100, 90, 150, 140, 90};
            pokemon = new Pokemon(RAYQUAZA, "Rayquaza", none, TONNERRE, DRACO_METEORE, DEFLAGRATION, LASER_GLACE, 1, types, NONE_S, stats_pokemon, 0,100);
            break;
        case LEVEINARD :
            types.push_back(NORMAL);
            stats_pokemon = {100, 100, 90, 150, 140, 90};
            pokemon = new Pokemon(LEVEINARD, "Leveinard", none, E_COQUE, ABRI, TOXIK, TONNERRE, 1, types, NONE_S, stats_pokemon, 0,100);
            break;
        case ECTOPLASMA :
            break;
        case STAROSS :
            types.push_back(WATER);
            types.push_back(PSY);
            stats_pokemon = {60, 75, 85, 100, 85, 115};
            pokemon = new Pokemon(STAROSS, "Staross", none, HYDROCANON, TONNERRE, EBULLITION, LASER_GLACE, 1, types, NONE_S, stats_pokemon, 0,60);
            break;
        case GARDEVOIR :
            break;
        case NOACIER :
            types.push_back(STEEL);
            types.push_back(GRASS);
            stats_pokemon = {74, 94, 131, 54, 116, 20};
            pokemon = new Pokemon(NOACIER, "Noacier", none, LAME_FEUILLE, MEGAFOUET, LUMINOCANON, TELLURIFORCE, 1, types, NONE_S, stats_pokemon, 0,74);
            break;
        case HEATRAN :
            types.push_back(STEEL);
            types.push_back(FIRE);
            stats_pokemon = {91, 90, 106, 130, 106, 77};
            pokemon = new Pokemon(HEATRAN, "Heatran", none, DEFLAGRATION, FRAPPE_ATLAS, LUMINOCANON, TELLURIFORCE, 1, types, NONE_S, stats_pokemon, 0,91);
            break;
        default:
            break;
    }

    return *pokemon;

}

}
