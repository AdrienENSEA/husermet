#include "Client.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>

// For json
#include <json/json.h>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#define PORT 8080
#define URL "http://localhost"

using namespace std;
static int ai_type = 4;
static int p, a, r, c;
static std::vector<int> order = {};
static int id1;
static int player;

void commandAdv(engine::Engine& e) {

        cout << "Command Adverse parsing " << endl;

        int id_adv;
        if (id1 == 2) id_adv = 3;
        else id_adv = 2;

        Json::Value command_json = e.writeJSON1v1();
        sf::Http http(URL,PORT);
        sf::Http::Response response;
        sf::Http::Request req;
        req.setMethod(sf::Http::Request::Post);
        req.setBody(command_json.toStyledString());
        req.setUri("/command/"+to_string(id_adv));
        req.setField("Content-Type", "application/json");
        Json::FastWriter fastwriter;
        string output = fastwriter.write(command_json);
        cout << "Sending /command : " << endl << output << endl;
        response = http.sendRequest(req);
        while (response.getStatus() == sf::Http::Response::Accepted) {
            sleep(2);
            cout << "Waiting for the other player to play" << endl;
            response = http.sendRequest(req);
        }

        e.undoCommand();
        e.undoCommand();

        sf::Http::Response response_get;
        sf::Http::Request req_get("/command/"+to_string(id_adv), sf::Http::Request::Get);
        cout << "Getting /command" << endl;
        do {
            sleep(2);
            response_get = http.sendRequest(req_get);
        }
        while(response_get.getStatus() != sf::Http::Response::Ok);
        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(response_get.getBody(), root, false))
        {
            cout << reader.getFormattedErrorMessages() << endl;
        }
        e.readJSON1v1(root);
    }

void thread_engine(void* ptr){
    engine::Engine* ptr_e=(engine::Engine*)ptr;
    while (1) {
        if (r==2) {
            commandAdv(*ptr_e);
            ptr_e->runCommands(order, player);
            r=0;
        }
    }
}

void thread_play(void* ptr){
    engine::Engine* ptr_e=(engine::Engine*)ptr;
    std::vector<engine::Command> vect;
        ptr_e->readJSON(vect);
        for (uint i=0; i<vect.size();i++) {
            if (vect.at(i).getCommandID()==2) order.push_back(vect.at(i).getPokemon_target());
            vect.at(i).execute(ptr_e->getState(),player);
            sleep(1);
        }
}

namespace client {

    Client::Client () {

    }

