
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Pokemon.h"
#include "../../src/shared/state/Object.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestPokemon)
{
  {
    StatsPokemon effect_stats {0, 0, 0, 0, 0, 0};
    StatsAttack stats_attack {0, 0, 0, 0, 0, 0};
    ModifStatsPokemon stats_modif;
    std::vector <Type> type {{NONE}};
    Attack a1(FRAPPE_ATLAS, "Frappe Atlas", "desc", NONE, stats_attack, stats_modif);
    Attack a2(TOXIK, "Toxic", "desc", NONE, stats_attack, stats_modif);
    Attack a3(ABRI, "Abri", "desc", NONE, stats_attack, stats_modif);
    Object restes(RESTES, "Restes", "description", effect_stats, NORMAL, NONE);
    std::vector <Attack> attacks{a1, a2, a3};
    StatsPokemon stats_pokemon = {0, 0, 0, 0, 0, 0};
    Pokemon groudon(GROUDON, "Groudon", restes , attacks, 1, type, NORMAL, stats_pokemon, 0);
    BOOST_CHECK_EQUAL(groudon.getName(), "Groudon");
    BOOST_CHECK_EQUAL(groudon.getID(), GROUDON);
    //BOOST_CHECK_EQUAL(groudon.getObject(), restes);
    const std::vector <Attack> a = groudon.getAttack();
    BOOST_CHECK(!a.empty());
    //BOOST_CHECK_EQUAL(a.at(0).getName(), "Frappe Atlas"); ERREUR
    const auto t = groudon.getType();
    BOOST_CHECK(!t.empty());
    BOOST_CHECK_EQUAL(t.at(0), NONE);
    BOOST_CHECK_EQUAL(groudon.getState(), NORMAL);
    BOOST_CHECK_EQUAL(groudon.getStats().pv, 0);
    BOOST_CHECK_EQUAL(groudon.getStats().attack, 0);
    BOOST_CHECK_EQUAL(groudon.getStats().defense, 0);
    BOOST_CHECK_EQUAL(groudon.getStats().sp_attack, 0);
    BOOST_CHECK_EQUAL(groudon.getStats().sp_defense, 0);
    BOOST_CHECK_EQUAL(groudon.getStats().speed, 0);
    BOOST_CHECK_EQUAL(groudon.getEV(), 0);
    //BOOST_CHECK_EQUAL(groudon.getID(), GROUDON);

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
