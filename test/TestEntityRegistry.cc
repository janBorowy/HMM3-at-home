#include "../src/engine_core/EntityRegistry.h"
#include "../src/engine_core/components/BoxComponent.h"
#include "doctest.h"

TEST_CASE("EntityRegistry") {
    EntityRegistry registry;
    std::shared_ptr<GameEntity> entity(new GameEntity(new BoxComponent(64)));

    SUBCASE("Should put GameEntity properly") { registry.putEntity(entity); }

    SUBCASE("Should return correct entity id") {
        unsigned id = registry.putEntity(entity);
        CHECK_EQ(id, 1);
        id = registry.putEntity(entity);
        CHECK_EQ(id, 2);
    }

    SUBCASE("Should reject nullptr") {
        CHECK_THROWS_AS(
            registry.putEntity(std::shared_ptr<GameEntity>(nullptr)),
            EntityRegistry::IllegalEntityException);
    }

    SUBCASE("Should get correct entity") {
        unsigned id = registry.putEntity(entity);
        auto entityFound = registry.getEntityHandle(id);
        CHECK_EQ(entity, entityFound);
    }
}
