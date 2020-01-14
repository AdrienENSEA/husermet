#include "UserService.h"
using namespace server;
using namespace std;

UserService::UserService (UserDB& userDB) : AbstractService("/user"),
    userDB(userDB) {
    
}

HttpStatus const UserService::get (Json::Value& out, int id) {
    const User* user = userDB.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    out["pokemon1"] = user->pokemon1;
    out["pokemon2"] = user->pokemon2;
    out["pokemon3"] = user->pokemon3;
    out["pokemon4"] = user->pokemon4;
    return HttpStatus::OK;
}

HttpStatus UserService::post (const Json::Value& in, int id) {
    const User* user = userDB.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    unique_ptr<User> usermod (new User(*user));
    if (in.isMember("pokemon1")) {
        usermod->pokemon1 = in["pokemon1"].asInt();
    }
    if (in.isMember("pokemon2")) {
        usermod->pokemon2 = in["pokemon2"].asInt();
    }
    if (in.isMember("pokemon3")) {
        usermod->pokemon3 = in["pokemon3"].asInt();
    }
    if (in.isMember("pokemon4")) {
        usermod->pokemon3 = in["pokemon4"].asInt();
    }
    userDB.setUser(id,std::move(usermod));
    return HttpStatus::NO_CONTENT;
}

HttpStatus UserService::put (Json::Value& out,const Json::Value& in) {
    int pokemon3 = in["pokemon3"].asInt();
    int pokemon4 = in["pokemon4"].asInt();
    int pokemon1 = in["pokemon1"].asInt();
    int pokemon2 = in["pokemon2"].asInt();
    std::unique_ptr<User> user;
    out["id"] = userDB.addUser(move(user));//pokemon1,pokemon2,pokemon3,pokemon4));
    return HttpStatus::CREATED;
}

HttpStatus UserService::remove (int id) {
    const User* user = userDB.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    userDB.removeUser(id);
    return HttpStatus::NO_CONTENT;
}
