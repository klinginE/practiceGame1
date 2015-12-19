
#include "GameWorld.hpp"
#include "../elements/Entity.hpp"
#include "GameLoop.hpp"

#include "GameWorld.hpp"

namespace sg {
    
    // CONSTRUCTORS

    GameWorld::GameWorld() {
        inputManager = NULL;
        inputActive = false;
        scanlineType = scanline_t::HORIZONTAL;
        collisionActive = true;
    }
    GameWorld::GameWorld(InputManager *inputManager) {
        this->inputManager = inputManager;
        this->inputActive = true;
        this->scanlineType = scanline_t::HORIZONTAL;
        this->collisionActive = true;
    }
    GameWorld::GameWorld(std::vector<Entity *> entities) {
        this->entities = entities;
        this->inputManager = NULL;
        this->inputActive = false;
        this->scanlineType = scanline_t::HORIZONTAL;
        this->collisionActive = true;
        sortEntities();
    }
    GameWorld::GameWorld(InputManager *inputManager,
                         std::vector<Entity *> entities) {
        this->entities = entities;
        this->inputManager = inputManager;
        this->inputActive = true;
        this->scanlineType = scanline_t::HORIZONTAL;
        this->collisionActive = true;
        // TODO: sort entities here
        sortEntities();
    }

    void GameWorld::update(const sf::Time &tslu) {
        // process input
        if (inputActive && inputManager)
            inputManager->processInput();
        // update all entities
        for (auto entityIter = entities.begin();
             entityIter != entities.end(); ++entityIter) {
            Entity *e = *entityIter;
            e->update(tslu);
        }
        // Detect and resolve collisions between entities
        if (collisionActive)
            scanline();
    }

    float GameWorld::scanMin(Entity *e) {
        if (scanlineType == scanline_t::HORIZONTAL)
            return e->getSurfaceBounds().left;

        return e->getSurfaceBounds().top;
    }
    float GameWorld::scanMax(Entity *e) {
        if (scanlineType == scanline_t::HORIZONTAL)
            return e->getSurfaceBounds().left
                 + e->getSurfaceBounds().width;

        return e->getSurfaceBounds().top
             + e->getSurfaceBounds().height;
    }

    void GameWorld::scanline() {
        // sort all entities before scanline 
        sortEntities();
        
        // TODO: scanline
        for (auto i1 = entities.begin();
             i1 != entities.end(); ++i1) {
            Entity *e1 = *i1;

            if (!e1->getIsCollidable())
                continue;

            for (auto i2 = i1;
                 i2 != entities.end() && scanMin(*i2) <= scanMax(e1);
                 ++i2) {
                
                Entity *e2 = *i2;

                if (!e2->getIsCollidable())
                    continue;

                e1->collides(*e2);

            }
        }
    }

    void GameWorld::addEntity(Entity *entity) {
        entities.push_back(entity);
    }
    void GameWorld::removeEntity(Entity *entity) {
        deleteSet.insert(entity);
    }
    std::vector<Entity *> GameWorld::getEntities() {
        return entities;
    }

    void GameWorld::activateCollisions() {
        collisionActive = true;
    }
    void GameWorld::deactivateCollisions() {
        collisionActive = false;
    }
    bool GameWorld::getCollisionStatus() {
        return collisionActive;
    }

    void GameWorld::activateInput() {
        inputActive = true;
    }
    void GameWorld::deactivateInput() {
        inputActive = false;
    }
    bool GameWorld::getInputStatus() {
        return inputActive;
    }

    void GameWorld::setVerticalScanline() {
        scanlineType = scanline_t::VERTICAL;
    }
    void GameWorld::setHorizontalScanline() {
        scanlineType = scanline_t::HORIZONTAL;
    }
    scanline_t GameWorld::getScanlineStatus() {
        return scanlineType;
    }

    void GameWorld::setInputManager(InputManager * inputManager) {
        this->inputManager = inputManager;
    }

    bool verticalComparitor(Entity *e1, Entity *e2) {
        if (e1->getSurfaceBounds().top < e2->getSurfaceBounds().top)
            return true;
        
        return false;
    }
    bool horizontalComparitor(Entity *e1, Entity *e2) {
        if (e1->getSurfaceBounds().left < e2->getSurfaceBounds().left)
            return true;
        
        return false;
    }

    void GameWorld::sortEntities() {
        removeDeletedEntities();
        if (scanlineType == scanline_t::VERTICAL) {
            std::sort(entities.begin(), entities.end(),
                      verticalComparitor);
        }
        else {
            std::sort(entities.begin(), entities.end(),
                      horizontalComparitor);
        }
    }

}