    void Client::run() {
        sf::RenderWindow window(sf::VideoMode(512, 512), "Fight");
        render::Scene s;
        engine::Engine e;
        ai::HeuristicAI joueur;
        ai::RandomAI ia1;
        ai::HeuristicAI ia2;
        ai::DeepAI ia3;
        int x, y;
        s.draw(e,window);
        std::thread t1(thread_engine, &e);
        while (window.isOpen()) {
            sf::Event event;
            int target=0;

            if(e.getState().getPokemon(0).getPV()==0 && r==0) {
                std::cout << e.getState().getPokemon(0).getName() << " est KO" << std::endl;
                if (e.getState().getPokemon(2).getPV()==0 && e.getState().getPokemon(3).getPV()==0 && e.getState().getPokemon(4).getPV()==0 && e.getState().getPokemon(5).getPV()==0) {
                    if (e.getState().getPokemon(0).getPV()<=0 && e.getState().getPokemon(1).getPV()<=0) {
                        std::cout << "Défaite" << std::endl;
                        //e.writeJSON(e.getPastCommands());
                        window.close();
                    }
                    r=1;
                    p=1;
                }
                else {
                    while (r==0) {
                        while (window.pollEvent(event) && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x>390 && event.mouseButton.y>410 && e.getState().getPokemon(s.convertP(event.mouseButton.x,event.mouseButton.y)).getPV()!=0) {
                            setCommand(e.getState(),e,event.mouseButton.x,event.mouseButton.y, ai_type, target,1);
                            r=1;
                        }
                    }
                    r=0;
                    p=0;
                    a=0;
                    s.initInterface(e.getState(), window,p,r);
                    s.DrawRefresh(window, e.getState(),order);
                    window.display();
                }
            }
            if(e.getState().getPokemon(1).getPV()==0 && r==0) {
                std::cout << e.getState().getPokemon(1).getName() << " est KO" << std::endl;
                if (e.getState().getPokemon(2).getPV()==0 && e.getState().getPokemon(3).getPV()==0 && e.getState().getPokemon(4).getPV()==0 && e.getState().getPokemon(5).getPV()==0) {
                    if (e.getState().getPokemon(0).getPV()<=0 && e.getState().getPokemon(1).getPV()<=0) {
                        std::cout << "Défaite" << std::endl;
                        //e.writeJSON(e.getPastCommands());
                        window.close();
                    }
                    r=1;
                    p=0;
                }
                else {
                    while (r==0) {
                        while (window.pollEvent(event) && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x>390 && event.mouseButton.y>410 && e.getState().getPokemon(s.convertP(event.mouseButton.x,event.mouseButton.y)).getPV()!=0) {
                                p=1;
                            setCommand(e.getState(),e,event.mouseButton.x,event.mouseButton.y, ai_type, target,1);
                            r=1;
                        }
                    }
                    r=0;
                    p=0;
                    a=0;
                    s.initInterface(e.getState(), window,p,r);
                    s.DrawRefresh(window, e.getState(),order);
                    window.display();
                }
            }
            if(e.getState().getPokemon(6).getPV()==0) {
                if (c==0) std::cout << e.getState().getPokemon(6).getName() << " ennemi est KO" << std::endl;
                if (e.getState().getPokemon(8).getPV()<=0 && e.getState().getPokemon(9).getPV()<=0 && e.getState().getPokemon(10).getPV()<=0 && e.getState().getPokemon(11).getPV()<=0) {
                    c=1;
                    if (e.getState().getPokemon(6).getPV()<=0 && e.getState().getPokemon(7).getPV()<=0) {
                        std::cout << "Victoire" << std::endl;
                        //e.writeJSON(e.getPastCommands());
                        window.close();
                        return;
                    }
                }
                else {
                    int i=8;
                    while(e.getState().getPokemon(i).getPV()<=0) {
                        if (i==11) {
                            break;
                        }
                        i++;
                    }
                    engine::Command c(3);
                    c.setPriority(6);
                    c.setPokemon(6);
                    c.setPokemon_target(i);
                    e.addCommand(c);
                    r=2;
                    p=0;
                    a=0;
                    s.DrawRefresh(window, e.getState(),order);
                    window.display();
                }
            }
            if(e.getState().getPokemon(7).getPV()==0) {
                if (c==0) std::cout << e.getState().getPokemon(7).getName() << " ennemi est KO" << std::endl;
                if (e.getState().getPokemon(8).getPV()==0 && e.getState().getPokemon(9).getPV()==0 && e.getState().getPokemon(10).getPV()==0 && e.getState().getPokemon(11).getPV()==0) {
                    c=1;
                    if (e.getState().getPokemon(6).getPV()<=0 && e.getState().getPokemon(7).getPV()<=0) {
                        std::cout << "Victoire" << std::endl;
                        //e.writeJSON(e.getPastCommands());
                        window.close();
                        return;
                    }
                }
                else {
                    int i=8;
                    while(e.getState().getPokemon(i).getPV()<=0) {
                        if (i==11) {
                            break;
                        }
                        i++;
                    }
                    engine::Command c(3);
                    c.setPriority(6);
                    c.setPokemon(7);
                    c.setPokemon_target(i);
                    e.addCommand(c);
                    r=2;
                    p=0;
                    a=0;
                    s.DrawRefresh(window, e.getState(),order);
                    window.display();
                }
            }

            if((e.getState().getPokemon(0).getPV() !=0 && e.getState().getPokemon(1).getPV()!=0 && e.getState().getPokemon(6).getPV()!=0 && e.getState().getPokemon(7).getPV()!=0) || c==1 || r==1) {

            while (window.pollEvent(event)) {
                s.DrawRefresh(window, e.getState(),order);
                if(event.type == sf::Event::Closed) {
                    std::cout << "Vous avez fermer la fenetre" << endl;

                    //e.writeJSON(e.getPastCommands());
                    window.close();
                    return;
                }

                if(event.type == sf::Event::KeyPressed && ai_type<4 && ai_type>0) {
                    if(event.key.code == sf::Keyboard::Return) {
                        if (joueur.check_pv(e,window,0)==0) {
                            joueur.run(e, e.getState(),0);
                        }
                        if (ai_type==1 && ia1.check_pv(e, window, 1)==0) {
                            ia1.run(e,e.getState(),1);
                            r=2;
                            s.DrawRefresh(window, e.getState(),order);
                            if (ia1.check_pv(e,window,1)==1) return;
                        }
                        else if (ai_type==2 && ia2.check_pv(e, window, 1)==0) {
                            ia2.run(e,e.getState(),1);
                            r=2;
                            s.DrawRefresh(window, e.getState(),order);
                            if (ia2.check_pv(e,window,1)==1) return;
                        }
                        else if (ai_type==3 && ia3.check_pv(e, window, 1)==0) {
                            ia3.run(e,e.getState(),1);
                            r=2;
                            s.DrawRefresh(window, e.getState(),order);
                            if (ia3.check_pv(e,window,1)==1) return;
                        }
                        if (joueur.check_pv(e,window,0)==1 || ia1.check_pv(e,window,1)==1 || ia2.check_pv(e,window,1)==1 || ia3.check_pv(e,window,1)==1) {
                            //e.writeJSON(e.getPastCommands());
                            return;
                        }
                        s.DrawRefresh(window, e.getState(),order);
                        for (int i =0; i<2; i++) {
                            if (e.getState().getPokemon(6+i).getPV()==0) std::cout << e.getState().getPokemon(6+i).getName() << " ennemi est KO" << endl;
                            if (e.getState().getPokemon(i).getPV()==0) std::cout << e.getState().getPokemon(i).getName() << " est KO" << endl;
                        }
                        cout << "--------Prochain tour--------" << endl;
                    }
                    s.initInterface(e.getState(), window, p,r);
                }

                if(event.type == sf::Event::KeyPressed) {
                    if(event.key.code == sf::Keyboard::Left) {
                        if (a%2 ==1) {
                            target = 6;
                            a++;
                            setCommand(e.getState(), e, x, y, ai_type, target);
                        }
                    }
                    if(event.key.code == sf::Keyboard::Right) {
                        if (a%2 ==1) {
                            target = 7;
                            a++ ;
                            setCommand(e.getState(), e, x, y, ai_type, target);
                        }
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        x = event.mouseButton.x;
                        y = event.mouseButton.y;
                        //std::cout << "mouse x: " << x << std::endl;
                        //std::cout << "mouse y: " << y << std::endl;
                        if (y>380 && x<=390) {
                            if (e.getState().getPokemon(p).getAttack(s.convertA(x, y)).getStatsAttack().scope==-1) {
                                if (e.getState().getPokemon(p).getPV()!=0) setCommand(e.getState(), e, x, y, ai_type, target);
                            }
                            else {
                                if (a%2 == 0) a++;
                                std::cout << "<- ou ->" << std::endl;
                            }

                        }
                        if (x>390 && y>380) {
                            if (e.getState().getPokemon(p).getPV()!=0) setCommand(e.getState(), e, x, y, ai_type, target);
                        }
                    }
                }
            }
            s.initInterface(e.getState(), window, p,r);
            window.display();
            }
        }
        t1.join();
    }

