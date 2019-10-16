#include "AttackFactory.h"

namespace state {


Attack AttackFactory::createAttack(IdAttack id_attack) {

    Attack* attack;
    StatsAttack stats_attack;
    ModifStatsPokemon stats_modif;
    
    switch (id_attack) 
    {
        case E_COQUE :
            stats_attack = {0, 0, 0, 0, 0, 0};
            attack = new Attack(E_COQUE, "E COQUE", "Le lanceur récupère jusqu’à la moitié de ses PV max", NORMAL, stats_attack, stats_modif);
            break;
        case TOXIK :
            break;
        case ABRI :
            break;
        case FRAPPE_ATLAS :
            break;
        case CHANGE_ECLAIR :
            break;
        case TONNERRE :
            break;
        case COUP_D_JUS :
            break;
        case EXPLOSION :
            break;
        case RAYON_CHARGE :
            break;
        case CAGE_ECLAIR :
            break;
        default:
            break;
    }
    
    return *attack;
}

}
