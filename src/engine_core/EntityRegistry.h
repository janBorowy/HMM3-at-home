#include <map>
#include <stdexcept>
#include "GameEntity.h"

class EntityRegistry {
    std::map<int, std::shared_ptr<GameEntity>> entities;

   public:
    class IllegalEntityException : public std::runtime_error {
       public:
        IllegalEntityException() : runtime_error("nullptr entity passed") {}
    };
    EntityRegistry();
    std::shared_ptr<GameEntity> getEntityHandle(unsigned id);
    unsigned putEntity(std::shared_ptr<GameEntity> const &entity);
    std::map<int, std::shared_ptr<GameEntity>>::iterator begin();
    std::map<int, std::shared_ptr<GameEntity>>::iterator end();
};