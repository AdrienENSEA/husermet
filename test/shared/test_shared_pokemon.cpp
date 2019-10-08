
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Pokemon.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestExemple)
{
  {
    Pokemon rayquaza {};
    rayquaza.setName("Rayquaza");
    rayquaza.setID(static_cast<IdPokemon>(1));
    BOOST_CHECK_EQUAL(rayquaza.name, "Rayquaza");
    BOOST_CHECK_EQUAL(rayquaza.id_pokemon, 1);
    
  }

  {
    Pokemon rayquaza {};
    rayquaza.setPV(210);
    BOOST_CHECK_LE(rayquaza.stats_pokemon.pv, 320); // Less than equal
    BOOST_CHECK_GT(rayquaza.stats_pokemon.pv, 110); // Greater than equl
  }
}

/* vim: set sw=2 sts=2 et : */
