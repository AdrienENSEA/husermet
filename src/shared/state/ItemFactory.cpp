#include "ItemFactory.h"

namespace state {

Item ItemFactory::createItem(IdItem id_item) {

    Item *item;
    StatsPokemon effect_stats;

    switch (id_item) 
    {
        case NONE_I :
            effect_stats = {0, 0, 0, 0, 0, 0};
            item = new Item(NONE_I, "", "", effect_stats, NONE_S, NONE_T);
            break;
        case RESTES :
            effect_stats = {0, 0, 0, 0, 0, 0};
            item = new Item(RESTES, "Restes", "Restaure 1/16 des pv max du pokemon a la fin de chaque tour", effect_stats, NONE_S, NONE_T);
            break;
        case ORBE_VIE :
            break;
        case MOUCHOIR_SOIE :
            break;
        default:
            break;
    }

    return *item;

}

}
