
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Pokemon.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}


BOOST_AUTO_TEST_CASE(TestPokemon)
{
  {
    StatsPokemon effect_stats {0, 0, 0, 0, 0, 0};
    StatsAttack stats_attack {0, 0, 0, 0, 0, 0};
    ModifStatsPokemon stats_modif;
    std::vector <Type> type {{GROUND}};
    Attack a1(FRAPPE_ATLAS, "Frappe Atlas", "desc", FIGHT, stats_attack, stats_modif);
    Attack a2(TOXIK, "Toxic", "desc", POISON, stats_attack, stats_modif);
    Attack a3(ABRI, "Abri", "desc", NORMAL, stats_attack, stats_modif);
    std::vector <Attack> attacks {a1, a2, a3};
    Object restes(ORBE_VIE, "Orbe vie", "description", effect_stats, NONE_S, NONE_T);
    StatsPokemon stats_pokemon = {0, 0, 0, 0, 0, 0, 0};
    Pokemon groudon(GROUDON, "Groudon", restes , attacks, 1, type, NONE_S, stats_pokemon, 0);
    BOOST_CHECK_EQUAL(groudon.getName(), "Groudon");
    BOOST_CHECK_EQUAL(groudon.getID(), GROUDON);
    BOOST_CHECK_EQUAL(groudon.getObject()->getName(), restes.getName());
    std::vector <Attack> a = groudon.getAttack();
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
    BOOST_CHECK_EQUAL(groudon.getEV(), 0);
  }

  {
    StatsPokemon effect_stats {0, 0, 0, 0, 0, 0};
    StatsAttack stats_attack {0, 0, 0, 0, 0, 0};
    ModifStatsPokemon stats_modif;
    Attack a1(PIEGE_DE_ROC, "Piege de Roc", "desc", ROCK, stats_attack, stats_modif);
    std::vector <Attack> attacks {a1};
    Object ballon(BALLON, "Ballon", "description", effect_stats, NONE_S, FLY);
    Pokemon heatran;
    heatran.setName("Heatran");
    heatran.setObject(ballon);
    heatran.setAttack(0, a1);
    BOOST_CHECK_EQUAL(heatran.getName(), "Heatran");
    std::vector <Attack> a = heatran.getAttack();
    BOOST_CHECK(!a.empty());
    BOOST_CHECK_EQUAL(a.at(0).getIdAttack(), PIEGE_DE_ROC);
    BOOST_CHECK_EQUAL(a.at(0).getName(), "Piege de Roc");
    BOOST_CHECK_EQUAL(heatran.getObject()->getIdObject(), BALLON);
  }
}

/* vim: set sw=2 sts=2 et : */
