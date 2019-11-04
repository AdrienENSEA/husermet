#include "Engine.h"

namespace engine {

    Engine::Engine () {
        std::vector <Command> commands = {};
    }

    void Engine::runCommands () {
        while (!commands.empty()) {
            commands.at(0).execute(state);
            commands.erase(commands.begin());
        }   
        
    }
    void Engine::addCommand (Command command, int priority) {
        Command c;
        c.setPriority(priority);
        
         
    }
    void Engine::undoCommand () {
    }
    // Setters and Getters

};
