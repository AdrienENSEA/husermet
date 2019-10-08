#include "Attack.h"

namespace state {

IdAttack Attack::getIdAttack () {
    return id_attack;
}
void Attack::setIdAttack (IdAttack id) {
    id_attack = id;
}
std::string Attack::getName () {
    return name;
}
void Attack::setName (std::string n) {
    name = n;
}
Type Attack::getType () {
    return type;
}

}

