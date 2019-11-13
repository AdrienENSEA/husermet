#include "Attack.h"
#include <iostream>

namespace state {

Attack::Attack () {
    id_attack = NONE_A;
	name = "name";
	descriptive_attack = "descriptive_attack";
	type = NONE_T;
	struct StatsAttack sa = {0,0,0,0,0,0}; 
    stats_attack = sa;
    ModifStatsPokemon s;
	stats_modif = s;
}

Attack::Attack (IdAttack id_attack, std::string name, std::string descriptive_attack, Type type, struct StatsAttack stats_attack, ModifStatsPokemon stats_modif, int pp) {
	this->id_attack = id_attack;
	this->name = name;
	this->descriptive_attack = descriptive_attack;
	this->type = type;
	this->stats_attack = stats_attack;
	this->stats_modif = stats_modif;
    this->pp = pp;
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
StatsAttack& Attack::getStatsAttack () {
	return stats_attack;
}
ModifStatsPokemon Attack::getStatsModif () const{
	return stats_modif;
}
void Attack::setType (Type type) {
	this->type = type;
} 
void Attack::setStatsAttack (StatsAttack& stats_attack) {
	this->stats_attack = stats_attack;
}
void Attack::setStatsModif (ModifStatsPokemon& stats_modif) {
	this->stats_modif = stats_modif;
}
int Attack::getPP() const{
	//std::cout << "apres getPP a" << pp << std::endl;
    return pp;
}
void Attack::modifPP(int pp) {
    if (this->pp + pp > 0) this->pp += pp;
	else this->pp = 0;
}
void Attack::setPP(int pp) {
	if (pp>0) this->pp = pp;
    else this->pp = 0;
    //std::cout << "apres setPP a" << pp << std::endl;
}
}

