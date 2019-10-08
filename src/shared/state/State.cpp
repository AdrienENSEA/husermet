#include "State.h"

namespace state {

void State::changeTeam (int fighter, int position, Pokemon pokemon) {
    
}
void State::changeArena (int type_arena) {
    
}
TypeArena State::getTypeArena () {
    return arena;
}
void State::setTypeArena (TypeArena a) {
    arena = a;
}
TypeWeather State::getWeather () {
    return weather;
}
    /// 	
    /// @param weather		(???) 
void State::setWeather (TypeWeather w) {
    weather = w;
}

}

