#include "Scene.h"
#include <iostream>

#define LENGTH_SPRITE 96
#define LENGTH_TERRAIN 290
#define HEIGHT_TERRAIN 174

using namespace std;

namespace render {

Scene::Scene () : height {512}, length {512}{
}

void Scene::draw (state::State& etat) {
    sf::RenderWindow window(sf::VideoMode(height, length), "Tilemap");
    /*std::string filefont = "../res/fontpokemon.ttf";
    font.loadFromFile(filefont);
	sf::Image image;
	image.loadFromFile("../res/sand.png");
    // rendre le blanc (255,255,255) transparent (0)
	//image.createMaskFromColor(sf::Color(255, 255, 255), 0);

    sf::Texture back;
    back.loadFromImage(image); 
    sf::Sprite p;
        p.setTexture(back);
    p.setScale(2.1f,2.1f); 
// rendre image transparente (0) ou légèrement (150)
    p.setColor(sf::Color(255, 255, 255, 220));    
     */
/*
    sf::Texture back;
    back.loadFromFile("../res/terrain_elec.jpg", sf::IntRect(0, 0, 512, 512));
    sf::Sprite p;
        p.setTexture(back); 
    p.setScale(2.1f,2.1f);*/
    sf::Texture back;
    back.loadFromFile("../res/spritesheet_terrain.png", sf::IntRect(LENGTH_TERRAIN*(etat.getTypeTerrain()-1), 0, LENGTH_TERRAIN*etat.getTypeTerrain(), HEIGHT_TERRAIN));
    back.setSmooth(true);
    
    background.setTexture(back);
    background.setScale(2.1f,2.1f); 
// rendre image transparente (0) ou légèrement (150)
    background.setColor(sf::Color(255, 255, 255, 250));    

    sf::Texture texture1;
    texture1.loadFromFile("../res/spritesheet.png", sf::IntRect(0, 0, LENGTH_SPRITE*etat.getPokemon(0).getID(), LENGTH_SPRITE));
    sf::Texture texture2;
    texture2.loadFromFile("../res/spritesheet.png", sf::IntRect(LENGTH_SPRITE*3, 0, LENGTH_SPRITE, LENGTH_SPRITE));
/*
        sf::Sprite p;
        std::vector <sf::Sprite> ps;
        ps = {};
        ps.push_back(p);
        ps.at(0).setTexture(texture);       
        ps.at(0).setPosition(100,100); 
        ps.at(0).setScale(SCALE_SPRITE, SCALE_SPRITE);
    window.draw(ps.at(0));*/
    
    window.clear(sf::Color(255, 255, 255, 255));
    window.draw(background);
    interface.drawRect(window);
    
    interface.setFont("../res/fontpokemon.ttf");
    interface.setText("Attaquer", 200, 410);
    interface.drawText(window);
    interface.setText("Pokemon", 350, 410);
    interface.drawText(window);
    interface.setText("Sac", 200, 460);
    interface.drawText(window);
    interface.setText("Fuite", 350, 460);
    interface.drawText(window);
    interface.setText("Que faire ?", 5, 415);
    interface.drawText(window);
    //window.draw(pokemon.getS(&texture1, false));
    //window.draw(pokemon.getS(&texture2, true));
    
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // on dessine le niveau
        
       

        window.display();
    }

}


}

