#include "InterfaceRenderer.h"
#include <iostream>

#define LENGTH_SPRITE 98
#define WIDTH_TYPE 50
#define HEIGHT_TYPE 20
#define LENGTH_WINDOW 512
#define SCALE_TYPE 1.2f
#define SCALE_SPRITE_MIN 0.9f
namespace render {

    InterfaceRenderer::InterfaceRenderer () {
        idpokemon=0;
        idtype = 0;
    }
    void InterfaceRenderer::drawRect (sf::RenderWindow& window) {

        sf::RectangleShape rectangle(sf::Vector2f(LENGTH_WINDOW-175, LENGTH_WINDOW-385));
        rectangle.setPosition(10, 385-10);
        rectangle.setOutlineThickness(10);
        rectangle.setOutlineColor(sf::Color(250, 150, 100));
        window.draw(rectangle);
    }
    
    bool InterfaceRenderer::setFont(std::string pathfont){
        if (!font.loadFromFile(pathfont)) return false;
        return true;
    }
    
    void InterfaceRenderer::setText(std::string text1, int width, int height, int size){
        text.setFont(font);
        text.setString(text1);
        text.setCharacterSize(size);
        text.setPosition(width, height);
        text.setColor(sf::Color::Black);
    }
    
    void InterfaceRenderer::drawText(sf::RenderWindow& window){
        window.draw(text);   
    }

    bool InterfaceRenderer::setTPokemon (std::string pathtexture) {
        if (!tpokemon.loadFromFile(pathtexture, sf::IntRect(LENGTH_SPRITE*2*(idpokemon-1), 0, LENGTH_SPRITE, LENGTH_SPRITE))) {
            std::cout << "Echec chargement texture pokemon" << std::endl;
            return false;
        }
        //tpokemon.setSmooth(true);
        return true;
        }

    void InterfaceRenderer::setPokemon (float x, float y) {
        pokemon.setTexture(tpokemon);
        pokemon.setPosition(x,y);
        pokemon.setScale(SCALE_SPRITE_MIN, SCALE_SPRITE_MIN);
}
    void InterfaceRenderer::setIdPokemon (int idpokemon) {
        this->idpokemon = idpokemon;
}
    void InterfaceRenderer::drawPokemon (sf::RenderWindow& window) {
        window.draw(pokemon);
}
    bool InterfaceRenderer::setTType (std::string pathtexture) {
        if (!ttype.loadFromFile(pathtexture, sf::IntRect(WIDTH_TYPE*(idtype-1), 0, WIDTH_TYPE, HEIGHT_TYPE))) {
            std::cout << "Echec chargement texture type" << std::endl;
            return false;
        }
        return true;
        }

    void InterfaceRenderer::setType (float x, float y) {
        type.setTexture(ttype);
        type.setPosition(x,y);
        type.setScale(SCALE_TYPE, SCALE_TYPE);
}
    void InterfaceRenderer::setIdType (int idtype) {
        this->idtype = idtype;
}
    void InterfaceRenderer::drawType (sf::RenderWindow& window) {
        window.draw(type);
}
}


