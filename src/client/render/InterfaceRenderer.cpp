#include "InterfaceRenderer.h"
#include <iostream>

using namespace std;

#define LENGTH_SPRITE 98
#define LENGTH_WINDOW 512
#define SCALE_SPRITE 1.3f
#define WIDTH_TYPE 50
#define HEIGHT_TYPE 20
#define SCALE_TYPE 1.2f
#define SCALE_SPRITE_MIN 0.5f

namespace render {

    InterfaceRenderer::InterfaceRenderer () {
        texts.resize(4);
        if (!font.loadFromFile("../res/fontpokemon.ttf"))
            cout << "Error loading font" << endl;
        for(std::size_t i=0; i<4; i++){
            texts[i].setFont(font);
            texts[i].setColor(sf::Color::Black);
            texts[i].setCharacterSize(16);
        }
        texts[0].setPosition(30, 395);
        texts[1].setPosition(200, 395);
        texts[2].setPosition(30, 445);
        texts[3].setPosition(200, 445);
    }
    void InterfaceRenderer::drawRect (sf::RenderWindow& window) {
        sf::RectangleShape rectangle1(sf::Vector2f(LENGTH_WINDOW-145, LENGTH_WINDOW-385));
        //rectangle.setPosition(175-10, 385-10);
        rectangle1.setPosition(10, 385-10);
        rectangle1.setOutlineThickness(10);
        rectangle1.setOutlineColor(sf::Color(250, 150, 100));
        window.draw(rectangle1);

        sf::RectangleShape rectangle2(sf::Vector2f(105, LENGTH_WINDOW-385));
        //rectangle.setPosition(175-10, 385-10);
        rectangle2.setPosition(LENGTH_WINDOW-115, 385-10);
        rectangle2.setOutlineThickness(10);
        rectangle2.setOutlineColor(sf::Color(0, 150, 100));
        window.draw(rectangle2);
    }
    
    bool InterfaceRenderer::setFont(std::string pathfont){
        if (!font.loadFromFile("../res/fontpokemon.ttf")) return false;
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
    
    void InterfaceRenderer::setTexts(std::vector<std::string> texts){
        for(int i=0; i<4; i++){
            this->texts[i].setString(texts[i]);
        } 
    }
    
    void InterfaceRenderer::drawTexts(sf::RenderWindow& window) const{
        for(std::size_t i=0; i<4; i++){
            window.draw(this->texts[i]);
            //cout << texts[i] << endl;
        } 
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


