#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include <string.h>

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);
 
    if (argc>1) {
        if (strncmp(argv[1],"hello",5)==0) {
            cout << "Bonjour tout le monde !" << endl;
        }
    }
    else {
        cout << "Veuillez mettre 'hello' en argument" << endl;
    }
    testSFML();
    return 0;
}
