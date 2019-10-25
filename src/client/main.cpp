#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include <string.h>
#include "render.h"

using namespace std;
using namespace state;
using namespace render;

int main(int argc, char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);
	
    if (argc>1) {
        if (string(argv[1]) == "hello") {
            cout << "Bonjour tout le monde !" << endl;
        }
	    if (string(argv[1]) == "state") {
		    cout << "state" << endl;
	    }
        if (string(argv[1]) == "render") {
            std::vector <Pokemon> battle = {};
            State s(battle, SUN, MISTY);
		    Scene scene1;
            scene1.draw(s);
	    }

    }
    else {
        cout << "Veuillez ajouté hello ou render en argument" << endl;
        StatsPokemon effect_stats {0, 0, 0, 0, 0, 0};
    StatsAttack stats_attack {0, 0, 0, 0, 0, 0};
    ModifStatsPokemon stats_modif;
    std::vector <Type> type {{GROUND}};
    Attack a1(FRAPPE_ATLAS, "Frappe Atlas", "desc", FIGHT, stats_attack, stats_modif);
    Attack a2(TOXIK, "Toxic", "desc", POISON, stats_attack, stats_modif);
    Attack a3(ABRI, "Abri", "desc", NORMAL, stats_attack, stats_modif);
    std::vector <Attack> attacks {a1, a2, a3};
    Object restes(ORBE_VIE, "Orbe vie", "description", effect_stats, NONE_S, NONE_T);
    StatsPokemon stats_pokemon = {0, 0, 0, 0, 0, 0};
    Pokemon groudon(GROUDON, "Groudon", restes , attacks, 1, type, NONE_S, stats_pokemon, 0);
        std::vector <Pokemon> battle {groudon, groudon};
            State s(battle, SUN, PSYCHIC);
		    Scene scene1;
            scene1.draw(s);
    }
    
    return 0;
}
