
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
    StatsPokemon effect_stats = {0, 0, 0, 0, 0, 0};
    Object restes(RESTES, "Restes", "description", effect_stats, NORMAL, NONE);
    std::list <Attack> attacks = {};
    StatsPokemon stats_pokemon = {0, 0, 0, 0, 0, 0};
    Pokemon groudon(GROUDON, "Groudon", restes , attacks, 1, NONE, NORMAL, stats_pokemon, 0);
    BOOST_CHECK_EQUAL(groudon.getName(), "Groudon");
    BOOST_CHECK_EQUAL(groudon.getID(), GROUDON); 
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
