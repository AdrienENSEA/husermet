#include "State.h"

namespace state {

State::State() {
	battle = {};
	weather = NONE_W;
	arena = NONE_A;
}

State::State(std::list <Team> battle, TypeWeather weather, TypeArena arena) {
	this->battle = battle;
	this->weather = weather;
	this->arena = arena;
}

void State::changeTeam (int fighter, int position, Pokemon pokemon) {
    
}
TypeArena State::getTypeArena () {
    return arena;
}
void State::setTypeArena (TypeArena a) {
    arena = a;
}
TypeWeather State::getTypeWeather () {
    return weather;
} 
void State::setTypeWeather (TypeWeather w) {
    weather = w;
}

}

