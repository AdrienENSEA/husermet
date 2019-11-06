#include "AttackCommand.h"

namespace engine {

    AttackCommand::AttackCommand () {
        priority = 0;
        commandID = 2;
    }
    void AttackCommand::execute (state::State* state) {
    }
// Setters and Getters
    state::Attack AttackCommand::getAttack() const {
        return attack;
    }
    void AttackCommand::setAttack(state::Attack attack) {
        this->attack = attack;
    }

};
