#include "ServicesManager.h"
#include <iostream>

using namespace std;
using namespace server;
static int connect = 0;
void ServicesManager::registerService (unique_ptr<AbstractService> service) {
    services.push_back(std::move(service));
}

AbstractService* ServicesManager::findService (const string& url) const {
    for (auto& service : services) {
        const string& pattern(service->getPattern());
        if (url.find(pattern) != 0)
            continue;
        if (url.size() > pattern.size() && url[pattern.size()] != '/')
            continue;
        return service.get();
    }
    return nullptr;
}

HttpStatus ServicesManager::queryService (string& out, const string& in, const string& url, const string& method) { 
    AbstractService* service = findService(url);
    if (!service)
        throw ServiceException(HttpStatus::NOT_FOUND,"Service "+url+" non trouvé");
    // Recherche un éventuel id (ex: /mon/service/<id>)
    const string& pattern(service->getPattern());
    int id = 0;
    if (url.size() > pattern.size()) {
        string end = url.substr(pattern.size());
        if (end[0] != '/')
            throw ServiceException(HttpStatus::BAD_REQUEST,"Url malformée (forme attendue: <service>/<nombre>)");
        end = end.substr(1);
        if (end.empty())
            throw ServiceException(HttpStatus::BAD_REQUEST,"Url malformée (forme attendue: <service>/<nombre>)");
        try {
            size_t pos = 0;
            id = stoi(end,&pos);
            if (pos != end.size())
                throw ServiceException(HttpStatus::BAD_REQUEST,"Url malformée: '"+end+"' n'est pas un nombre");
        }
        catch(...) {
            throw ServiceException(HttpStatus::BAD_REQUEST,"Url malformée: '"+end+"' n'est pas un nombre");
        }
    }
    // Traite les différentes méthodes
    if (method == "GET") {
        cerr << "Requête GET " << pattern << " avec id=" << id << endl;
        Json::Value jsonOut;
        HttpStatus status;
        /*
        if (connect>1) connect++;
        if (id == 2 && connect == 1) connect = 2;
        if (id == 3 && connect == 0) connect = 1;
        */
        if (pattern == "/command") 
        //if (connect == 6) 
            status = ((CommandService*)service)->get(jsonOut,id);
        else
            status = ((UserService*)service)->get(jsonOut,id);
        //cout << "connect" << connect << endl;
        out = jsonOut.toStyledString();
        return status;
    }
    else if (method == "POST") {
        cerr << "Requête POST " << pattern << " avec contenu: " << in << endl;
        Json::Reader jsonReader;
        Json::Value jsonIn;
        if (!jsonReader.parse(in,jsonIn))
            throw ServiceException(HttpStatus::BAD_REQUEST,"Données invalides: "+jsonReader.getFormattedErrorMessages());
        return ((CommandService*)service)->post(jsonIn,id);
    }
    else if (method == "PUT") {
        cerr << "Requête PUT " << pattern << " avec contenu: " << in << endl;
        Json::Reader jsonReader;
        Json::Value jsonIn;
        if (!jsonReader.parse(in,jsonIn))
            throw ServiceException(HttpStatus::BAD_REQUEST,"Données invalides: "+jsonReader.getFormattedErrorMessages());
        Json::Value jsonOut;
        HttpStatus status = service->put(jsonOut,jsonIn);
        out = jsonOut.toStyledString();
        return status;
    }
    else if (method == "DELETE") {
        cerr << "Requête DELETE" << endl;
        return service->remove(id);
    }
    throw ServiceException(HttpStatus::BAD_REQUEST,"Méthode "+method+" invalide");
}
