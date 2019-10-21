#include "Scene.h"

namespace render {

Scene::Scene () {
    uint height = 512;
}

Attack::Attack (IdAttack id_attack, std::string name, std::string descriptive_attack, Type type, StatsAttack stats_attack, ModifStatsPokemon stats_modif) {
	this->id_attack = id_attack;
	this->name = name;
	this->descriptive_attack = descriptive_attack;
	this->type = type;
	this->stats_attack = stats_attack;
	this->stats_modif = stats_modif;
}

void Attack::Scene (ModifStatsPokemon stats_modif) {
	this->stats_modif = stats_modif;
}

}

