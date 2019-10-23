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
            std::list <Team> battle = {};
            State s(battle, SUN, GRASSY);
		    Scene scene1;
            scene1.drawScene(s);
	    }

    }
    else {
        cout << "Veuillez ajouté hello ou render en argument" << endl;
    }
    
    return 0;
}
