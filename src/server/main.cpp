#include <iostream>
#include <unistd.h>

#include <state.h>
#include <string.h>
#include <fstream>
#include "engine.h"
#include "server.h"


using namespace std;
using namespace state;
using namespace engine;
using namespace server;

int main(int argc, char* argv[])
{
	
    if (argc>1) {
        if (string(argv[1]) == "record") {
            cout << "Start of record : " << endl;
            // Copy of the json
            ifstream src("../res/command.json", ios::binary);
            ofstream dst("../res/replay.txt", ios::binary);
            dst << src.rdbuf();
        }
	    if (string(argv[1]) == "listen") {
		    cout << "Start of listen : " << endl;
		    Server server;
		    server.run();
		    Server server1;
		    server1.talkwith();
	    }
    
    else {
        cout << "Veuillez ajouté record ou listen en argument" << endl;
    }
    
    return 0;
}
}
