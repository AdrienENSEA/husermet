
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/ModifStatsPokemon.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestMSP)
{
  {
    StatsPokemon s1 = {68, 90, 80, 60, 80, 100};
    ModifStatsPokemon m1();
    m1.setModifStats(s1);
    m1.setRoundLeft(3);
    ModifStatsPokemon m2(s1,3);
    BOOST_CHECK_EQUAL(m1, m2);
  }
}

/* vim: set sw=2 sts=2 et : */
