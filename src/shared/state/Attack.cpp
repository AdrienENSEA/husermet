#include "Attack.h"

namespace state {

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
Type Attack::getType () {
	return type;
}
void Attack::setType (Type type) {
	this->type = type;
}

}

