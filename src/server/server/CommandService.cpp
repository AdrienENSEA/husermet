#include "CommandService.h"
using namespace server;
using namespace std;

CommandService::CommandService () : AbstractService("/command") {
    
}

HttpStatus const CommandService::get (Json::Value& out, int id) {
    const User* user = userDB.getUser(id);
    if (id==2) const User* user2 = userDB.getUser(3);    
    else const User* user2 = userDB.getUser(2);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    if(user.post && user2.post) {
        vector<Command> commands = engine.getCommand();
        for (uint i=0; i<this->commands.size(); i++) {
            if (commands.at(i).getCommandID()!=0) {
                out["Command"+to_string(i)]["Pokemon"]         = commands.at(i).getPokemon(); 
                out["Command"+to_string(i)]["Pokemon_target"]  = commands.at(i).getPokemon_target();
                out["Command"+to_string(i)]["Attack"]          = commands.at(i).getAttack();
                out["Command"+to_string(i)]["Priority"]        = commands.at(i).getPriority();
                out["Command"+to_string(i)]["CommandID"]       = commands.at(i).getCommandID();
            }
        }
        user.post = false;
        user.get = true;
        return HttpStatus::OK;
    }
    else return HttpStatus::ACCEPTED;
}

HttpStatus CommandService::post (const Json::Value& in, int id) {
    const User* user = userDB.getUser(id);
    if (id==2) const User* user2 = userDB.getUser(3);    
    else const User* user2 = userDB.getUser(2);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    if(user.get && user2.get) {
        Command command;
        int i = 0;
        while (in.isMember("Command" + to_string(i)))
            command.getPokemon();  = in["Command"+to_string(i)]["Pokemon"].asInt();
            command.getPokemon_target(); = in["Command"+to_string(i)]["Pokemon_target"].asInt();
            command.getAttack(); = in["Command"+to_string(i)]["Attack"].asInt();
            command.getPriority(); = in["Command"+to_string(i)]["Priority"].asInt();
            command.getCommandID() = in["Command"+to_string(i)]["CommandID"].asInt();
            i++;
        }
        engine.addCommand(command);
        user.post = true
        user.get = false;
        return HttpStatus::NO_CONTENT;
    }
    else return HttpStatus::ACCEPTED;
}
