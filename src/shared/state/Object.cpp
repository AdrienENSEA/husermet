#include "Object.h"

namespace state {

Object::Object(IdObject id_object, std::string name, std::string descriptive_effect, StatsPokemon effect_stats, TypeState effect_state, Type effect_type) {
    this->id_object = id_object;
    this->name = name;
    this->descriptive_effect = descriptive_effect;
    this->effect_stats = effect_stats;
    this->effect_state = effect_state;
    this->effect_type = effect_type;
}
/*
IdObject Object::getIdObject () {
	return id_object;
}
void Object::setIdObject (IdObject id) {
	
}
std::string Object::getName () {
	return name;
}
void Object::setName (std::string name) {
	
}
std::string Object::getDescriptive () {
	return descriptive_effect;
}
void Object::setDescriptive (std::string descriptive) {
	
}*/
StatsPokemon Object::getEffectStats () {
	return effect_stats;
}
void Object::setEffectStats (StatsPokemon stats) {
	effect_stats = stats;
}
TypeState Object::getEffectState () {
	return effect_state;
}
void Object::setEffectState (TypeState effect_state) {
	this->effect_state = effect_state;
}
Type Object::getEffectType () {
	return effect_type;
}
void Object::setEffectType (Type effect_type) {
	this->effect_type = effect_type;
}
// Setters and Getters

}
