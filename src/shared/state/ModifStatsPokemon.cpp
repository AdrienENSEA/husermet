#include "ModifStatsPokemon.h"

namespace state {

ModifStatsPokemon::ModifStatsPokemon (StatsPokemon modif_stats_pokemon, int round_left) {
	this->modif_stats_pokemon = modif_stats_pokemon;
	this->round_left = round_left;
}
ModifStatsPokemon::ModifStatsPokemon () {
	this->modif_stats_pokemon = {0, 0, 0, 0, 0, 0};
	this->round_left = 0;
}

// Setters and Getters
StatsPokemon ModifStatsPokemon::getModifStats () const {
	return modif_stats_pokemon;
}
void ModifStatsPokemon::setModifStats (StatsPokemon modifStatsPokemon) {
	this->modif_stats_pokemon = modif_stats_pokemon;
}
int ModifStatsPokemon::getRoundLeft () const {
	return round_left;
}
void ModifStatsPokemon::setRoundLeft (int roundLeft) {
	
}


}
