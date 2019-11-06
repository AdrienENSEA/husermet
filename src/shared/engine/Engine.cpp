#include "Engine.h"
#include <iostream>


namespace engine {

    Engine::Engine (state::State* state) {
        std::vector <Command> commands = {};
        this->state = state;
    }

    void Engine::runCommands () {
        while (!commands.empty()) {
            commands.at(0).execute(state);
            commands.erase(commands.begin());
        }   
        
    }
    void Engine::addCommand (Command command) {
        int p;
        if (commands.size() == 0) {
            commands.insert(commands.begin(), command);
        }
        for (uint i=0; i<commands.size(); i++) {
            p = commands.at(i).getPriority();
            if (p<command.getPriority()) {
                auto it = commands.begin()+i;
                commands.insert(it, command);
                break;
            }
        }
    }
    void Engine::undoCommand () {
        commands.clear();
    }
    // Setters and Getters

};
