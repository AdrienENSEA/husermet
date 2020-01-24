#include "Engine.h"
#include <iostream>
#include <stdlib.h>
#include <typeinfo>
#include <string.h>

// For json
#include <json/json.h>
#include <fstream>

using namespace std;

namespace engine {

    Engine::Engine () :state() {
        std::vector <Command> commands = {};
        std::vector <Command> past_commands = {};
    }

    Engine::Engine (std::vector <int> list, state::TypeWeather weather, state::TypeTerrain terrain) {
        std::vector<state::Pokemon> battle = {};
        for (uint i=0; i<list.size();i++) {
            state::Pokemon p = state::PokemonFactory::createPokemon((state::IdPokemon)list.at(i));
            cout << "list" << p.getName() << p.getID();
            battle.push_back(p);
        }
        state::State s(battle,weather,terrain);
        this->state = s;
        std::vector <Command> commands = {};
        std::vector <Command> past_commands = {};
    }

    void Engine::runCommands (std::vector<int>& order, int player) {
        while (!commands.empty()) {
            
            if (state.getPokemon(commands.at(0).getPokemon()).getPV()!=0) {
                if (commands.at(0).getCommandID()==2) order.push_back(commands.at(0).getPokemon_target());
                commands.at(0).execute(state, player);
                cout << "target" << commands.at(0).getPokemon_target() << endl;
                past_commands.push_back(commands.at(0));
            }
            if (commands.at(0).getCommandID()==3  /*|| (state.getPokemon(commands.at(0).getPokemon()).getPV()==0 && commands.at(0).getCommandID()==1)*/) {
                commands.at(0).execute(state, player);
                past_commands.push_back(commands.at(0));
                if (commands.size()>1) {
                    for (uint i =1; i<commands.size(); i++) {
                        if (commands.at(i).getPokemon()==commands.at(0).getPokemon()) commands.erase(commands.begin()+i);
                    }
                }
            }
            commands.erase(commands.begin());
        }
    }
    state::State& Engine::getState() {
        return state;
    }
    void Engine::addCommand (Command command) {
        //state::State state = getState();
        //std::cout << "size debut" << commands.size() << std::endl;
        if (commands.size() == 0) {
            commands.insert(commands.begin(), command);
            //std::cout << "size fin vide" << commands.size() << std::endl;
        }
        else {
            for (uint i=0; i<commands.size(); i++) {
                if (commands.at(i).getPriority()<command.getPriority()) {
                    auto it = commands.begin()+i;
                    commands.insert(it, command);
                    //std::cout << "size fin prio" << commands.size() << std::endl;
                    break;
                }
                else if (commands.at(i).getPriority()==command.getPriority()) {
                    if (state.getPokemon(commands.at(i).getPokemon()).getStats().speed<state.getPokemon(command.getPokemon()).getStats().speed) {
                        auto it = commands.begin()+i;
                        commands.insert(it, command);
                        //std::cout << "size fin vit" << commands.size() << std::endl;
                        break;
                    }
                    else {
                        srand (time(NULL));
                        int r = rand() % 2;
                        if (r==0) {
                            auto it = commands.begin()+i;
                            commands.insert(it, command);
                            //std::cout << "size fin rand1" << commands.size() << std::endl;
                            break;
                        }
                        else {
                            auto it = commands.begin()+i+1;
                            commands.insert(it, command);
                            //std::cout << "size fin rand2" << commands.size() << std::endl;
                            break;
                        }
                    }
                }
                else if (i==commands.size()-1) {
                    auto it = commands.end();
                    commands.insert(it, command);
                    //std::cout << "size fin" << commands.size() << std::endl;
                    break;
                }
            }
        }
        //std::cout << "size fin" << commands.size() << std::endl;
        
    }
    
    void Engine::updateState(state::State& state) {
        this->state = state;
    }

