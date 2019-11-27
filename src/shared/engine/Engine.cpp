#include "Engine.h"
#include <iostream>
#include <stdlib.h>
#include <typeinfo>

namespace engine {

    Engine::Engine () {
        std::vector <Command> commands = {};
    }

    void Engine::runCommands (state::State &state, std::vector<int>& order) {
        while (!commands.empty()) {
            if (state.getPokemon(commands.at(0).getPokemon()).getPV()!=0 || commands.at(0).getCommandID()==1) {
                if (commands.at(0).getCommandID()==2) order.push_back(commands.at(0).getPokemon_target());
                commands.at(0).execute(state);
            }
            commands.erase(commands.begin());
        }   
    }

    void Engine::addCommand (Command command, state::State& state) {
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
    
    void Engine::undoCommand () {
        commands.clear();
    }
    // Setters and Getters

};
