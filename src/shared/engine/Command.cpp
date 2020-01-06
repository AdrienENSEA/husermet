#include "Command.h"
#include <iostream>

using namespace std;

namespace engine {

    Command::Command (int commandID) : commandID(commandID) {

    }

    void Command::execute (state::State& state) {
        if (commandID==1) {
            ChangePokemonCommand c(pokemon, pokemon_target);
            c.execute(state);
        }
        if (commandID==2) {
            AttackCommand a(pokemon, pokemon_target, attack);
            a.execute(state);
        }
        if (commandID == 3) {
            /*
            int i=0;
            while (state.getPokemon(i).getPV()==0) {
                if (i==5) {
                    state.set(0);
                    break;
                }
                else i++;
            }
            i=6;
            while (state.getPokemon(i).getPV()==0) {
                if (i==11) {
                    state.set(1);
                    break;
                }
                else i++;
            }*/
            
        }
    }

    // Setters and Getters
    int Command::getPokemon() const {
        return pokemon;
    }
    void Command::setPokemon(int pokemon) {
        this->pokemon = pokemon;
    }
    int Command::getPokemon_target() const {
        return pokemon_target;
    }
    void Command::setPokemon_target(int pokemon_target) {
        this->pokemon_target = pokemon_target;
    }
    int Command::getAttack() const {
        return attack;
    }
    void Command::setAttack(int attack) {
        this->attack = attack;
    }
    int Command::getPriority() const {
        return priority;
    }
    void Command::setPriority(int priority) {
        this->priority = priority;
    }
    int Command::getCommandID() const {
        return commandID;
    }
    void Command::setCommandID(int commandID) {
        this->commandID = commandID;
    }
    void Command::toString() {
        cout << " Pokemon : "           << to_string(this->pokemon) << endl;
        cout << " Pokemon target : "    << to_string(this->pokemon_target) << endl;
        cout << " Attack : "            << to_string(this->attack) << endl;
        cout << " Priority : "          << to_string(this->priority) << endl;
        cout << " CommandID : "         << to_string(this->commandID) << endl;
    }


};
