#include "Attack.h"

namespace state {

Attack::Attack () {
    id_attack = NONE_A;
	name = "name";
	descriptive_attack = "descriptive_attack";
	type = NONE_T;
	stats_attack = {0,0,0,0,0,0};
    ModifStatsPokemon s;
	stats_modif = s;
}

Attack::Attack (IdAttack id_attack, std::string name, std::string descriptive_attack, Type type, StatsAttack stats_attack, ModifStatsPokemon stats_modif) {
	this->id_attack = id_attack;
	this->name = name;
	this->descriptive_attack = descriptive_attack;
	this->type = type;
	this->stats_attack = stats_attack;
	this->stats_modif = stats_modif;
}

IdAttack Attack::getIdAttack () {
	return id_attack;
}
std::string Attack::getName () {
	return name;
}
std::string Attack::getDescriptive () {
	return descriptive_attack;
}
Type Attack::getType () {
	return type;
}
StatsAttack Attack::getStatsAttack () {
	return stats_attack;
}
ModifStatsPokemon Attack::getStatsModif () {
	return stats_modif;
}
void Attack::setType (Type type) {
	this->type = type;
} 
void Attack::setStatsAttack (StatsAttack stats_attack) {
	this->stats_attack = stats_attack;
}
void Attack::setStatsModif (ModifStatsPokemon stats_modif) {
	this->stats_modif = stats_modif;
}

}

