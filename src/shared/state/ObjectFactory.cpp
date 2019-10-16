#include "ObjectFactory.h"

namespace state {

Object ObjectFactory::createObject(IdObject id_object) {

    Object *object;
    StatsPokemon effect_stats;
    //Object none(NONE_O, "", "", effect_stats, NORMAL, NONE);
    //std::vector <Attack> attacks = {};

    switch (id_object) 
    {
        case NONE_O :
            //std::vector <Type> types = {FIRE}; //SOL
            //StatsPokemon stats_pokemon = {100, 150, 140, 100, 90, 90};
            object = new Object(NONE_O, "", "", effect_stats, NONE_S, NONE_T);
            break;
        case RESTES :
            effect_stats = {0, 0, 0, 0, 0, 0};
            object = new Object(NONE_O, "Restes", "Restaure 1/16 des pv max du pokemon a la fin de chaque tour", effect_stats, NONE_S, NONE_T);
            break;
        case ORBE_VIE :
            break;
        case MOUCHOIR_SOIE :
            break;
        default:
            break;
    }

    return *object;

}

}
