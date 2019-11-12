#include "Item.h"

namespace state {

Item::Item() {
    id_item = NONE_I;
    name = "name";
    descriptive_effect = "descriptive_effect";
    effect_stats = {0,0,0,0,0,0};
    effect_state = NONE_S;
    effect_type = NONE_T;
}

Item::Item(IdItem id_item, std::string name, std::string descriptive_effect, StatsPokemon effect_stats, TypeState effect_state, Type effect_type) {
    this->id_item = id_item;
    this->name = name;
    this->descriptive_effect = descriptive_effect;
    this->effect_stats = effect_stats;
    this->effect_state = effect_state;
    this->effect_type = effect_type;
}

// Setters and Getters
IdItem Item::getIdItem () const {
	return id_item;
}
std::string Item::getName () const {
	return name;
}
std::string Item::getDescriptive () const {
	return descriptive_effect;
}
StatsPokemon Item::getEffectStats () const {
	return effect_stats;
}
void Item::setEffectStats (StatsPokemon stats) {
	effect_stats = stats;
}
TypeState Item::getEffectState () const {
	return effect_state;
}
void Item::setEffectState (TypeState effect_state) {
	this->effect_state = effect_state;
}
Type Item::getEffectType () const {
	return effect_type;
}
void Item::setEffectType (Type effect_type) {
	this->effect_type = effect_type;
}

}
