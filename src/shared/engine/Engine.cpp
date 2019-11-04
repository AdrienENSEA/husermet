#include "Engine.h"

namespace engine {

    Engine::Engine (state::State& state) {
        this->state = state;
        std::vector <Command> commands = {};
    }

    void Engine::runCommands () {
        auto it = commands.begin();
        while (it != commands.cend()) {
            commands.at(it).execute(state);
            commands.erase(it);
            it++
        }   
        
    }
    void Engine::addCommand (Command command, int priority) {
        Command c;
        
         
    }
    void Engine::undoCommand () {
    }
    // Setters and Getters

};
