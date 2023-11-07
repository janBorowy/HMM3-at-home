#include "EntityRegistry.h"

EntityRegistry::EntityRegistry() : entities() {}

unsigned EntityRegistry::putEntity(std::shared_ptr<GameEntity> const &entity) {
    if (!entity) {
        throw IllegalEntityException();
    }
    size_t count = entities.size();
    unsigned id = count + 1;
    entities.insert({id, entity});
    return id;
}

std::shared_ptr<GameEntity> EntityRegistry::getEntityHandle(unsigned id) {
    return entities.at(id);
}

std::map<int, std::shared_ptr<GameEntity>>::iterator EntityRegistry::begin() {
    return entities.begin();
}
std::map<int, std::shared_ptr<GameEntity>>::iterator EntityRegistry::end() {
    return entities.end();
}
