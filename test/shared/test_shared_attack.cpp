
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Attack.h"
#include "../../src/shared/state/ModifStatsPokemon.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestAttack)
{
  {
    StatsAttack stats_attack = {0, 0, 0, 0, 0, 0};
    ModifStatsPokemon stats_modif();
    Attack frappe_atlas(FRAPPE_ATLAS, "Frappe Atlas", "desc", NONE, stats_attack, stats_modif);
    BOOST_CHECK_EQUAL(frappe_atlas.getName(), "Frappe Atlas");
    BOOST_CHECK_EQUAL(frappe_atlas.getIdAttack(), FRAPPE_ATLAS); 
  }
}

/* vim: set sw=2 sts=2 et : */
