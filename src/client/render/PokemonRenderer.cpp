#include "PokemonRenderer.h"

#define LENGTH_SPRITE 96
#define LENGTH_WINDOW 512
#define SCALE_SPRITE 2.1f

namespace render {

    PokemonRenderer::PokemonRenderer () {
        sf::Sprite b;
        background = b;
        position = {};
       
    }

    sf::Sprite PokemonRenderer::getS (sf::Texture* texture, bool position) {
        sf::Sprite p;
        p.setTexture(*texture);
        if (position) p.setPosition(10,180); 
        else p.setPosition(280,10); 
        p.setScale(SCALE_SPRITE, SCALE_SPRITE);
        return p;
    }
    void PokemonRenderer::drawWait () {}
    void PokemonRenderer::drawEffect () {}
    void PokemonRenderer::load (const std::string& tileset, sf::Vector2u tilesize) {}

}

