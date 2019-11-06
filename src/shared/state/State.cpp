#include "State.h"
#include <iostream>

namespace state {

State::State (std::vector <Pokemon> battle, TypeWeather weather, TypeTerrain terrain, std::vector<int> pps, int pv) {
	this->battle = battle;
	this->weather = weather;
	this->terrain = terrain;
    this->pps = pps;
    this->pv = pv;
}

State::State() {
	battle = {};
	weather = NONE_W;
	terrain = NONE_G;
    pps = {0,0,0,0};
    pv = 0;
}

void State::changeTeam (int fighter, int back, int player) {
    Pokemon temp = battle.at(player + fighter);
    battle.at(player + fighter) = battle.at(player + back);
    battle.at(player + back) = temp;
}
TypeTerrain State::getTypeTerrain () const {
    return terrain;
}
void State::setTypeTerrain (TypeTerrain t) {
    terrain = t;
}
TypeWeather State::getTypeWeather () const {
    return weather;
} 
void State::setTypeWeather (TypeWeather w) {
    weather = w;
}
Pokemon State::getPokemon (int position) const{
    return battle.at(position);
}
void State::setPPs (std::vector<int> pps) {
    this->pps = pps;
}
std::vector<int> State::getPPs() const {
    return pps;
}
void State::setPV (int pv) {
    this->pv = pv;
}
int State::getPV() const {
    return pv;
}
}

