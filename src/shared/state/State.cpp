#include "State.h"

namespace state {

State::State (std::list <Team> battle, TypeWeather weather, TypeTerrain terrain) {
	this->battle = battle;
	this->weather = weather;
	this->terrain = terrain;
}

State::State() {
	battle = {};
	weather = NONE_W;
	terrain = NONE_G;
}

void State::changeTeam (int fighter, int position, Pokemon pokemon) {
    
}
TypeTerrain State::getTypeTerrain () {
    return terrain;
}
void State::setTypeTerrain (TypeTerrain t) {
    terrain = t;
}
TypeWeather State::getTypeWeather () {
    return weather;
} 
void State::setTypeWeather (TypeWeather w) {
    weather = w;
}

}

