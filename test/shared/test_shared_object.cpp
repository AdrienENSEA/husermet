
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Object.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestObject)
{
  {
    StatsPokemon effect_stats = {0, 0, 0, 0, 0, 0};
    Object restes(RESTES, "Restes", "description", effect_stats, NORMAL, NONE);
    BOOST_CHECK_EQUAL(restes.getName(), "Restes");
    BOOST_CHECK_EQUAL(restes.getIdObject(), RESTES); 
    BOOST_CHECK_EQUAL(restes.getDescriptive(), "description"); 
    BOOST_CHECK_EQUAL(restes.getEffectState(), NORMAL); 
    BOOST_CHECK_EQUAL(restes.getEffectType(), NONE); 
    BOOST_CHECK_EQUAL(restes.getEffectStats().pv, 0);
    BOOST_CHECK_EQUAL(restes.getEffectStats().attack, 0);
    BOOST_CHECK_EQUAL(restes.getEffectStats().defense, 0);
    BOOST_CHECK_EQUAL(restes.getEffectStats().sp_attack, 0);
    BOOST_CHECK_EQUAL(restes.getEffectStats().sp_defense, 0);
    BOOST_CHECK_EQUAL(restes.getEffectStats().speed, 0);

  }
}

/* vim: set sw=2 sts=2 et : */
