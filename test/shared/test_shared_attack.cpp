
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
    StatsAttack stats_attack {0, 0, 0, 0, 0, 0};
    ModifStatsPokemon stats_modif;
    Attack frappe_atlas(FRAPPE_ATLAS, "Frappe Atlas", "desc", FIGHTING, stats_attack, stats_modif);
    BOOST_CHECK_EQUAL(frappe_atlas.getName(), "Frappe Atlas");
    BOOST_CHECK_EQUAL(frappe_atlas.getIdAttack(), FRAPPE_ATLAS);
    BOOST_CHECK_EQUAL(frappe_atlas.getDescriptive(), "desc");
    BOOST_CHECK_EQUAL(frappe_atlas.getType(), FIGHTING);
    BOOST_CHECK_EQUAL(frappe_atlas.getStatsAttack().pp, 0);
    BOOST_CHECK_EQUAL(frappe_atlas.getStatsAttack().power, 0);
    BOOST_CHECK_EQUAL(frappe_atlas.getStatsAttack().accuracy, 0);
    BOOST_CHECK_EQUAL(frappe_atlas.getStatsAttack().category, 0);
    BOOST_CHECK_EQUAL(frappe_atlas.getStatsAttack().priority, 0);
    BOOST_CHECK_EQUAL(frappe_atlas.getStatsAttack().scope, 0);
    BOOST_CHECK_EQUAL(frappe_atlas.getStatsModif().getModifStats().pv, 0);
    BOOST_CHECK_EQUAL(frappe_atlas.getStatsModif().getModifStats().attack, 0);
    BOOST_CHECK_EQUAL(frappe_atlas.getStatsModif().getModifStats().defense, 0);
    BOOST_CHECK_EQUAL(frappe_atlas.getStatsModif().getModifStats().sp_attack, 0);
    BOOST_CHECK_EQUAL(frappe_atlas.getStatsModif().getModifStats().sp_defense, 0);
    BOOST_CHECK_EQUAL(frappe_atlas.getStatsModif().getModifStats().speed, 0);
  }
}

/* vim: set sw=2 sts=2 et : */
