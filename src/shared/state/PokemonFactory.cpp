#include "PokemonFactory.h"

namespace state {

Pokemon PokemonFactory::createPokemon(IdPokemon id_pokemon) {

    Pokemon *pokemon;
    Item none = ItemFactory::createItem(NONE_I);
    std::vector <Type> types = {};
    StatsPokemon stats_pokemon;

    switch (id_pokemon) 
    {
        case LEVEINARD :
            types.push_back(NORMAL);
            stats_pokemon = {704, 109, 109, 169, 309, 199};
            pokemon = new Pokemon(LEVEINARD, "Leveinard", none, E_COQUE, ABRI, TOXIK, TONNERRE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case ELECTRODE :
            types.push_back(ELECTRIC);
            stats_pokemon = {324, 199, 239, 259, 259, 399};
            pokemon = new Pokemon(ELECTRODE, "Electrode", none, COUP_D_JUS, CHANGE_ECLAIR, DANSE_PLUIE, TONNERRE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case NOACIER :
            types.push_back(GRASS);
            types.push_back(STEEL);
            stats_pokemon = {352, 287, 361, 207, 331, 139};
            pokemon = new Pokemon(NOACIER, "Noacier", none, LUMINOCANON, MEGAFOUET, TELLURIFORCE, TONNERRE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case GALLLAME :
            types.push_back(PSY);
            types.push_back(FIGHT);
            stats_pokemon = {340, 349, 229, 229, 329, 259};
            pokemon = new Pokemon(GALLLAME, "Gallame", none, COUPE_PSYCHO, LAME_FEUILLE, CLOSE_COMBAT, VAMPIPOING, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case GARDEVOIR :
            types.push_back(PSY);
            types.push_back(FAIRY);
            stats_pokemon = {340, 229, 229, 349, 329, 259};
            pokemon = new Pokemon(GARDEVOIR, "Gardevoir", none, POUVOIR_LUNAIRE, PSYKO, BALL_OMBRE, EXPLOFORCE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case ECTOPLASMA : 
            types.push_back(GHOST);
            types.push_back(POISON);
            stats_pokemon = {324, 229, 219, 359, 249, 319};
            pokemon = new Pokemon(ECTOPLASMA, "Ectoplasma", none, FEU_FOLLET, CRADOVAGUE, BALL_OMBRE, EXPLOFORCE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case SCORVOL : 
            types.push_back(FLY);
            types.push_back(POISON);
            stats_pokemon = {354, 289, 349, 189, 249, 289};
            pokemon = new Pokemon(SCORVOL, "Scorvol", none, SEISME, DEMI_TOUR, ABRI, SABOTAGE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case GROUDON :
            types.push_back(GROUND);
            stats_pokemon = {404, 399, 379, 299, 279, 279};
            pokemon = new Pokemon(GROUDON, "Groudon", none, SEISME, TONNERRE, LAME_PANGEENNE, DEFLAGRATION, 1, types, NONE_S, stats_pokemon, 0, stats_pokemon.pv);
            break;
        case LEVIATOR : 
            types.push_back(WATER);
            types.push_back(FLY);
            stats_pokemon = {394, 349, 257, 219, 299, 261};
            pokemon = new Pokemon(LEVIATOR, "Leviator", none, CASCADE, SEISME, CROCS_GIVRE, MACHOUILLE , 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case HEATRAN :
            types.push_back(STEEL);
            types.push_back(FIRE);
            stats_pokemon = {386, 279, 311, 359, 311, 253};
            pokemon = new Pokemon(HEATRAN, "Heatran", none, DEFLAGRATION, FRAPPE_ATLAS, LUMINOCANON, TELLURIFORCE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case KYOGRE :
            types.push_back(WATER);
            stats_pokemon = {404, 399, 379, 299, 279, 279};
            pokemon = new Pokemon(KYOGRE, "Kyogre", none, EBULLITION, TONNERRE, LASER_GLACE, HYDROCANON, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case DEMETEROS :
            types.push_back(GROUND);
            types.push_back(FLY);
            stats_pokemon = {382, 349, 279, 329, 259, 301};
            pokemon = new Pokemon(DEMETEROS, "Demeteros", none, EXPLOFORCE, LAME_DE_ROC, CRADOVAGUE, TELLURIFORCE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case LATIAS :
            types.push_back(DRAGON);
            types.push_back(PSY);
            stats_pokemon = {364, 259, 279, 319, 359, 319};
            pokemon = new Pokemon(LATIAS, "Latias", none, DRACO_METEORE, CHOC_PSY, PSYKO, TONNERRE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case LATIOS :
            types.push_back(DRAGON);
            types.push_back(PSY);
            stats_pokemon = {364, 279, 259, 359, 319, 319};
            pokemon = new Pokemon(LATIOS, "Latios", none, DRACO_METEORE, CHOC_PSY, LASER_GLACE, PSYKO, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case RAYQUAZA :
            types.push_back(DRAGON);
            stats_pokemon = {414, 399, 279, 399, 279, 289};
            pokemon = new Pokemon(RAYQUAZA, "Rayquaza", none, TONNERRE, DRACO_METEORE, DEFLAGRATION, LASER_GLACE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case CRYPTERO :
            types.push_back(PSY);
            types.push_back(FLY);
            stats_pokemon = {348, 215, 259, 305, 259, 293};
            pokemon = new Pokemon(CRYPTERO, "Cryptero", none, LAME_D_AIR, LASER_GLACE, PSYKO, ATTERISSAGE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case STAROSS :
            types.push_back(WATER);
            types.push_back(PSY);
            stats_pokemon = {324, 249, 269, 299, 269, 329};
            pokemon = new Pokemon(STAROSS, "Staross", none, HYDROCANON, TONNERRE, EBULLITION, LASER_GLACE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case TYRANOCIF :
            types.push_back(DARK);
            types.push_back(ROCK);
            stats_pokemon = {404, 367, 319, 289, 299, 221};
            pokemon = new Pokemon(TYRANOCIF, "Tyranocif", none, MACHOUILLE, LAME_DE_ROC, SEISME, LASER_GLACE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case DIMORET :
            types.push_back(DARK);
            types.push_back(ICE);
            stats_pokemon = {344, 339, 229, 189, 269, 349};
            pokemon = new Pokemon(DIMORET, "Dimoret", none, ECLATS_GLACE, SABOTAGE, CHUTE_GLACE, CASSE_BRIQUE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        case ELECTHOR :
            types.push_back(ELECTRIC);
            types.push_back(FLY);
            stats_pokemon = {384, 279, 269, 349, 279, 299};
            pokemon = new Pokemon(ELECTHOR, "Electhor", none, CANICULE, TONNERRE, CHANGE_ECLAIR, ATTERISSAGE, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
        default:
            types.push_back(NORMAL);
            stats_pokemon = {200, 200, 200, 200, 200, 200};
            pokemon = new Pokemon(LEVEINARD, "Default", none, ABRI, ABRI, ABRI, ABRI, 1, types, NONE_S, stats_pokemon, 0,stats_pokemon.pv);
            break;
    }

    return *pokemon;

}

}
