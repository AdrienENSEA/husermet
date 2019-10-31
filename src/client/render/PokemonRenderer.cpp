#include "PokemonRenderer.h"
#include <iostream>

#define LENGTH_SPRITE 96
#define LENGTH_WINDOW 512
#define SCALE_SPRITE 2.1f

using namespace std;

namespace render {

    PokemonRenderer::PokemonRenderer () {
        idpokemon=0;
    }
/*
    sf::Sprite PokemonRenderer::getS (sf::Texture* texture, bool position) {
        sf::Sprite p;
        p.setTexture(*texture);
        if (position) p.setPosition(10,180); 
        else p.setPosition(280,10); 
        p.setScale(SCALE_SPRITE, SCALE_SPRITE);
        return p;
    }
    void PokemonRenderer::draw (sf::RenderWindow& window) {
        pokemon.setTexture(texture);
        if (position) p.setPosition(10,180); 
        else p.setPosition(280,10); 
        pokemon.setScale(SCALE_SPRITE, SCALE_SPRITE);
        window.draw(pokemon)
}
    void PokemonRenderer::drawWait () {}
    void PokemonRenderer::drawEffect () {}
    void PokemonRenderer::load (const std::string& tileset, sf::Vector2u tilesize) {} 
*/
    void PokemonRenderer::draw (sf::RenderWindow& window) {
        window.draw(pokemon);
}
    void PokemonRenderer::setBack (bool b) {
        back = b;
    }
    bool PokemonRenderer::setTexture (std::string pathtexture) {
        if (!tpokemon.loadFromFile(pathtexture, sf::IntRect(LENGTH_SPRITE*2*(idpokemon-1)+LENGTH_SPRITE*back, 0, LENGTH_SPRITE, LENGTH_SPRITE))) {
            cout << "Echec chargement texture" << endl;
            return false;
        }
        //tpokemon.setSmooth(true);
        return true;
        }

    void PokemonRenderer::setSprite () {
        pokemon.setTexture(tpokemon);
        if (back) pokemon.setPosition(10,180);
        else pokemon.setPosition(280,10);
        pokemon.setScale(SCALE_SPRITE, SCALE_SPRITE);
}
    void PokemonRenderer::setIdPokemon (int idpokemon) {
        this->idpokemon = idpokemon;
}

}

