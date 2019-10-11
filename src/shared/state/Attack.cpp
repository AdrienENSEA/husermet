#include "Attack.h"

namespace state {

IdAttack Attack::getIdAttack () {
    return id_attack;
}
std::string Attack::getName () {
    return name;
}
Type Attack::getType () {
    return type;
}

}

