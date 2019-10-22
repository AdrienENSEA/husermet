#include "Scene.h"

namespace render {

Scene::Scene () {
    height = 512;
    length = 512;
    sf::RenderWindow window(sf::VideoMode(length, height), "Tilemap");
}

void Scene::draw () {
    
}

}

