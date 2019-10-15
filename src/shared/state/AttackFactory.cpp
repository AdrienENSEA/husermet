#include "PokemonFactory.h"

namespace state {

AttackFactory::AttackFactory() {

}

Pokemon createAttack(IdAttack id_attack) {

    Attack attack;

    switch (id_pokemon) 
    {
        case GROUDON :
            attack = new Pokemon groudon(GROUDON, "Groudon", none, attacks, 1, types, NORMAL, stats_pokemon, 0);
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
