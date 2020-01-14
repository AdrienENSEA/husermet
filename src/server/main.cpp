#include <iostream>
#include <unistd.h>
#include <memory>
#include <microhttpd.h>
#include <state.h>
#include <string.h>
#include <fstream>
#include <thread>

#include <sstream>
#include <cstring>

#include "engine.h"
#include "server.h"
#include "client.h"
#include "ai.h"


using namespace std;
using namespace state;
using namespace engine;
using namespace server;
using namespace client;
using namespace ai;

static int r;
static std::vector<int> order = {};
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
void automatic_run();

void thread_engine(void* ptr){
    static int i = 0;
    while (i<5) {
        if (r==2) {
        //cout << "test" << endl;

        //joueur.run(*ptr, ptr->getState(),window,0);
        engine::Engine* ptr_e=(engine::Engine*)ptr;

        ptr_e->runCommands(order);
        usleep(5000);
        r=0;
        i++;
        }
    }
}

class Request {
public:
    struct MHD_PostProcessor *pp = nullptr;
    string data;
    ~Request() {
        if (pp) MHD_destroy_post_processor (pp);
    }
};

// Détruit les données d'une requête
static void
request_completed (void *cls, struct MHD_Connection *connection,
                   void **con_cls, enum MHD_RequestTerminationCode toe)
{
  Request *request = (Request*)*con_cls;
  if (request) {
      delete request;
      *con_cls = nullptr;
  }
}

// Gestionnaire principal
static int
main_handler (void *cls,      
          struct MHD_Connection *connection,
          const char *url, // 
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr) 
{
    // Données pour une requête (en plusieurs appels à cette fonction)
    Request *request = (Request*)*ptr;

    // Premier appel pour cette requête
    if (!request) { 
        request = new Request();
        if (!request) {
            return MHD_NO;
        }
        *ptr = request;

        return MHD_YES;
    }    
    
    // Cas où il faut récupérer les données envoyés par l'utilisateur
    if (strcmp(method, MHD_HTTP_METHOD_POST) == 0
     || strcmp(method, MHD_HTTP_METHOD_PUT) == 0) {
        if (*upload_data_size != 0) {
            request->data = upload_data;
            *upload_data_size = 0;
            return MHD_YES;
        }    
    }

    HttpStatus status;
    string response;
    try {

        ServicesManager *manager = (ServicesManager*) cls;
        status = manager->queryService(response,request->data,url,method);
    }
    catch(ServiceException& e) {
        status = e.status();
        response = e.what();
        response += "\n";
    }
    catch(exception& e) {
        status = HttpStatus::SERVER_ERROR;
        response = e.what();
        response += "\n";
    }
    catch(...) {
        status = HttpStatus::SERVER_ERROR;
        response = "Unknown exception\n";
    }

    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(response.size(),(void *)response.c_str(),MHD_RESPMEM_MUST_COPY);
    if (strcmp(method,MHD_HTTP_METHOD_GET) == 0) {
        MHD_add_response_header(mhd_response,"Content-Type","application/json; charset=utf-8");
    }
    int ret = MHD_queue_response(connection, status, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}
int main(int argc, char* argv[])
{
    if (argc>1) {
        if (string(argv[1]) == "record") {
            cout << "Start of record : " << endl;
            // Run the code 
            automatic_run();
            // Copy of the json
            ifstream src("../res/command.json", ios::binary);
            ofstream dst("../res/replay.txt", ios::binary);
            dst << src.rdbuf();
        }
	    if (string(argv[1]) == "listen") {
		    cout << "Start of listen : " << endl;
		    Server server;
		    server.run();
	    }
	    if (string(argv[1]) == "client") {
		    cout << "Start of client : " << endl;
		    Server server1;
		    server1.talkwith();
	    }
        if(!strcmp(argv[1], "listen1")){
            cout << "starting" << endl;
            try {
                ServicesManager servicesManager;
                servicesManager.registerService(make_unique<VersionService>());
        /*
                UserDB userDB;
                userDB.addUser(make_unique<User>(1,1,1,1));
                servicesManager.registerService(make_unique<UserService>(std::ref(userDB)));
        */
                struct MHD_Daemon *d;
                d = MHD_start_daemon(// MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG | MHD_USE_POLL,
                        MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
                        // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG | MHD_USE_POLL,
                        // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
                        8080,
                        NULL, NULL, 
                        &main_handler, (void*) &servicesManager,
                        MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
                        MHD_OPTION_END);
                if (d == NULL)
                    return 1;
                cout << "Pressez <entrée> pour arrêter le serveur" << endl;
                (void) getc(stdin);
                MHD_stop_daemon(d);
            }
            catch(exception& e) {
                cerr << "Exception: " << e.what() << endl;
            }
        }
        return 0;
    }
}

void automatic_run() {
    int k = 0 ;
    engine::Engine e;
    std::thread t1(thread_engine, &e);
    while(k<4) {
        k++;
        sf::RenderWindow window;
        ai::HeuristicAI ia1;
        ai::HeuristicAI ia2;
        
        if (ia1.check_pv(e,window,0)==0) {
            ia1.run(e, e.getState(),0);
            //r=2;
        }
        if (ia2.check_pv(e, window, 1)==0) {
            ia2.run(e,e.getState(),1);
            r=2;
            if (ia2.check_pv(e,window,1)==1) return;
        }
        if (ia1.check_pv(e,window,0)==1 || ia2.check_pv(e,window,1)==1) {
            return;
        }
        for (int i =0; i<2; i++) {
            if (e.getState().getPokemon(6+i).getPV()==0) std::cout << e.getState().getPokemon(6+i).getName() << " ennemi est KO" << endl;
            if (e.getState().getPokemon(i).getPV()==0) std::cout << e.getState().getPokemon(i).getName() << " est KO" << endl;
        }
        cout << "Round n°" + to_string(k) + "Done" << endl;
    }
    
    e.writeJSON(e.getPastCommands());
}

