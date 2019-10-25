#include "PokemonRenderer.h"

#define LENGTH_SPRITE 96
#define LENGTH_WINDOW 512
#define SCALE_SPRITE 2.1f

namespace render {

    PokemonRenderer::PokemonRenderer () {
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
    void PokemonRenderer::setTexture (std::string pathtexture, int idpokemon) {
        tpokemon.loadFromFile(pathtexture, sf::IntRect(LENGTH_SPRITE*(idpokemon-1)+LENGTH_SPRITE*back, 0, LENGTH_SPRITE, LENGTH_SPRITE));
        }

    void PokemonRenderer::setSprite () {
        pokemon.setTexture(tpokemon);
        if (back) pokemon.setPosition(10,180);
        else pokemon.setPosition(280,10); 
        pokemon.setScale(SCALE_SPRITE, SCALE_SPRITE);
}

}

