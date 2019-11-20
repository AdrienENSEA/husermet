#include "State.h"
#include <iostream>

namespace state {

State::State (std::vector <Pokemon> battle, TypeWeather weather, TypeTerrain terrain) : battle(battle), weather(weather), terrain(terrain) {

}

State::State() {
	battle = {};
	weather = NONE_W;
	terrain = NONE_G;
}

void State::changeTeam (int fighter, int back) {
    Pokemon temp = battle.at(fighter);
    battle.at(fighter) = battle.at(back);
    battle.at(back) = temp;
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
Pokemon& State::getPokemon (int position){
    return battle.at(position);
}
/*
void State::modifPP (int pp, int i) {
    pps.at(i) += pp;
}
void State::modifPV (int pv) {
    this->pv += pv;
}
void State::setPPs(std::vector<int> pps) {
    this->pps = pps;
}
void State::setPP(int pp, int i) {
    if (pp>0) this->pp.at(i) = pp;
    else this->pp.at(i) = 0;
    //std::cout << "apres setPP" << a.getPP()<<std::endl;
    //std::cout << "apres setPP s" <<getPokemon(0).getAttack().at(i).getPP()<<std::endl;
}
int State::getPP(int i) const {
    //std::cout << "apres getPP s" <<getPokemon(0).getAttack().at(i).getPP()<<std::endl;
    return pp.at(i);
}
void State::setPV(int pv) {
    if (pv>0) this->pv = pv;
    else this->pv = 0;
}
int State::getPV() const {
    return pv;
}
*/
}

