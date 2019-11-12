#include "InterfaceRenderer.h"
#include <iostream>

using namespace std;

#define LENGTH_SPRITE 96
#define LENGTH_WINDOW 512
#define SCALE_SPRITE 1.3f

namespace render {

    InterfaceRenderer::InterfaceRenderer () {
        texts.resize(5);
        if (!font.loadFromFile("../res/fontpokemon.ttf"))
            cout << "Error loading font" << endl;
        for(std::size_t i=0; i<5; i++){
            texts[i].setFont(font);
            texts[i].setColor(sf::Color::Black);
            texts[i].setCharacterSize(16);
        }
        texts[0].setPosition(5, 415);
        texts[1].setPosition(200, 410);
        texts[2].setPosition(350, 410);
        texts[3].setPosition(200, 460);
        texts[4].setPosition(350, 460);
    }
    void InterfaceRenderer::drawRect (sf::RenderWindow& window) {
        sf::RectangleShape rectangle(sf::Vector2f(LENGTH_WINDOW-175, LENGTH_WINDOW-385));
        rectangle.setPosition(175-10, 385-10);
        rectangle.setOutlineThickness(10);
        rectangle.setOutlineColor(sf::Color(250, 150, 100));
        window.draw(rectangle);
    }
    
    bool InterfaceRenderer::setFont(std::string pathfont){
        if (!font.loadFromFile("../res/fontpokemon.ttf")) return false;
        return true;
    }
    
    void InterfaceRenderer::setText(std::string text1, int width, int height){
        text.setFont(font);
        text.setString(text1);
        text.setCharacterSize(16);
        text.setPosition(width, height);
        text.setColor(sf::Color::Black);
    }
    
    void InterfaceRenderer::drawText(sf::RenderWindow& window){
        window.draw(text);   
    }
    
    void InterfaceRenderer::setTexts(std::vector<std::string> texts){
        for(int i=0; i<5; i++){
            this->texts[i].setString(texts[i]);
        } 
    }
    
    void InterfaceRenderer::drawTexts(sf::RenderWindow& window) const{
        for(std::size_t i=0; i<5; i++){
            window.draw(this->texts[i]);
            //cout << texts[i] << endl;
        } 
    }
}


