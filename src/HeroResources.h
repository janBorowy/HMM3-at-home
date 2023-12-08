#pragma once
constexpr int ONE_FIELD_MOVEMENT_PENALTY = 100;

class HeroResources {
    int stamina_;
    int gold_;
    int wood_;
    int ore_;
    int const movement_;

   public:
    HeroResources(int movement);
    int refreshStamina();
    int stamina() const;
    int movement() const;
    void reduceStaminaByStep();
    bool canMove() const;
    int calculateMaxSteps() const;
    int gold() const;
    int wood() const;
    int ore() const;
    void addGold(int);
    void addWood(int);
    void addOre(int);
};