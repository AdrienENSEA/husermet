#include "Pokemon.h"

namespace state {

Pokemon::Pokemon (IdPokemon id_pokemon, std::string name, Object object, std::list <Attack> attacks, int ability, Type type, TypeState state, StatsPokemon stats_pokemon, int ev) {
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
void Pokemon::setObject ( Object object) {

}
std::list <Attack> Pokemon::getAttack () {
	return attacks;
}
/// 	
/// @param position		(???) 
/// @param attack		(???) 
void Pokemon::setAttack (int position, Attack attack) {
    std::list<Attack>::iterator it = attacks.begin();
    advance(it, position-1); 
    attacks.insert(it, attack);
}
// Setters and Getters

}

