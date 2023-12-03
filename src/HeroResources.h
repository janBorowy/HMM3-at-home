class HeroResources {
    int stamina_;
    int const movement_;

   public:
    HeroResources(int movement);
    int refreshStamina();
    int stamina() const;
    int movement() const;
    void reduceStaminaByStep();
    bool canMove() const;
    int calculateMaxSteps() const;
};