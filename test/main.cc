#include "TestGameMap.cc"
#include "TestHero.cc"
#include "TestHeroResources.cc"
#include "TestMapObject.cc"
#include "TestMapParser.cc"
#include "TestTurnManager.cc"
#include "doctest.h"

int main(int argc, char **argv) {
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    context.setOption("no-breaks", true);

    int res = context.run();

    if (context.shouldExit()) return res;

    return res;
}