    void Client::play() {
        sf::RenderWindow window(sf::VideoMode(512, 512), "Fight");
        render::Scene s;
        engine::Engine e;
        engine::Command command(0);
        s.draw(e,window);
        std::thread t1(thread_play, &e);

        while (window.isOpen()) {
            sf::Event event;
            s.DrawRefresh(window,e.getState(),order);
            s.initInterface(e.getState(),window,p,r);
            window.display();
            while (window.pollEvent(event)){
                if(event.type == sf::Event::Closed) {
                    std::cout << "Vous avez fermer la fenetre" << endl;
                    window.close();
                }
            }
            if(e.getState().getPokemon(6).getPV()==0 && e.getState().getPokemon(7).getPV()==0 && e.getState().getPokemon(8).getPV()==0 && e.getState().getPokemon(9).getPV()==0 && e.getState().getPokemon(10).getPV()==0 && e.getState().getPokemon(11).getPV()==0) {
                cout << "IA adverse a perdu" << endl;
                window.close();
            }
            if(e.getState().getPokemon(0).getPV()==0 && e.getState().getPokemon(1).getPV()==0 && e.getState().getPokemon(2).getPV()==0 && e.getState().getPokemon(3).getPV()==0 && e.getState().getPokemon(4).getPV()==0 && e.getState().getPokemon(5).getPV()==0) {
                cout << "IA joueur a perdu" << endl;
                window.close();
            }

        }
        t1.join();
    }

