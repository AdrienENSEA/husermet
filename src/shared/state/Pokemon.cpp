#include "Pokemon.h"
#include "StatsPokemon.h"

namespace state {

int Pokemon::getID () {
	return id_pokemon;
}
void Pokemon::setID ( IdPokemon id) {
    id_pokemon = id;
}
std::string Pokemon::getName () {

}
void Pokemon::setName (std::string new_name) {
    name = new_name;
}
int Pokemon::getObject () {
	return 0;
}
void Pokemon::setObject ( int object) {

}
int Pokemon::getPV () {
	return stats_pokemon.pv;
}
void Pokemon::setPV (int x) {
    stats_pokemon.pv = x;
}
int Pokemon::getAttack () {
	return 0;
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

