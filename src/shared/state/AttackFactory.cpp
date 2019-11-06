#include "AttackFactory.h"

namespace state {


Attack AttackFactory::createAttack(IdAttack id_attack) {

    Attack* attack;
    StatsAttack stats_attack;
    ModifStatsPokemon stats_modif;
    StatsPokemon stats_pokemon;
    
    switch (id_attack) 
    {
        case E_COQUE :
            stats_attack = {10, 10, 0, 100, 3, 0, -1};
            stats_pokemon = {50, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(E_COQUE, "E-Coque", "Le lanceur récupère jusqu’à la moitié de ses PV max", NORMAL, stats_attack, stats_modif);
            break;
        case DANSE_PLUIE :
            stats_attack = {5, 5, 0, 0, 3, 0, 4};
            stats_modif.setRoundLeft(5);
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(DANSE_PLUIE, "Danse Pluie", "Invoque de fortes pluies qui durent cinq tours, augmentant la puissance des capacités de type Eau et baissant celle des capacités de type Feu", WATER, stats_attack, stats_modif);
            break;
        case TOXIK :
            stats_attack = {10, 10, 0, 0, 3, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(TOXIK, "Toxik", "Empoisonne gravement l'ennemi. Les dégâts dûs au poison augmentent à chaque tour.", POISON, stats_attack, stats_modif);
            break;
        case ABRI :
            stats_attack = {10, 10, 0, 101, 3, 4, -1};
            stats_modif.setRoundLeft(1);
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(ABRI, "Abri", "Le lanceur esquive toutes les attaques. Le risque d’échec augmente lorsque la capacité est utilisée plusieurs fois de suite.", NORMAL, stats_attack, stats_modif);
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
