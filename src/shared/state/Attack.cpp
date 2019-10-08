#include "Attack.h"

namespace state {

IdAttack Attack::getIdAttack () {
    return idAttack;
}
void Attack::setIdAttack (IdAttack id) {
    idAttack = id;
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

