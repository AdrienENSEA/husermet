#include "InfoRenderer.h"
#include <iostream>

using namespace std;

namespace render {

    InfoRenderer::InfoRenderer () {
    }
    
    void InfoRenderer::setTexture(int back) {
        if (back==1) {
            if (!tinfo.loadFromFile("../res/hud.png", sf::IntRect(0, 43, 121, 30)))
                cout << "Error load texture pokemon" << endl;
        }
        else if (back==0) {
            if (!tinfo.loadFromFile("../res/hud.png", sf::IntRect(0, 22, 124, 16)))
                cout << "Error load texture pokemon" << endl;
        }
        else
            cout << "Error value back in setTexture InfoRenderer" << endl;
        
        //this->setLifeBar();
    }
    
    void InfoRenderer::setSprite(int position) {
        this->setFont();
        
        sinfo.setTexture(tinfo);
        switch (position) { 
            case 0:
                sinfo.setPosition(270,200); 
                name.setPosition(290,200);
                level.setPosition(450,200); 
                slifebar.setPosition(270+112,200+20); 
                hp.setPosition(270+110,200+30);
                hp_max.setPosition(270+180,200+30); break;
            case 1:
                sinfo.setPosition(280,260); 
                name.setPosition(300,260); 
                level.setPosition(460,260); 
                slifebar.setPosition(280+112,260+20); 
                hp.setPosition(280+110,260+30); 
                hp_max.setPosition(280+180,260+30); break;
            case 2:
                sinfo.setPosition(0,50); 
                name.setPosition(20,50); 
                level.setPosition(190,50); 
                slifebar.setPosition(0+85,50+20); 
                hp.setString("");
                hp_max.setString(""); break;
            case 3:
                sinfo.setPosition(-10,10); 
                name.setPosition(10,10); 
                level.setPosition(180, 10); 
                slifebar.setPosition(-10+85,10+20);
                hp.setString("");
                hp_max.setString(""); break;
            default:
                cout << "Error setting position sprite pokemon" << endl;
                sinfo.setPosition(-10,-100); break;
        }
        sinfo.setScale(2,2);
        
        slifebar.setScale(2,2);

    }
    void InfoRenderer::setFont() {
        if (!font.loadFromFile("../res/fontpokemon.ttf"))
            cout << "Error load font" << endl;
    }
    
    void InfoRenderer::setLifeBar(int pv) {
        // high life
        if(pv>100) {
            if (!tlifebar.loadFromFile("../res/hud.png", sf::IntRect(59, 7, 48, 1)))
                cout << "Error load texture lifebar" << endl;
        }
                
        // low life
        else if(pv<30) {
            if (!tlifebar.loadFromFile("../res/hud.png", sf::IntRect(59, 14, 48, 1)))
                cout << "Error load texture lifebar" << endl;
        }
        
        // middle life
        else {
            
            if (!tlifebar.loadFromFile("../res/hud.png", sf::IntRect(59, 10, 48, 2)))
                cout << "Error load texture lifebar" << endl;
        }
                
        slifebar.setTexture(tlifebar);
        
    }
    
    void InfoRenderer::setTexts(state::Pokemon& pokemon, int joueur) {
        //this->setFont();
        name.setFont(font);
        name.setString(pokemon.getName());
        name.setCharacterSize(12);
        name.setColor(sf::Color::Black);
        
        level.setFont(font);
        level.setString("100");
        level.setCharacterSize(12);
        level.setColor(sf::Color::Black);
          if (joueur ==0) {
        hp.setFont(font);  
        hp.setString(to_string(pokemon.getPV()));
        hp.setCharacterSize(12);
        hp.setColor(sf::Color::White);
        
        hp_max.setFont(font);
        hp_max.setString(to_string(pokemon.getStats().pv));
        hp_max.setCharacterSize(12);
        hp_max.setColor(sf::Color::White);}
        
    }
    
    void InfoRenderer::draw(sf::RenderWindow& window) const {
        window.draw(sinfo);
        window.draw(level);
        window.draw(name);
        window.draw(slifebar);
        window.draw(hp);
        window.draw(hp_max);
    }
    
    void InfoRenderer::drawLife() const {
        
    }
    
    void InfoRenderer::displayDamage (state::State& state, sf::RenderWindow& window, int damage) {
        //this->setSprite();
    }
}

