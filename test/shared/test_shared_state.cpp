
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Attack.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestState)
{
  {
  StatsPokemon effect_stats {0, 0, 0, 0, 0, 0};
    StatsAttack stats_attack {0, 0, 0, 0, 0, 0};
    ModifStatsPokemon stats_modif;
    std::vector <Type> type {{GROUND}};
    Attack a1(FRAPPE_ATLAS, "Frappe Atlas", "desc", FIGHT, stats_attack, stats_modif,0);
    Attack a2(TOXIK, "Toxic", "desc", POISON, stats_attack, stats_modif,0);
    Attack a3(ABRI, "Abri", "desc", NORMAL, stats_attack, stats_modif,0);
    std::vector <Attack> attacks {a1, a2, a3};
    Item restes(ORBE_VIE, "Orbe vie", "description", effect_stats, NONE_S, NONE_T);
    StatsPokemon stats_pokemon = {0, 0, 0, 0, 0, 0};
    Pokemon groudon(GROUDON, "Groudon", restes , attacks, 1, type, NONE_S, stats_pokemon, 0,0);
    Pokemon p;
    std::vector <Pokemon> battle{p,p,p,p,p,p,p,p,p,p,p,p};
    State s(battle, SUN, GRASSY);
    std::vector<Pokemon> team {groudon, p,p,p,p,p};
    s.setTeam(0,team);
    BOOST_CHECK_EQUAL(s.getTypeTerrain(), GRASSY);
    BOOST_CHECK_EQUAL(s.getTypeWeather(), SUN);
    BOOST_CHECK_EQUAL(s.getPokemon(0).getID(), GROUDON); 
  }

  {
    State s;
    s.setTypeTerrain(MISTY);
    s.setTypeWeather(RAIN);
    BOOST_CHECK_EQUAL(s.getTypeTerrain(), MISTY);
    BOOST_CHECK_EQUAL(s.getTypeWeather(), RAIN); 
  }
}

/* vim: set sw=2 sts=2 et : */
