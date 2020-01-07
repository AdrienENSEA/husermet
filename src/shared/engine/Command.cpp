#include "Command.h"
#include <iostream>
#include <stdlib.h>
#include <typeinfo>
#include <string.h>
// For json
#include <json/json.h>
#include <fstream>

using namespace std;

namespace engine {

    Command::Command (int commandID) : commandID(commandID) {

    }
    void Command::writeJSON (Command command) {
        static int nbcommand=0;
        // Open file
        fstream file_json;
        file_json.open("../res/command.json", fstream::out | fstream::in | fstream::app);
        cerr << "Error : " << strerror(errno) << endl;
        
        command.toString();
        cout << endl;
        
        //Create value
        Json::Value command_json;
        Json::StyledWriter styledwriter;
        
        // Command 1
        command_json["Command"+to_string(nbcommand)]["Pokemon"]         = command.getPokemon(); 
        command_json["Command"+to_string(nbcommand)]["Pokemon_target"]  = command.getPokemon_target();
        command_json["Command"+to_string(nbcommand)]["Attack"]          = command.getAttack();
        command_json["Command"+to_string(nbcommand)]["Priority"]        = command.getPriority();
        command_json["Command"+to_string(nbcommand)]["CommandID"]       = command.getCommandID();
        
        // Write output
        file_json << styledwriter.write(command_json);
        nbcommand++;
        file_json.close();
        
    }
    void Command::readJSON (Command& command) {
        static int nbstep = 0;
        // Open file
        fstream file_json;
        file_json.open("../res/command.json", fstream::in);
        
        //Create value
        Json::Value command_json;
        Json::Reader reader;
        
        if(!reader.parse(file_json, command_json))
            cout << "error" << endl;
        
        // Read the command
        command.setPokemon(         command_json["Command"+to_string(nbstep)]["Pokemon"].asInt());
        command.setPokemon_target(  command_json["Command"+to_string(nbstep)]["Pokemon_target"].asInt());
        command.setAttack(          command_json["Command"+to_string(nbstep)]["Attack"].asInt());
        command.setPriority(        command_json["Command"+to_string(nbstep)]["Priority"].asInt());
        command.setCommandID(       command_json["Command"+to_string(nbstep)]["CommandID"].asInt());
        toString();
        
        nbstep++;
        // CLose file
        file_json.close();
        //return nbstep;
    }
    void Command::execute (state::State& state) {
        //writeJSON(*this);
        if (commandID==1) {
            ChangePokemonCommand c(pokemon, pokemon_target);
            c.execute(state);
        }
        if (commandID==3) {
            ChangePokemonCommand c(pokemon, pokemon_target);
            c.execute(state);
            toString();
        }
        if (commandID==2) {
            AttackCommand a(pokemon, pokemon_target, attack);
            a.execute(state);
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
        cout << endl;
    }


};
