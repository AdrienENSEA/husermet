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
            stats_pokemon = {404, 399, 379, 299, 279, 279};
            pokemon = new Pokemon(GROUDON, "Groudon", none, SEISME, TONNERRE, TELLURIFORCE, DEFLAGRATION, 1, types, NONE_S, stats_pokemon, 0, stats_pokemon.pv);
            break;
        case KYOGRE :
            types.push_back(WATER);
            stats_pokemon = {404, 399, 379, 299, 279, 279};
            pokemon = new Pokemon(KYOGRE, "Kyogre", none, EBULLITION, TONNERRE, LASER_GLACE, HYDROCANON, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case RAYQUAZA :
            types.push_back(DRAGON);
            stats_pokemon = {414, 399, 279, 399, 279, 289};
            pokemon = new Pokemon(RAYQUAZA, "Rayquaza", none, TONNERRE, DRACO_METEORE, DEFLAGRATION, LASER_GLACE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case LEVEINARD :
            types.push_back(NORMAL);
            stats_pokemon = {704, 109, 109, 169, 309, 199};
            pokemon = new Pokemon(LEVEINARD, "Leveinard", none, E_COQUE, ABRI, TOXIK, TONNERRE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case ECTOPLASMA : 
            types.push_back(GHOST);
            types.push_back(POISON);
            stats_pokemon = {324, 229, 219, 359, 249, 319};
            pokemon = new Pokemon(ECTOPLASMA, "Ectoplasma", none, FEU_FOLLET, CRADOVAGUE, BALL_OMBRE, EXPLOFORCE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case STAROSS :
            types.push_back(WATER);
            types.push_back(PSY);
            stats_pokemon = {324, 249, 269, 299, 269, 329};
            pokemon = new Pokemon(STAROSS, "Staross", none, HYDROCANON, TONNERRE, EBULLITION, LASER_GLACE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case NOACIER :
            types.push_back(STEEL);
            types.push_back(GRASS);
            stats_pokemon = {352, 287, 361, 207, 331, 139};
            pokemon = new Pokemon(NOACIER, "Noacier", none, LAME_FEUILLE, MEGAFOUET, LUMINOCANON, TELLURIFORCE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case HEATRAN :
            types.push_back(STEEL);
            types.push_back(FIRE);
            stats_pokemon = {386, 279, 311, 359, 311, 253};
            pokemon = new Pokemon(HEATRAN, "Heatran", none, DEFLAGRATION, FRAPPE_ATLAS, LUMINOCANON, TELLURIFORCE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        default:
            types.push_back(STEEL);
            types.push_back(FIRE);
            stats_pokemon = {386, 279, 311, 359, 311, 253};
            pokemon = new Pokemon(HEATRAN, "Heatran", none, DEFLAGRATION, FRAPPE_ATLAS, LUMINOCANON, TELLURIFORCE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
    }

    return *pokemon;

}

}
