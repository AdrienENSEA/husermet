#include <iostream>
#include <unistd.h>

#include <state.h>
#include <string.h>
#include <fstream>
#include <thread>
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
    }
    else {
        cout << "Veuillez ajouté record ou listen en argument" << endl;
    }
    
    return 0;
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