    void Client::inverseConvertP(int p, int& x, int& y) {
        switch (p) {
            case 2 :
                x = 400;
                y = 450;
                break;
            case 3 :
                x = 480;
                y = 450;
                break;
            case 4 :
                x = 400;
                y = 470;
                break;
            case 5 :
                x = 480;
                y = 470;
                break;
            case 8 :
                x = 400;
                y = 450;
                break;
            case 9 :
                x = 480;
                y = 450;
                break;
            case 10 :
                x = 400;
                y = 470;
                break;
            case 11 :
                x = 480;
                y = 470;
                break;
            default : 
                break;
        }
    }

    int Client::convertP(int x, int y) {
        if (x< 450 && x> 390 && y<460 && y >420) return 2;
        else if (x< 510 && x> 450 && y<460 && y >420) return 3;
        else if (x< 450 && x> 390 && y >460) return 4;
        else if (x< 510 && x> 450 && y >460) return 5;
        return -1;
    }

    int Client::convertA(int x, int y) {
        if (x< 200 && y<440 && y >370) return 0;
        else if (x<390 && x> 200 && y<440 && y >370) return 1;
        else if (x< 200 && y >440) return 2;
        else if (x<390 && x> 200 && y >440) return 3;
        return -1;
    }

    void Client::setCommand(state::State& state, engine::Engine& e, int x, int y, int ai_type, int target, int prio) {
        if (y>380 && x<=390) {
            int att = convertA(x,y);
            if (state.getPokemon(p+6*player).getAttack(att).getPP()==0) return;
            if (state.getPokemon(p+6*player).getPV()==0) return;
            if (state.getPokemon(p+6*player).getAttack(att).getStatsAttack().scope==3) {
                    engine::Command a1(2);
                    a1.setPokemon(p+6*player);
                    a1.setPokemon_target(1-p-6*player);
                    a1.setAttack(att);
                    a1.setPriority(state.getPokemon(p+6*player).getAttack(att).getStatsAttack().priority);
                    e.addCommand(a1);
                    engine::Command a2(2);
                    a2.setPokemon(p+6*player);
                    a2.setPokemon_target(6-6*player);
                    a2.setAttack(att);
                    a2.setPriority(state.getPokemon(p+6*player).getAttack(att).getStatsAttack().priority);
                    e.addCommand(a2);
                    engine::Command a3(2);
                    a3.setPokemon(p+6*player);
                    a3.setPokemon_target(7-6*player);
                    a3.setAttack(att);
                    a3.setPriority(state.getPokemon(p+6*player).getAttack(att).getStatsAttack().priority);
                    e.addCommand(a3);
                }
                else {
                    engine::Command a(2);
                    a.setPokemon(p+6*player);
                    a.setPokemon_target(target-6*player);
                    a.setAttack(att);
                    a.setPriority(state.getPokemon(p+6*player).getAttack(att).getStatsAttack().priority);
                    e.addCommand(a);
                }
            r++;
            p=1-p;
        }

        else if (x< 450 && x> 390 && y<420 && y >380) {
            if (p==1) {
                p = 0;
                a=0;
                r=0;
                e.undoCommand();
            }
            return;
        }
        else if (x< 510 && x> 450 && y<420 && y >380) {
            if (p==0) {
                p=1;
                a=0;
                r=0;
                e.undoCommand();
            }
            return;
        }
        else if (y>380 && x> 390) {
            int poke = convertP(x,y);
            if (state.getPokemon(poke+6*player).getPV()==0) return;
            if (prio==1) {
                engine::Command c(3);
                c.setPokemon(p+6*player);
                c.setPokemon_target(poke+6*player);
                c.setPriority(6);
                c.execute(state, player);
                e.setPastCommands(c);
            }
            else {
                engine::Command c(1);
                c.setPokemon(p+6*player);
                c.setPokemon_target(poke+6*player);
                c.setPriority(6);
                e.addCommand(c);
            }
            r++;
            p=1-p;
        }
        if (r==2) {
            if (ai_type==1) {
                ai::RandomAI ia;
                ia.run(e,state,1);
            }
            else if (ai_type==2) {
                ai::HeuristicAI ia;
                ia.run(e,state,1);
            }
            else if (ai_type==3) {
                ai::DeepAI ia;
                ia.run(e,state,1);
            }
            r=0;
            a=0;
            p=0;
        }
    }
    void Client::connect() {

        int id = 1, list_player = 1;
        string name;
        cout << "Enter your name: ";
        cin >> name;
        sf::Http http(URL, PORT);
        addPlayer(http,name);
        std::vector<int> list = {};
        while (list_player == 1) {
            list_player = getPlayer(http, id);
            id++;
        }
        cout << "id player is " << to_string(id1) << endl;
        sleep(2);
        while (1) {
            if (getListPokemon(http, list) == 2) {
                player = id1-2;
                this->run1v1(list, id1-2);
            }
            else list = {};
            sleep(3);
        }
    }

