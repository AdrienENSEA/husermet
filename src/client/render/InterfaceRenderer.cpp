#include "InterfaceRenderer.h"

#define LENGTH_SPRITE 96
#define LENGTH_WINDOW 512
#define SCALE_SPRITE 1.3f

namespace render {

    InterfaceRenderer::InterfaceRenderer () {
        sf::Sprite t;
        sf::Sprite m;
        background_text = t;
        background_menu = m;
    }
    sf::RectangleShape InterfaceRenderer::getR () {
        sf::RectangleShape rectangle(sf::Vector2f(LENGTH_WINDOW-175, LENGTH_WINDOW-385));
        rectangle.setPosition(175-10, 385-10);
        rectangle.setOutlineThickness(10);
        rectangle.setOutlineColor(sf::Color(250, 150, 100));
        return rectangle;
    }
    sf::Text InterfaceRenderer::getText (sf::Font* font, std::string text, int length, int height) {
        sf::Text t;
        t.setFont(*font);
        t.setString(text);
        t.setCharacterSize(16);
        t.setPosition(length, height);
        t.setColor(sf::Color::Black);
        return t;
    }
    void InterfaceRenderer::drawWait () {

    }
    void InterfaceRenderer::load () {

    }

}

