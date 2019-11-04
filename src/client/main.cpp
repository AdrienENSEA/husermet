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
		    cout << "Veillez utiliser les commandes make unittest et make code-coverage depuis le dossier build" << endl;
	    }
        if (string(argv[1]) == "render") {
            cout << "Affichage d'un état" << endl;
            Pokemon p;
            // seul un nombre réduit de pokemon sont codés : groudon, kyofre, rayquaza, leveinard
            Pokemon groudon = PokemonFactory::createPokemon(GROUDON);
            Pokemon kyogre = PokemonFactory::createPokemon(KYOGRE);
            std::vector <Pokemon> battle {kyogre, p, p, p, p, p, groudon, p, p, p, p, p};
            // le terrain PSYCHIC peut etre remplacé par GRASSY, MISTY ou ELECTRIK
            State s(battle, SUN, PSYCHIC);
		    Scene scene1;
            scene1.draw(s);
        }
        if (string(argv[1]) == "engine") {

        }
    }

    else {
        cout << "Veuillez ajouté hello ou render en argument" << endl;
            Pokemon p;
            // seul un nombre réduit de pokemon sont codés : groudon, kyofre, rayquaza, leveinard
            Pokemon groudon = PokemonFactory::createPokemon(GROUDON);
            Pokemon kyogre = PokemonFactory::createPokemon(KYOGRE);
            std::vector <Pokemon> battle {kyogre, p, p, p, p, p, groudon, p, p, p, p, p};
            // le terrain PSYCHIC peut etre remplacé par GRASSY, MISTY ou ELECTRIK
            State s(battle, SUN, PSYCHIC);
            //Engine engine(s);
            
    }
    
    return 0;
}