    void Client::connectTest() {

        int id = 1, list_player = 1;
        string name;
        cout << "Enter your name: ";
        cin >> name;
        sf::Http http(URL, PORT);
        addPlayer(http,name);
        while (list_player == 1) {
            list_player = getPlayer(http, id);
            id++;
        }
        sleep(5);
        deletePlayer(id);
    }

    int Client::addPlayer(sf::Http &http, string name) {

        sf::Http::Response response;
        sf::Http::Request req;
        req.setUri("/user");
        req.setMethod(sf::Http::Request::Put);
        Json::Value User;
        srand (time(NULL));
        User["Pokemon1"] = rand() % 19 +1;
        User["Pokemon2"] = rand() % 19 +1;
        User["Pokemon3"] = rand() % 19 +1;
        User["Pokemon4"] = rand() % 19 +1;
        User["Pokemon5"] = rand() % 19 +1;
        User["Pokemon6"] = rand() % 19 +1;
        User["Name"] = name;
        req.setBody(User.toStyledString());
        req.setField("Content-Type", "application/json");
        req.setHttpVersion(1, 1);
        response = http.sendRequest(req);
        if (response.getStatus() == sf::Http::Response::Created) {
            Json::Value root;
            Json::Value players;
            Json::Reader reader;
            if (!reader.parse(response.getBody(), root, false))
            {
                cout << reader.getFormattedErrorMessages() << endl;
            }
            int id = root["id"].asInt();
            id1 = id;
            cout << "id" << id;
            if (id == -1)
            {
                cout << "Plus de place" << endl;
                return -1;
            }
            else
            {
                return id;
            }
        }
        else
        {
            cout << "Erreur: " << response.getStatus() << endl;
            return -1;
        }
    }

    void Client::deletePlayer(int id) {
        sf::Http http(URL,PORT);
        sf::Http::Response response;
        sf::Http::Request req;
        req.setMethod(sf::Http::Request::Delete);
        req.setUri("/user/" + std::to_string(id));
        req.setField("Content-Type", "application/json");
        req.setBody("");
        response = http.sendRequest(req);
    }

