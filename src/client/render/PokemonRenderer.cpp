#include "PokemonRenderer.h"
#include <iostream>

#define LENGTH_SPRITE 98
#define LENGTH_WINDOW 512
#define SCALE_SPRITE 2.1f

using namespace std;

namespace render {

    PokemonRenderer::PokemonRenderer () {
    }
    
    void PokemonRenderer::draw (sf::RenderWindow& window) {
        window.draw(pokemon);
        info.draw(window);
    }

    void PokemonRenderer::drawP (sf::RenderWindow& window) {
        window.draw(pokemon);
    }
    
    bool PokemonRenderer::setTexture (int idpokemon, int back) {
        if (!tpokemon.loadFromFile("../res/spritesheet2.png", sf::IntRect(LENGTH_SPRITE*2*(idpokemon-1)+LENGTH_SPRITE*back, 0, LENGTH_SPRITE, LENGTH_SPRITE))){
            cout << "Echec chargement texture" << endl;
            return false;
        }
        info.setTexture(back);
        return true;
    }

    void PokemonRenderer::setSprite (int position) {
        pokemon.setTexture(tpokemon);
        switch (position) { 
            case 0:
                pokemon.setPosition(-10,170); 
                pokemon.setScale(SCALE_SPRITE-0.1, SCALE_SPRITE-0.1); break;
            case 1:
                pokemon.setPosition(80,180); 
                pokemon.setScale(SCALE_SPRITE+0.1, SCALE_SPRITE+0.1); break;
            case 2:
                pokemon.setPosition(280,-10); 
                pokemon.setScale(SCALE_SPRITE-0.1, SCALE_SPRITE-0.1); break;
            case 3:
                pokemon.setPosition(370,10); 
                pokemon.setScale(SCALE_SPRITE+0.1, SCALE_SPRITE+0.1); break;
            default:
                cout << "Error setting position sprite pokemon" << endl;
                pokemon.setPosition(-100,-100); break;
        }
        info.setSprite(position);
    }
    
    void PokemonRenderer::setInfo(state::Pokemon& pokemon, int joueur) {
        info.setTexts(pokemon, joueur);
        info.setLifeBar(pokemon.getPV(), pokemon.getStats().pv);
    }

    InfoRenderer& PokemonRenderer::getInfo() {
        return this->info;
    }

    void PokemonRenderer::makeTransparent(bool transparent) {
        sf::Color color = pokemon.getColor();
        if (transparent) {
            color.r = 0;
            color.g = 0;
            color.b = 0;
        } else {
            color.r = 255;
            color.g = 255;
            color.b = 255;
        }
        pokemon.setColor(color);
    }
    
    void PokemonRenderer::displayDamage (state::State& state, sf::RenderWindow& window, int damage, int position) {
        sf::Clock clock;
        sf::Time tim;
        bool shown = false;
        do {
            sf::sleep(sf::milliseconds(200));
            makeTransparent(shown);
            draw(window);
            window.display();
            shown = !shown;
            tim = clock.getElapsedTime();
        } while(tim.asSeconds()<1.0);
        makeTransparent(false);
        draw(window);
        window.display();
        info.displayDamage(state, window, damage, position);

    } 
    
}

