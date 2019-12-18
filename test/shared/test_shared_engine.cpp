
#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine.h"
#include "../../src/shared/state/IdPokemon.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace engine;
using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}


BOOST_AUTO_TEST_CASE(TestEngine)
{
  {
    std::vector<engine::Command> vect_command1;
    std::vector<engine::Command> vect_command2;
    engine::Command command1(1);
    engine::Command command2(1);
    engine::Engine engine;
    
    command1.setPokemon(IdPokemon::LEVEINARD);
    command1.setPokemon_target(IdPokemon::GARDEVOIR);
    command1.setPriority(1);
    command1.setAttack(3);
    vect_command1.push_back(command1);
    vect_command1.push_back(command1);
    vect_command1.push_back(command1);
    vect_command1.push_back(command1);
    
    engine.writeJSON(vect_command1);
    engine.readJSON(vect_command2);
    
    BOOST_CHECK_EQUAL(vect_command1.at(0).getPokemon_target(), vect_command2.at(0).getPokemon_target());
    
    cout << "Attack         " << vect_command2.at(0).getAttack() << endl;
    cout << "CommandId      " << vect_command2.at(0).getCommandID() << endl;
    cout << "Pokemon        " << vect_command2.at(0).getPokemon() << endl;
    cout << "Pokemon_target " << vect_command2.at(0).getPokemon_target() << endl;
    cout << "Priority       " << vect_command2.at(0).getPriority() << endl;
    cout << endl;
    
    cout << "Attack         " << vect_command2.at(1).getAttack() << endl;
    cout << "CommandId      " << vect_command2.at(1).getCommandID() << endl;
    cout << "Pokemon        " << vect_command2.at(1).getPokemon() << endl;
    cout << "Pokemon_target " << vect_command2.at(1).getPokemon_target() << endl;
    cout << "Priority       " << vect_command2.at(1).getPriority() << endl;
    cout << endl;
    
    cout << "Attack         " << vect_command2.at(2).getAttack() << endl;
    cout << "CommandId      " << vect_command2.at(2).getCommandID() << endl;
    cout << "Pokemon        " << vect_command2.at(2).getPokemon() << endl;
    cout << "Pokemon_target " << vect_command2.at(2).getPokemon_target() << endl;
    cout << "Priority       " << vect_command2.at(2).getPriority() << endl;
    cout << endl;
    
    cout << "Attack         " << vect_command2.at(3).getAttack() << endl;
    cout << "CommandId      " << vect_command2.at(3).getCommandID() << endl;
    cout << "Pokemon        " << vect_command2.at(3).getPokemon() << endl;
    cout << "Pokemon_target " << vect_command2.at(3).getPokemon_target() << endl;
    cout << "Priority       " << vect_command2.at(3).getPriority() << endl;
    cout << endl;
  }
}

/* vim: set sw=2 sts=2 et : */
