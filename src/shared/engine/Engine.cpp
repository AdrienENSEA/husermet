#include "Engine.h"
#include <iostream>
#include <stdlib.h>
#include <typeinfo>

namespace engine {

    Engine::Engine () {
        std::vector <Command> commands = {};
    }

    void Engine::runCommands (state::State &state) {
        while (!commands.empty()) {
            commands.at(0).execute(state);
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
                        int r = rand() % 2;
                        std::cout << r << std::endl;
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
        
    }
    void Engine::undoCommand () {
        commands.clear();
    }
    // Setters and Getters

};
