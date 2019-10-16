
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/AttackFactory.h"
#include "../../src/shared/state/Pokemon.h"


using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestAttackFactory)
{
  {
    Attack e_coque = AttackFactory::createAttack(E_COQUE);
    
    
    //BOOST_CHECK_EQUAL(groudon.getName(), "Groudon");
    ///BOOST_CHECK_EQUAL(groudon.getID(), GROUDON);
    //BOOST_CHECK_EQUAL(groudon.getObject(), restes);
    /*std::vector <Attack> a = groudon.getAttack();
    BOOST_CHECK(!a.empty());
    BOOST_CHECK_EQUAL(a.at(0).getIdAttack(), FRAPPE_ATLAS);
    BOOST_CHECK_EQUAL(a.at(0).getName(), "Frappe Atlas");
    BOOST_CHECK_EQUAL(a.at(0).getDescriptive(), "desc");
    BOOST_CHECK_EQUAL(a.at(0).getStatsAttack().pp, 0);
    BOOST_CHECK_EQUAL(a.at(0).getStatsAttack().power, 0);
    BOOST_CHECK_EQUAL(a.at(0).getStatsAttack().accuracy, 0);
    BOOST_CHECK_EQUAL(a.at(0).getStatsAttack().category, 0);
    BOOST_CHECK_EQUAL(a.at(0).getStatsAttack().priority, 0);
    BOOST_CHECK_EQUAL(a.at(0).getStatsAttack().scope, 0);
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
    BOOST_CHECK_EQUAL(groudon.getStats().pv, 0);
    BOOST_CHECK_EQUAL(groudon.getStats().attack, 0);
    BOOST_CHECK_EQUAL(groudon.getStats().defense, 0);
    BOOST_CHECK_EQUAL(groudon.getStats().sp_attack, 0);
    BOOST_CHECK_EQUAL(groudon.getStats().sp_defense, 0);
    BOOST_CHECK_EQUAL(groudon.getStats().speed, 0);
    BOOST_CHECK_EQUAL(groudon.getEV(), 0);*/

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
