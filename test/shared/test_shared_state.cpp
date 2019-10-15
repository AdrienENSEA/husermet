
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
    std::list <Team> battle = {};
    State s(battle, SUN, GRASSY);
    BOOST_CHECK_EQUAL(s.getTypeTerrain(), GRASSY);
    BOOST_CHECK_EQUAL(s.getTypeWeather(), SUN); 
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
