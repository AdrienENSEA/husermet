
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/PokemonFactory.h"
#include "../../src/shared/state/Pokemon.h"


using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestPokemonF)
{
  {
    Pokemon groudon = PokemonFactory::createPokemon(GROUDON);
    Pokemon kyogre = PokemonFactory::createPokemon(KYOGRE);
    
    
    BOOST_CHECK_EQUAL(groudon.getName(), "Groudon");
    BOOST_CHECK_EQUAL(groudon.getID(), GROUDON);
    std::vector <Attack> a = groudon.getAttacks();
    BOOST_CHECK(!a.empty());
    BOOST_CHECK_EQUAL(a.at(0).getIdAttack(), E_COQUE);
    BOOST_CHECK_EQUAL(a.at(0).getName(), "E-Coque");
    BOOST_CHECK_EQUAL(a.at(0).getStatsAttack().pp, 10);
    BOOST_CHECK_EQUAL(a.at(0).getStatsAttack().power, 0);
    BOOST_CHECK_EQUAL(a.at(0).getStatsAttack().accuracy, 100);
    BOOST_CHECK_EQUAL(a.at(0).getStatsAttack().category, 3);
    BOOST_CHECK_EQUAL(a.at(0).getStatsAttack().priority, 0);
    BOOST_CHECK_EQUAL(a.at(0).getStatsAttack().scope, -1);
    BOOST_CHECK_EQUAL(a.at(0).getStatsModif().getModifStats().pv, 0);
    BOOST_CHECK_EQUAL(a.at(0).getStatsModif().getModifStats().attack, 0);
    BOOST_CHECK_EQUAL(a.at(0).getStatsModif().getModifStats().defense, 0);
    BOOST_CHECK_EQUAL(a.at(0).getStatsModif().getModifStats().sp_attack, 0);
    BOOST_CHECK_EQUAL(a.at(0).getStatsModif().getModifStats().sp_defense, 0);
    BOOST_CHECK_EQUAL(a.at(0).getStatsModif().getModifStats().speed, 0);
    const auto t = groudon.getType();
    BOOST_CHECK(!t.empty());
    BOOST_CHECK_EQUAL(t.at(0), GROUND);
    BOOST_CHECK_EQUAL(groudon.getState(), NONE_S);
    BOOST_CHECK_EQUAL(groudon.getStats().pv, 100);
    BOOST_CHECK_EQUAL(groudon.getStats().attack, 150);
    BOOST_CHECK_EQUAL(groudon.getStats().defense, 140);
    BOOST_CHECK_EQUAL(groudon.getStats().sp_attack, 100);
    BOOST_CHECK_EQUAL(groudon.getStats().sp_defense, 90);
    BOOST_CHECK_EQUAL(groudon.getStats().speed, 90);
    BOOST_CHECK_EQUAL(groudon.getEV(), 0);

  }
/*
  {
    Pokemon rayquaza {};
    rayquaza.setPV(210);
    BOOST_CHECK_LE(rayquaza.getPV(), 320); // Less than equal
    BOOST_CHECK_GT(rayquaza.getPV(), 110); // Greater than equl
  }*/
}

/* vim: set sw=2 sts=2 et : */