    int Client::getPlayer(sf::Http &http, int id) {
        sf::Http::Response response;
        sf::Http::Request req("/user/"+to_string(id), sf::Http::Request::Get);
        response = http.sendRequest(req);

        if (response.getStatus() == sf::Http::Response::Ok) {
            cout << "succes get" << id << endl;
            cout << response.getBody() << endl;
            return 1;
        }
        else {
            cout << "echec get" << response.getStatus() << endl;
            return 0;
        }
    }

    int Client::getListPokemon(sf::Http &http, std::vector<int>& list) {
        int nb_player = 0;
        for (int i=2; i<4; i++) {
            sf::Http::Response response;
            sf::Http::Request req("/user/"+to_string(i), sf::Http::Request::Get);
            response = http.sendRequest(req);

            if (response.getStatus() == sf::Http::Response::Ok) {
                Json::Value root;
                Json::Reader reader;
                if (!reader.parse(response.getBody(), root, false))
                {
                    cout << reader.getFormattedErrorMessages() << endl;
                }
                int pokemon1 = root["Pokemon1"].asInt();
                int pokemon2 = root["Pokemon2"].asInt();
                int pokemon3 = root["Pokemon3"].asInt();
                int pokemon4 = root["Pokemon4"].asInt();
                int pokemon5 = root["Pokemon5"].asInt();
                int pokemon6 = root["Pokemon6"].asInt();
                list.push_back(pokemon1);
                list.push_back(pokemon2);
                list.push_back(pokemon3);
                list.push_back(pokemon4);
                list.push_back(pokemon5);
                list.push_back(pokemon6);
                cout << pokemon1 << pokemon2 << pokemon3<< pokemon4<< pokemon5<< pokemon6<< endl;
                nb_player ++;
            }
            else {
                cout << "echec get " << i << " " << response.getStatus() << endl;
            }
        }
        return nb_player;
    }


