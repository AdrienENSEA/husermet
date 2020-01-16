#include "ModifStatsPokemon.h"

namespace state {

	ModifStatsPokemon::ModifStatsPokemon (StatsPokemon modif_stats_pokemon, int round_left) {
		this->modif_stats_pokemon = modif_stats_pokemon;
		this->round_left = round_left;
		weather=NONE_W;
		terrain=NONE_G;
		state=NONE_S;
	}
	ModifStatsPokemon::ModifStatsPokemon () {
		this->modif_stats_pokemon = {0, 0, 0, 0, 0, 0};
		this->round_left = 0;
		weather=NONE_W;
		terrain=NONE_G;
		state=NONE_S;
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
		this->round_left = round_left;
	}
	TypeWeather ModifStatsPokemon::getWeather () const {
		return weather;
	}
    void ModifStatsPokemon::setWeather (TypeWeather w) {
		weather = w;
	}
    TypeTerrain ModifStatsPokemon::getTerrain () const {
		return terrain;
	}
    void ModifStatsPokemon::setTerrain (TypeTerrain t) {
		terrain = t;
	}
	TypeState ModifStatsPokemon::getState () const {
		return this->state;
	}
    void ModifStatsPokemon::setState (TypeState s) {
		this->state = s;
	}
}
