#include "PokemonFactory.h"

namespace state {

Pokemon PokemonFactory::createPokemon(IdPokemon id_pokemon) {

    Pokemon *pokemon;
    Object none = ObjectFactory::createObject(NONE_O);
    Attack first_attack;
    std::vector <Attack> attacks = {};
    std::vector <Type> types = {};
    StatsPokemon stats_pokemon;

    switch (id_pokemon) 
    {
        case GROUDON :
            first_attack = AttackFactory::createAttack(E_COQUE);
            attacks.push_back(first_attack);
            types.push_back(GROUND);
            stats_pokemon = {100, 150, 140, 100, 90, 90};
            pokemon = new Pokemon(GROUDON, "Groudon", none, attacks, 1, types, NONE_S, stats_pokemon, 0);
            break;
        case KYOGRE :
            first_attack = AttackFactory::createAttack(DANSE_PLUIE);
            attacks.push_back(first_attack);
            types.push_back(WATER);
            stats_pokemon = {100, 100, 90, 150, 140, 90};
            pokemon = new Pokemon(KYOGRE, "Kyogre", none, attacks, 1, types, NONE_S, stats_pokemon, 0);
            break;
        case RAYQUAZA :
            first_attack = AttackFactory::createAttack(E_COQUE);
            attacks.push_back(first_attack);
            types.push_back(WATER);
            stats_pokemon = {100, 100, 90, 150, 140, 90};
            pokemon = new Pokemon(RAYQUAZA, "Rayquaza", none, attacks, 1, types, NONE_S, stats_pokemon, 0);
            break;
        case LEVEINARD :
            first_attack = AttackFactory::createAttack(E_COQUE);
            attacks.push_back(first_attack);
            types.push_back(WATER);
            stats_pokemon = {100, 100, 90, 150, 140, 90};
            pokemon = new Pokemon(LEVEINARD, "Leveinard", none, attacks, 1, types, NONE_S, stats_pokemon, 0);
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