    void Client::run1v1(std::vector<int> list, int player) {
        sf::RenderWindow window(sf::VideoMode(512, 512), "Fight id" + to_string(player+2));
        render::Scene s(512,512,player);
        engine::Engine e(list,state::NONE_W,state::GRASSY);
        ai::HeuristicAI joueur;
        ai::HeuristicAI joueur2;
        ai::RandomAI ia1;
        ai::HeuristicAI ia2;
        ai::DeepAI ia3;
        int x, y;
        s.draw(e,window);
        std::thread t1(thread_engine, &e);
        while (window.isOpen()) {
            sf::Event event;
            int target=0;
            s.initInterface(e.getState(), window, p,r); // Ca clignote moins avec ça
            window.display();// Ca clignote moins avec ça

            if(e.getState().getPokemon(0+6*player).getPV()==0 && r==0) {
                std::cout << e.getState().getPokemon(0+6*player).getName() << " est KO" << std::endl;
                if (e.getState().getPokemon(2+6*player).getPV()==0 && e.getState().getPokemon(3+6*player).getPV()==0 && e.getState().getPokemon(4+6*player).getPV()==0 && e.getState().getPokemon(5+6*player).getPV()==0) {
                    if (e.getState().getPokemon(0+6*player).getPV()<=0 && e.getState().getPokemon(1+6*player).getPV()<=0) {
                        std::cout << "Défaite" << std::endl;
                        //e.writeJSON(e.getPastCommands());
                        window.close();
                    }
                    r=1;
                    p=1;
                }
                else {
                    for (int p =2+6*player; p<6; p++) {
                        if (e.getState().getPokemon(p).getPV()!=0) {
                            inverseConvertP(p,x,y);
                            setCommand(e.getState(),e,x,y, ai_type, target,1);
                        }
                    }
                    r=0;
                    p=0;
                    a=0;
                    s.DrawRefresh(window, e.getState(),order);
                    s.initInterface(e.getState(), window,p,r);
                    window.display();
                }
            }
            if(e.getState().getPokemon(1+6*player).getPV()==0 && r==0) {
                std::cout << e.getState().getPokemon(1+6*player).getName() << " est KO" << std::endl;
                if (e.getState().getPokemon(2+6*player).getPV()==0 && e.getState().getPokemon(3+6*player).getPV()==0 && e.getState().getPokemon(4+6*player).getPV()==0 && e.getState().getPokemon(5+6*player).getPV()==0) {
                    if (e.getState().getPokemon(0+6*player).getPV()<=0 && e.getState().getPokemon(1+6*player).getPV()<=0) {
                        std::cout << "Défaite" << std::endl;
                        //e.writeJSON(e.getPastCommands());
                        window.close();
                    }
                    r=1;
                    p=0;
                }
                else {
                    for (int p =2+6*player; p<6; p++) {
                        if (e.getState().getPokemon(p).getPV()!=0) {
                            inverseConvertP(p,x,y);
                            setCommand(e.getState(),e,x,y, ai_type, target,1);
                        }
                    }
                    r=0;
                    p=0;
                    a=0;
                    s.DrawRefresh(window, e.getState(),order);
                    s.initInterface(e.getState(), window,p,r);
                    window.display();
                }
            }
            if(e.getState().getPokemon(6).getPV()==0) {
                if (c==0) std::cout << e.getState().getPokemon(6).getName() << " ennemi est KO" << std::endl;
                if (e.getState().getPokemon(8).getPV()<=0 && e.getState().getPokemon(9).getPV()<=0 && e.getState().getPokemon(10).getPV()<=0 && e.getState().getPokemon(11).getPV()<=0) {
                    c=1;
                    if (e.getState().getPokemon(6).getPV()<=0 && e.getState().getPokemon(7).getPV()<=0) {
                        std::cout << "Victoire" << std::endl;
                        //e.writeJSON(e.getPastCommands());
                        window.close();
                        return;
                    }
                }
                else {
                    int i=8;
                    while(e.getState().getPokemon(i).getPV()<=0) {
                        if (i==11) {
                            break;
                        }
                        i++;
                    }
                    engine::Command c(3);
                    c.setPriority(6);
                    c.setPokemon(6);
                    c.setPokemon_target(i);
                    e.addCommand(c);
                    r=2;
                    p=0;
                    a=0;
                    s.DrawRefresh(window, e.getState(),order);
                    s.initInterface(e.getState(), window,p,r);
                    window.display();
                }
            }
            if(e.getState().getPokemon(7).getPV()==0) {
                if (c==0) std::cout << e.getState().getPokemon(7).getName() << " ennemi est KO" << std::endl;
                if (e.getState().getPokemon(8).getPV()==0 && e.getState().getPokemon(9).getPV()==0 && e.getState().getPokemon(10).getPV()==0 && e.getState().getPokemon(11).getPV()==0) {
                    c=1;
                    if (e.getState().getPokemon(6).getPV()<=0 && e.getState().getPokemon(7).getPV()<=0) {
                        std::cout << "Victoire" << std::endl;
                        //e.writeJSON(e.getPastCommands());
                        window.close();
                        return;
                    }
                }
                else {
                    int i=8;
                    while(e.getState().getPokemon(i).getPV()<=0) {
                        if (i==11) {
                            break;
                        }
                        i++;
                    }
                    engine::Command c(3);
                    c.setPriority(6);
                    c.setPokemon(7);
                    c.setPokemon_target(i);
                    e.addCommand(c);
                    r=2;
                    p=0;
                    a=0;
                    s.DrawRefresh(window, e.getState(),order);
                    s.initInterface(e.getState(), window,p,r);
                    window.display();
                }
            }

            if((e.getState().getPokemon(0).getPV() !=0 && e.getState().getPokemon(1).getPV()!=0 && e.getState().getPokemon(6).getPV()!=0 && e.getState().getPokemon(7).getPV()!=0) || c==1 || r==1) {
                if (r==0) {
                joueur.run(e, e.getState(),0);
                //cout << "r = " << r << endl;
                r = 2;
                }
                window.pollEvent(event);
                s.DrawRefresh(window, e.getState(),order);
                if(event.type == sf::Event::Closed) {
                    std::cout << "Vous avez fermer la fenetre" << endl;

                    //e.writeJSON(e.getPastCommands());
                    window.close();
                    return;
                }
                s.initInterface(e.getState(), window, p,r);
                window.display();
            }
        }
        t1.join();
    }


};
