#include "CommandService.h"
using namespace server;
using namespace std;
#include <iostream>

CommandService::CommandService () : AbstractService("/command"){
    post1 = false;
    post2 = false;
    get1 = true;
    get2 = true;
}

HttpStatus const CommandService::get (Json::Value& out, int id) {
    cout << "get command" << endl;
    if(post1 && post2) {
        vector<engine::Command> commands = engine.getCommands();
        for (uint i=0; i<commands.size(); i++) {
            if (commands.at(i).getCommandID()!=0) {
                out["Command"+to_string(i)]["Pokemon"]         = commands.at(i).getPokemon(); 
                out["Command"+to_string(i)]["Pokemon_target"]  = commands.at(i).getPokemon_target();
                out["Command"+to_string(i)]["Attack"]          = commands.at(i).getAttack();
                out["Command"+to_string(i)]["Priority"]        = commands.at(i).getPriority();
                out["Command"+to_string(i)]["CommandID"]       = commands.at(i).getCommandID();
            }
        }
        if (id%2) {
        post1 = false;
        get1 = true; }
        else {
        post2 = false;
        get2 = true; }
        return HttpStatus::OK;
    }
    else return HttpStatus::OK;//ACCEPTED;
}

HttpStatus CommandService::post (const Json::Value& in, int id) {
    cout << "post command" << endl;
    if(get1 && get2) {
        engine::Command command(0);
        int i = 0;
        while (in.isMember("Command" + to_string(i))) {
            command.setPokemon(         in["Command"+to_string(i)]["Pokemon"].asInt());
            command.setPokemon_target(  in["Command"+to_string(i)]["Pokemon_target"].asInt());
            command.setAttack(          in["Command"+to_string(i)]["Attack"].asInt());
            command.setPriority(        in["Command"+to_string(i)]["Priority"].asInt());
            command.setCommandID(       in["Command"+to_string(i)]["CommandID"].asInt());
            i++;
        }
        engine.addCommand(command);
        if (id%2) {
        post1 = true;
        get1 = false; }
        else { 
        post2 = true;
        get2 = false; }        
        return HttpStatus::CREATED;
    }
    else return HttpStatus::ACCEPTED;
}


HttpStatus CommandService::put (Json::Value& out,const Json::Value& in) { 

}


HttpStatus CommandService::remove (int id) { }





