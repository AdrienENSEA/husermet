
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
    StatsAttack stats_attack {0, 0, 0, 0, 0, 0, 0};
    ModifStatsPokemon stats_modif;
    Attack frappe_atlas(PROVOC, "Provoc", "desc", DARK, stats_attack, stats_modif);
    BOOST_CHECK_EQUAL(frappe_atlas.getName(), "Provoc");
    BOOST_CHECK_EQUAL(frappe_atlas.getIdAttack(), PROVOC);
    BOOST_CHECK_EQUAL(frappe_atlas.getDescriptive(), "desc");
    BOOST_CHECK_EQUAL(frappe_atlas.getType(), DARK);
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
    StatsAttack stats_attack1 {10, 0, 0, 0, 0, 0, 0};
    frappe_atlas.setStatsAttack(stats_attack1);
    BOOST_CHECK_EQUAL(frappe_atlas.getStatsAttack().pp, 10);
  }

  {
    Attack coudjus;
    coudjus.setType(ELECTRIC);
    coudjus.setStatsAttack ({15,15,90,100,2,0,3});
    BOOST_CHECK_EQUAL(coudjus.getType(), ELECTRIC);
    BOOST_CHECK_EQUAL(coudjus.getStatsAttack().pp, 15);
    BOOST_CHECK_EQUAL(coudjus.getStatsAttack().power, 90);
    BOOST_CHECK_EQUAL(coudjus.getStatsAttack().accuracy, 100);
    BOOST_CHECK_EQUAL(coudjus.getStatsAttack().category, 2);
    BOOST_CHECK_EQUAL(coudjus.getStatsAttack().priority, 0);
    BOOST_CHECK_EQUAL(coudjus.getStatsAttack().scope, 3);
  }
}

/* vim: set sw=2 sts=2 et : */
