#include <iostream>
#include <memory>
#include <vector>
#include "../src/Battle.h"
#include "GameWindow.h"
#include "doctest.h"

TEST_CASE("Battle") {
    SType::Archer archer(5, 0, 0);
    SType::Pikeman pikeman(5, 0, 0);
    SType::SwordsMan swordsMan(5, 15, 15);
    SUBCASE("Should initialize properly") {}
    SUBCASE("Testing Soldier initialization and methods") {
        CHECK_FALSE(archer.try_to_move(15, 15));
        CHECK(pikeman.try_to_move(1, 3));
        CHECK_EQ(pikeman.getX(), 1);
        CHECK_EQ(pikeman.getY(), 3);
        CHECK_EQ(archer.attack(15, 15), 15);
        CHECK_EQ(pikeman.attack(15, 15), 0);
        CHECK_EQ(pikeman.attack(2, 2), 15);
        CHECK_EQ(pikeman.getX(), 2);
        CHECK_EQ(pikeman.getY(), 2);
        swordsMan.receive_damage(40);
        CHECK_EQ(swordsMan.get_number(), 4);
        swordsMan.receive_damage(135);
        CHECK_EQ(swordsMan.get_number(), 0);
        CHECK_FALSE(swordsMan.isAlive());
    }
    std::vector<SoldierPtr> hero_army;
    std::vector<SoldierPtr> enemy_army;
    hero_army.push_back(std::make_unique<SType::Archer>(4, 0, 2));
    hero_army.push_back(std::make_unique<SType::Pikeman>(2, 0, 7));
    hero_army.push_back(std::make_unique<SType::SwordsMan>(2, 0, 11));

    enemy_army.push_back(std::make_unique<SType::Archer>(5, 15, 5));
    enemy_army.push_back(std::make_unique<SType::Pikeman>(6, 15, 10));

    AlivePlayer player;
    SUBCASE("Testing AlivePlayer move and attack") {
        CHECK_FALSE(player.makeMove(15, 15, hero_army, enemy_army, 0));
        CHECK(player.makeMove(15, 10, hero_army, enemy_army, 0));
        CHECK_EQ(enemy_army.at(1)->get_number(), 5);
        CHECK(player.makeMove(4, 11, hero_army, enemy_army, 2));
        CHECK_EQ(hero_army.at(2)->getX(), 4);
        CHECK_EQ(hero_army.at(2)->getY(), 11);
        player.makeMove(9, 11, hero_army, enemy_army, 2);
        player.makeMove(13, 11, hero_army, enemy_army, 2);
        CHECK_EQ(hero_army.at(2)->getX(), 13);
        CHECK_EQ(hero_army.at(2)->getY(), 11);
        CHECK(player.makeMove(15, 10, hero_army, enemy_army, 2));
        CHECK_EQ(hero_army.at(2)->getX(), 14);
        CHECK_EQ(hero_army.at(2)->getY(), 11);
        CHECK_EQ(enemy_army.at(1)->get_number(), 4);
        player.makeMove(13, 11, hero_army, enemy_army, 2);
        enemy_army.push_back(std::make_unique<SType::Pikeman>(1, 14, 11));
        CHECK(player.makeMove(15, 10, hero_army, enemy_army, 2));
        CHECK_EQ(hero_army.at(2)->getX(), 14);
        CHECK_EQ(hero_army.at(2)->getY(), 10);
    }

    std::vector<UnitInfo> h_units;
    std::vector<UnitInfo> e_units;
    h_units.push_back(UnitInfo(Archer, 3));

    e_units.push_back(UnitInfo(Pikeman, 1));
    SUBCASE("Testing Battle") {
        Battle battle(false);
        battle.setArmy(h_units, e_units);
        CHECK_EQ(battle.getState(), heroTurn);
        battle.battleSpin(15, 7);
        CHECK_EQ(battle.getState(), enemyTurn);
        battle.battleSpin(0, 0);
        CHECK_EQ(battle.getState(), enemyTurn);
        battle.battleSpin(15, 6);
        CHECK_EQ(battle.getState(), heroTurn);
        battle.battleSpin(15, 6);
        CHECK_EQ(battle.getState(), won);
    }
    hero_army.clear();
    enemy_army.clear();
    // hero_army.push_back(std::make_unique<SType::Archer>(4, 0, 2));
    hero_army.push_back(std::make_unique<SType::SwordsMan>(5, 15, 2));
    hero_army.push_back(std::make_unique<SType::SwordsMan>(2, 15, 7));
    hero_army.push_back(std::make_unique<SType::SwordsMan>(2, 15, 12));
    // hero_army.push_back(std::make_unique<SType::SwordsMan>(2, 0, 11));

    enemy_army.push_back(std::make_unique<SType::Archer>(3, 0, 2));
    enemy_army.push_back(std::make_unique<SType::Pikeman>(5, 0, 7));
    enemy_army.push_back(std::make_unique<SType::SwordsMan>(2, 0, 12));
    SUBCASE("Testing AiPlayer") {
        AiPlayer player;
        State state(hero_army, enemy_army);
        std::vector<State> children;
        // player.addChildren(children, state, 0, state.my_army.size(), true);
        player.makeMove(0, 0, hero_army, enemy_army, 0);
        player.makeMove(0, 0, hero_army, enemy_army, 0);
        player.makeMove(0, 0, hero_army, enemy_army, 0);
        std::cout << "bbll";
    }
}