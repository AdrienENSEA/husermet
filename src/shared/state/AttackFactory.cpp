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
            stats_attack = {10, 0, 100, 3, 0, -1};
            stats_pokemon = {50, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(E_COQUE, "E-Coque", "Le lanceur récupère jusqu’à la moitié de ses PV max", NORMAL, stats_attack, stats_modif, 10);
            break;
        case DANSE_PLUIE :
            stats_attack = {5, 153, 0, 3, 0, 4};
            stats_modif.setRoundLeft(5);
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            stats_modif.setWeather(RAIN);
            attack = new Attack(DANSE_PLUIE, "Danse Pluie", "Invoque de fortes pluies qui durent cinq tours, augmentant la puissance des capacités de type Eau et baissant celle des capacités de type Feu", WATER, stats_attack, stats_modif,5);
            break;
        case TOXIK :
            stats_attack = {10, 0, 0, 3, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            stats_modif.setState(POISONED);
            attack = new Attack(TOXIK, "Toxik", "Empoisonne gravement l'ennemi. Les dégâts dûs au poison augmentent à chaque tour.", POISON, stats_attack, stats_modif,10);
            break;
        case ABRI :
            stats_attack = {10, 0, 101, 3, 4, -1};
            stats_modif.setRoundLeft(1);
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(ABRI, "Abri", "Le lanceur esquive toutes les attaques. Le risque d’échec augmente lorsque la capacité est utilisée plusieurs fois de suite.", NORMAL, stats_attack, stats_modif,10);
            break;
        case FRAPPE_ATLAS :
            stats_attack = {20, 100, 100, 1, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(FRAPPE_ATLAS, "Frappe Atlas", "L'ennemi est projeté grâce au pouvoir de la gravité. Inflige des dégâts équivalents au niveau du lanceur.", FIGHT, stats_attack, stats_modif,20);
            break;
        case CHANGE_ECLAIR :
            stats_attack = {20, 70, 100, 1, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(CHANGE_ECLAIR, "Change Eclair", "Après son attaque, le lanceur revient à toute vitesse et change de place avec un Pokémon de l'équipe prêt au combat.", ELECTRIC, stats_attack, stats_modif,20);
            break;
        case TONNERRE :
            stats_attack = {15, 90, 100, 2, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(TONNERRE, "Tonnerre", "Après son attaque, le lanceur revient à toute vitesse et change de place avec un Pokémon de l'équipe prêt au combat.", ELECTRIC, stats_attack, stats_modif,15);
            break;
        case COUP_D_JUS :
            break;
        case EXPLOSION :
            break;
        case RAYON_CHARGE :
            break;
        case CAGE_ECLAIR :
            break;
        case HYDROCANON :
            stats_attack = {5, 110, 100, 2, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(HYDROCANON, "Hydrocanon","", WATER, stats_attack, stats_modif,5);
            break;
        case MEGAFOUET :
            stats_attack = {10, 120, 85, 1, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(MEGAFOUET, "Megafouet", "", GRASS, stats_attack, stats_modif,10);
            break;
        case LAME_FEUILLE :
            stats_attack = {15, 90, 100, 1, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(LAME_FEUILLE, "Lame feuille", "", GRASS, stats_attack, stats_modif,15);
            break;
        case DEFLAGRATION :
            stats_attack = {5, 110, 85, 2, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(DEFLAGRATION, "Deflagration", "", FIRE, stats_attack, stats_modif,5);
            break;
        case EBULLITION :
            stats_attack = {15, 80, 100, 2, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(EBULLITION, "Ebullition", "", WATER, stats_attack, stats_modif,15);
            break;
        case LASER_GLACE :
            stats_attack = {10, 90, 100, 2, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(LASER_GLACE, "Laser Glace", "", ICE, stats_attack, stats_modif,10);
            break;
        case LUMINOCANON :
            stats_attack = {10, 80, 100, 2, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(LUMINOCANON, "Luminocanon", "", STEEL, stats_attack, stats_modif,10);
            break;
        case TELLURIFORCE :
            stats_attack = {10, 90, 100, 2, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(TELLURIFORCE, "Telluriforce", "", GROUND, stats_attack, stats_modif,15);
            break;
        case DRACO_METEORE :
            stats_attack = {5, 130, 90, 2, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(DRACO_METEORE, "Draco Meteore", "", DRAGON, stats_attack, stats_modif,5);
            break;
        case BALL_OMBRE : 
            stats_attack = {15, 80, 100, 2, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(BALL_OMBRE, "Ball'Ombre", "", GHOST, stats_attack, stats_modif,15);
            break;
        case CRADOVAGUE : 
            stats_attack = {10, 95, 100, 2, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(CRADOVAGUE, "Cradovague", "", POISON, stats_attack, stats_modif,10);
            break;
        case EXPLOFORCE : 
            stats_attack = {5, 120, 70, 2, 0, 1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(EXPLOFORCE, "Exploforce", "", FIGHT, stats_attack, stats_modif,5);
            break;
        case FEU_FOLLET : 
            stats_attack = {15, 0, 85, 3, 0, -1};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            stats_modif.setState(BURNED);
            attack = new Attack(FEU_FOLLET, "Feu Follet", "", FIRE, stats_attack, stats_modif,15);
            break;
        case SEISME : 
            stats_attack = {10, 100, 100, 1, 0, 3};
            stats_pokemon = {0, 0, 0, 0, 0, 0};
            stats_modif.setModifStats(stats_pokemon);
            attack = new Attack(SEISME, "Seisme", "", GROUND, stats_attack, stats_modif,10);
            break;
        default:
            attack = new Attack();
            break;
    }
    
    return *attack;
}

}