    void Engine::undoCommand () {
        commands.clear();
    }
    // Setters and Getters
    
     
    void Engine::writeJSON (std::vector<Command> vect_command) {
        static int nbcommand = 0;
        // Open file
        fstream file_json;
        file_json.open("../res/command.json", fstream::out | fstream::in | fstream::app);
        cerr << "Error : " << strerror(errno) << endl;
        /*
        vect_command.at(0).toString();
        cout << endl;
        vect_command.at(1).toString();
        cout << endl;
        vect_command.at(2).toString();
        cout << endl;
        vect_command.at(3).toString();
        */
        //Create value
        Json::Value command_json;
        Json::StyledWriter styledwriter;
        
        // Command 1
        for (uint i=0; i<vect_command.size(); i++) {
            if (vect_command.at(i).getCommandID()!=0) {
                command_json["Command"+to_string(i)]["Pokemon"]         = vect_command.at(i).getPokemon(); 
                command_json["Command"+to_string(i)]["Pokemon_target"]  = vect_command.at(i).getPokemon_target();
                command_json["Command"+to_string(i)]["Attack"]          = vect_command.at(i).getAttack();
                command_json["Command"+to_string(i)]["Priority"]        = vect_command.at(i).getPriority();
                command_json["Command"+to_string(i)]["CommandID"]       = vect_command.at(i).getCommandID();
            }
        }
        // Write output
        file_json << styledwriter.write(command_json);
        nbcommand++;
        file_json.close();
        
    }

    void Engine::readJSON (std::vector<Command>& vect_command) {
        static int nbstep = 0;
        // Open file
        fstream file_json;
        file_json.open("../res/command.json", fstream::in);

        //Create value
        Json::Value command_json;
        Json::Reader reader;
        engine::Command command(0);
        
        if(!reader.parse(file_json, command_json))
            cout << "error parse" << endl;
        
        // Read all the 4 commands
        for (uint i=0;i<21;i++) {
            command.setPokemon(         command_json["Command"+to_string(i)]["Pokemon"].asInt());
            command.setPokemon_target(  command_json["Command"+to_string(i)]["Pokemon_target"].asInt());
            command.setAttack(          command_json["Command"+to_string(i)]["Attack"].asInt());
            command.setPriority(        command_json["Command"+to_string(i)]["Priority"].asInt());
            command.setCommandID(       command_json["Command"+to_string(i)]["CommandID"].asInt());
            //command.toString();
            if (command.getCommandID()!=0) vect_command.push_back(command);
        }
        
        nbstep++;
        // CLose file
        file_json.close();
        //return vect_command;
    }
    
    Json::Value Engine::writeJSON1v1 () {
        //static int nbcommand = 0;

        //Create value
        Json::Value command_json;
        
        // Command 1
        for (uint i=0; i<this->commands.size(); i++) {
            if (commands.at(i).getCommandID()!=0) {
                command_json["Command"+to_string(i)]["Pokemon"]         = commands.at(i).getPokemon(); 
                command_json["Command"+to_string(i)]["Pokemon_target"]  = commands.at(i).getPokemon_target();
                command_json["Command"+to_string(i)]["Attack"]          = commands.at(i).getAttack();
                command_json["Command"+to_string(i)]["Priority"]        = commands.at(i).getPriority();
                command_json["Command"+to_string(i)]["CommandID"]       = commands.at(i).getCommandID();
            }
        }

        return command_json;
        
    }

    void Engine::readJSON1v1 (std::vector<Command>& vect_command) {
        static int nbstep = 0;
        // Open file
        fstream file_json;
        file_json.open("../res/commandAdv.json", fstream::in);

        //Create value
        Json::Value command_json;
        Json::Reader reader;
        engine::Command command(0);
        
        if(!reader.parse(file_json, command_json))
            cout << "error parse" << endl;
        
        // Read all the 4 commands
        for (uint i=0;i<21;i++) {
            command.setPokemon(         command_json["Command"+to_string(i)]["Pokemon"].asInt());
            command.setPokemon_target(  command_json["Command"+to_string(i)]["Pokemon_target"].asInt());
            command.setAttack(          command_json["Command"+to_string(i)]["Attack"].asInt());
            command.setPriority(        command_json["Command"+to_string(i)]["Priority"].asInt());
            command.setCommandID(       command_json["Command"+to_string(i)]["CommandID"].asInt());
            //command.toString();
            if (command.getCommandID()!=0) vect_command.push_back(command);
            else i=21;
        }
        
        nbstep++;
        // CLose file
        file_json.close();
        //return vect_command;
    }

    std::vector<Command>& Engine::getPastCommands() {
        return past_commands;
    }

    std::vector<Command>& Engine::getCommands() {
        return commands;
    }

    void Engine::setPastCommands(Command command) {
        past_commands.push_back(command);
    }
};
