#include "Pokemon.h"
#include <iostream>

namespace state {

Pokemon::Pokemon () {
	id_pokemon = NONE_P;
    name = "name";
    Item i;
    item = &i;
    attacks = {};
    ability = 0;
    type = {NONE_T};
    state = NONE_S;
    stats_pokemon = {0,0,0,0,0};
    ev = 0;
}

Pokemon::Pokemon (IdPokemon id_pokemon, std::string name, Item item, std::vector <Attack> attacks, int ability, std::vector <Type> type, TypeState state, StatsPokemon stats_pokemon, int ev, int pv) {
	this->id_pokemon = id_pokemon;
    this->name = name;
    this->item = &item;
    this->attacks = attacks;
    this->ability = ability;
    this->type = type;
    this->state = state;
    this->stats_pokemon = stats_pokemon;
    this->ev = ev;
    this->pv = pv;
}

Pokemon::Pokemon (IdPokemon id_pokemon, std::string name, Item item, IdAttack id_attack1, IdAttack id_attack2, IdAttack id_attack3, IdAttack id_attack4, int ability, std::vector<Type> type, TypeState state, StatsPokemon stats_pokemon, int ev, int pv) :
id_pokemon(id_pokemon), name(name), attacks({AttackFactory::createAttack(id_attack1), AttackFactory::createAttack(id_attack2), AttackFactory::createAttack(id_attack3), AttackFactory::createAttack(id_attack4)}), ability(ability), ev(ev), pv(pv) {
    this->item = &item;
    this->type = type;
    this->state = state;
    this->stats_pokemon = stats_pokemon;
}
    
// Setters and Getters
IdPokemon Pokemon::getID () const{
	return id_pokemon;
}
std::string Pokemon::getName () const{
	return name;
}
Item& Pokemon::getItem () {
	return *item;
}
Attack& Pokemon::getAttack (int i) {
	return attacks.at(i);
}
std::vector<Attack> Pokemon::getAttacks () {
	return attacks;
}
std::vector <Type> Pokemon::getType () const {
	return type;
}
TypeState Pokemon::getState () const {
	return state;
}
StatsPokemon Pokemon::getStats () const {
	return stats_pokemon;
}
int Pokemon::getEV () const{
	return ev;
}
void Pokemon::setName (std::string name) {
	this->name = name;
}
void Pokemon::setItem (Item item) {
	this->item = &item;
}
/// 	
/// @param position		position de l'attaque a ajouter
/// @param attack		attaque a ajouter dans la liste
void Pokemon::setAttack (int position, Attack& attack) {
    std::vector<Attack>::iterator it = attacks.begin();
    advance(it, position); 
    attacks.insert(it, attack);
}
void Pokemon::setStatsPokemon (StatsPokemon& stats) {
	stats_pokemon = stats;
}
void Pokemon::setPV(int pv) {
    if (pv>0) this->pv = pv;
    else this->pv = 0;
}
int Pokemon::getPV() const {
    return pv;
}
void Pokemon::modifPV(int pv) {
    if (this->pv + pv > 0) this->pv += pv;
    else this->pv = 0;
}
}


