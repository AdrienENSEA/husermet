#include "UserService.h"
using namespace server;
using namespace std;
#include <iostream>

UserService::UserService (UserDB& userDB) : AbstractService("/user"),
    userDB(userDB) {
    
}

HttpStatus const UserService::get (Json::Value& out, int id) {
    cout << "get user" << endl;
    const User* user = userDB.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    out["Pokemon1"] = user->pokemon1;
    out["Pokemon2"] = user->pokemon2;
    out["Pokemon3"] = user->pokemon3;
    out["Pokemon4"] = user->pokemon4;
    out["Pokemon5"] = user->pokemon5;
    out["Pokemon6"] = user->pokemon6;
    out["Name"] = user->name;
    return HttpStatus::OK;
}

HttpStatus UserService::post (const Json::Value& in, int id) {
    const User* user = userDB.getUser(id);
    cout << to_string(id) << endl;
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    unique_ptr<User> usermod (new User(*user));
    if (in.isMember("Pokemon1")) {
        usermod->pokemon1 = in["Pokemon1"].asInt();
    }
    if (in.isMember("Pokemon2")) {
        usermod->pokemon2 = in["Pokemon2"].asInt();
    }
    if (in.isMember("Pokemon3")) {
        usermod->pokemon3 = in["Pokemon3"].asInt();
    }
    if (in.isMember("Pokemon4")) {
        usermod->pokemon4 = in["Pokemon4"].asInt();
    }
    if (in.isMember("Pokemon5")) {
        usermod->pokemon5 = in["Pokemon5"].asInt();
    }
    if (in.isMember("Pokemon6")) {
        usermod->pokemon6 = in["Pokemon6"].asInt();
    }
    if (in.isMember("Name")) {
        usermod->name = in["Name"].asString();
    }
    userDB.setUser(id,std::move(usermod));
    return HttpStatus::NO_CONTENT;
}

HttpStatus UserService::put (Json::Value& out,const Json::Value& in) {
    int pokemon1 = in["Pokemon1"].asInt();
    int pokemon2 = in["Pokemon2"].asInt();
    int pokemon3 = in["Pokemon3"].asInt();
    int pokemon4 = in["Pokemon4"].asInt();
    int pokemon5 = in["Pokemon5"].asInt();
    int pokemon6 = in["Pokemon6"].asInt();
    string name = in["Name"].asString();
    out["id"] = userDB.addUser(std::unique_ptr<User> (new User(name,pokemon1,pokemon2,pokemon3,pokemon4,pokemon5,pokemon6)));
    return HttpStatus::CREATED;
}

HttpStatus UserService::remove (int id) {
    const User* user = userDB.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    userDB.removeUser(id);
    return HttpStatus::NO_CONTENT;
}
