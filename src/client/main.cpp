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

using namespace std;
using namespace state;
using namespace render;
using namespace engine;

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
/*
            cout << "Affichage d'un état" << endl;
            Pokemon p;
            // seul un nombre réduit de pokemon sont codés : groudon, kyogre, rayquaza, leveinard
            Pokemon groudon = PokemonFactory::createPokemon(GROUDON);
            Pokemon kyogre = PokemonFactory::createPokemon(KYOGRE);
            std::vector <Pokemon> battle {kyogre, p, p, p, p, p, groudon, p, p, p, p, p};
            // le terrain PSYCHIC peut etre remplacé par GRASSY, MISTY ou ELECTRIK
            State s(battle, SUN, PSYCHIC, {0,0,0,0},0);
		    Scene scene1;
            scene1.draw(s);*/
        }
        if (string(argv[1]) == "engine") {/*
            cout << "Affichage de l'état initial" << endl;
            Pokemon p;
            // seul un nombre réduit de pokemon sont codés : groudon, kyogre, rayquaza, leveinard
            Pokemon groudon = PokemonFactory::createPokemon(GROUDON);
            Pokemon kyogre = PokemonFactory::createPokemon(KYOGRE);
            Pokemon ray = PokemonFactory::createPokemon(RAYQUAZA);
            std::vector <Pokemon> battle {kyogre,ray, ray, ray, p, p, groudon, p, p, p, p, p};
            std::vector <Attack> att = battle.at(0).getAttack();
            std::vector<int> pps = {att.at(0).getStatsAttack().pp, att.at(1).getStatsAttack().pp, att.at(2).getStatsAttack().pp, att.at(3).getStatsAttack().pp};
            // le terrain PSYCHIC peut etre remplacé par GRASSY, MISTY ou ELECTRIK
            int pv = battle.at(0).getStats().pv;
            State s(battle, SUN, PSYCHIC, pps, pv);
            Scene scene;
            scene.draw(s);
            cout << "Affichage de l'état après un changement de Pokémon" << endl;
            Engine e(&s);
            ChangePokemonCommand c;
            c.setPokemon(kyogre);
            c.setPokemon_target(ray);
            e.addCommand(c);
            e.runCommands();
            scene.draw(s);
            cout << "Affichage de l'état après la première attaque du pokemon actif" << endl;
            AttackCommand a;
            a.setPokemon(battle.at(0));
            a.setPokemon_target(battle.at(6));
            a.setAttack(battle.at(0).getAttack().at(0));
            e.addCommand(a);
            e.runCommands();
            scene.draw(s);*/
        }
    }

    else {
        cout << "Veuillez ajouté hello, render ou engine en argument" << endl;
            cout << "Affichage de l'état initial" << endl;
            Pokemon p;
            // seul un nombre réduit de pokemon sont codés : groudon, kyogre, rayquaza, leveinard
            Pokemon groudon = PokemonFactory::createPokemon(GROUDON);
            //Pokemon kyogre = PokemonFactory::createPokemon(KYOGRE);
            Pokemon kyogre = PokemonFactory::createPokemon(KYOGRE);
            Pokemon ray = PokemonFactory::createPokemon(RAYQUAZA);
            std::vector <Pokemon> battle {kyogre,ray, ray, ray, p, p, groudon, groudon, p, p, p, p};
            
            
            // le terrain PSYCHIC peut etre remplacé par GRASSY, MISTY ou ELECTRIK
            std::vector<int> pps = {battle.at(0).getAttack(0).getPP(),battle.at(0).getAttack(1).getPP(),battle.at(0).getAttack(2).getPP(),battle.at(0).getAttack(3).getPP()};

            State s(battle, SUN, PSYCHIC, battle.at(6).getPV(), pps);
/*
cout<<s.getPokemon(0).getAttack().at(0).getPP()<<endl;
Attack a = s.getPokemon(0).getAttack().at(0);
cout<<a.getPP()<<endl;*/
/*
Attack attaque;
cout << "attaque" << attaque.getPP()<< endl;
attaque.setPP(3);
cout << attaque.getPP()<< endl;
*/
            Scene scene;
            scene.draw(s);/*
            cout << "Affichage de l'état après un changement de Pokémon" << endl;
            
            Command c(1);
            c.setPokemon(0);
            c.setPokemon_target(1);
            e.addCommand(c);
            e.runCommands();
            scene.draw(s);
            cout << "Affichage de l'état après la première attaque du pokemon actif" << endl;
            Command a(2);
            a.setPokemon(0);
            a.setPokemon_target(6);
            a.setAttack(0);
            e.addCommand(a);
            e.runCommands();
            scene.draw(s);  */
            
    }
    
    return 0;
}
