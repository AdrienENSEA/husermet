#include "Pokemon.h"

namespace state {

Pokemon::Pokemon (IdPokemon id_pokemon, std::string name, Object object, std::vector <Attack> attacks, int ability, std::vector <Type> type, TypeState state, StatsPokemon stats_pokemon, int ev) {
	this->id_pokemon = id_pokemon;
    this->name = name;
    this->object = &object;
    this->attacks = attacks;
    this->ability = ability;
    this->type = type;
    this->state = state;
    this->stats_pokemon = stats_pokemon;
    this->ev = ev;
}

IdPokemon Pokemon::getID () {
	return id_pokemon;
}
std::string Pokemon::getName () {
	return name;
}
Object* Pokemon::getObject () {
	return object;
}
std::vector <Attack> Pokemon::getAttack () {
	return attacks;
}
std::vector <Type> Pokemon::getType () {
	return type;
}
TypeState Pokemon::getState () {
	return state;
}
StatsPokemon Pokemon::getStats () {
	return stats_pokemon;
}
int Pokemon::getEV () {
	return ev;
}
void Pokemon::setName (std::string new_name) {
	this->name = name;
}
void Pokemon::setObject ( Object object) {
	this->object = &object;
}
/// 	
/// @param position		position de l'attaque a ajouter
/// @param attack		attaque a ajouter dans la liste
void Pokemon::setAttack (int position, Attack attack) {
    std::vector<Attack>::iterator it = attacks.begin();
    advance(it, position-1); 
    attacks.insert(it, attack);
}
// Setters and Getters

}

