#include "Attack.h"
#include <iostream>

namespace state {

Attack::Attack () {
    id_attack = NONE_A;
	name = "name";
	descriptive_attack = "descriptive_attack";
	type = NONE_T;
	struct StatsAttack sa = {0,0,0,0,0,0,0}; 
    stats_attack = sa;
    ModifStatsPokemon s;
	stats_modif = s;
}

Attack::Attack (IdAttack id_attack, std::string name, std::string descriptive_attack, Type type, struct StatsAttack stats_attack, ModifStatsPokemon stats_modif) {
	this->id_attack = id_attack;
	this->name = name;
	this->descriptive_attack = descriptive_attack;
	this->type = type;
	this->stats_attack = stats_attack;
	this->stats_modif = stats_modif;
}

// Setters and Getters
IdAttack Attack::getIdAttack () const {
	return id_attack;
}
std::string Attack::getName () const {
	return name;
}
std::string Attack::getDescriptive () const {
	return descriptive_attack;
}
Type Attack::getType () const {
	return type;
}
StatsAttack Attack::getStatsAttack () const {
	return stats_attack;
}
ModifStatsPokemon Attack::getStatsModif () const{
	return stats_modif;
}
void Attack::setType (Type type) {
	this->type = type;
} 
void Attack::setStatsAttack (StatsAttack stats_attack) {
	this->stats_attack = stats_attack;
std::cout << "attack stats pp ppmax " << stats_attack.pp << stats_attack.ppmax << std::endl;
}
void Attack::setStatsModif (ModifStatsPokemon stats_modif) {
	this->stats_modif = stats_modif;
}
int Attack::getPP(){
    return stats_attack.pp;
}
void Attack::modifPP(int pp) {
    std::cout << stats_attack.pp << "+" << pp << "=";
    stats_attack.pp += pp;
    std::cout << stats_attack.pp << std::endl;
}

}

