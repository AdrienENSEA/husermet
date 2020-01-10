#include <iostream>
#include <unistd.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include <string.h>
#include "render.h"
#include "engine.h"
#include "client.h"

using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace client;

int main(int argc, char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);
	
    if (argc>1) {
        if (string(argv[1]) == "hello") {
            cout << "Bonjour tout le monde !" << endl;
        }
	    else if (string(argv[1]) == "state") {
		    cout << "Veillez utiliser les commandes make unittest et make code-coverage depuis le dossier build" << endl;
	    }
        else if (string(argv[1]) == "render") {
            cout << "Affichage d'un état" << endl;
            sf::RenderWindow window(sf::VideoMode(512, 512), "Fight");
		    Scene scene;
            Engine e;
            int p=0;
            std::vector<int> order;
            scene.draw(window);
            scene.initInterface(e.getState(), window,p);
            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if(event.type == sf::Event::Closed) {
                        std::cout << "Vous avez fermer la fenetre" << endl;
                        window.close();
                    }
                }
                window.display();
            }
        }
        else if (string(argv[1]) == "engine") {
            cout << "Affichage de l'état initial" << endl;
            sf::RenderWindow window(sf::VideoMode(512, 512), "Fight");
            Scene scene;
            scene.draw(window,-1);
        }
        else if (string(argv[1]) == "random_ai") {
            cout << "Affichage de l'état initial avec une IA random" << endl;
            sf::RenderWindow window(sf::VideoMode(512, 512), "Fight");
            Scene scene;
            scene.draw(window,1);
        }
        else if (string(argv[1]) == "heuristic_ai") {
            cout << "Affichage de l'état initial avec une IA heuristic" << endl;
            sf::RenderWindow window(sf::VideoMode(512, 512), "Fight");
            Scene scene;
            scene.draw(window,2);
        }
        else if (string(argv[1]) == "deep_ai") {
            cout << "Affichage de l'état initial avec une IA deep" << endl;
            sf::RenderWindow window(sf::VideoMode(512, 512), "Fight");
            Scene scene;
            scene.draw(window,3);
        }
        else if (string(argv[1]) == "thread") {
            cout << "Affichage de l'état initial avec un thread séparé" << endl;
            remove("../res/command.json");
			Client client;
            client.run();
        }
        else if (string(argv[1]) == "play") {
            cout << "Affichage du jeu depuis un enregistrement de commandes" << endl;
            Client client;
            client.play();
        }
        else if (string(argv[1]) == "network") {
            cout << "Network" << endl;
            
        }
    }

    else {
        cout << "Veuillez ajouté hello, render ou engine en argument" << endl;
			Client client;
            client.connect();

    }
    
    return 0;
}
