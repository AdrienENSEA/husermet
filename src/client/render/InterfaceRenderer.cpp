#include "InterfaceRenderer.h"

#define LENGTH_SPRITE 96
#define LENGTH_WINDOW 512
#define SCALE_SPRITE 1.3f

namespace render {

    InterfaceRenderer::InterfaceRenderer () {
    }
    
    void InterfaceRenderer::drawRect(sf::RenderWindow& window) {
        sf::RectangleShape rectangle(sf::Vector2f(LENGTH_WINDOW-175, LENGTH_WINDOW-385));
        rectangle.setPosition(175-10, 385-10);
        rectangle.setOutlineThickness(10);
        rectangle.setOutlineColor(sf::Color(250, 150, 100));
        window.draw(rectangle);
    }
    
    void InterfaceRenderer::setFont(std::string pathfont){
        font.loadFromFile(pathfont);
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
}

