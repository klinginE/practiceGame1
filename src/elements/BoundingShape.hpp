#pragma once

//C++ includes
#include <vector>
#include <stdint.h>

//SFML includes
#include <SFML/Graphics.hpp>

namespace sg {

    class BoundingShape : public sf::Transformable {

        private:
            //Private member variables
            std::vector<sf::Shape *> shapes;
            //Private member functions
            sf::FloatRect getBounds(bool) const;
            const sf::ConvexShape approximateCircle(const sf::CircleShape &, const sf::Transformable &, const sf::Transformable &) const;
            sf::Vector2f calculateUnitNormal(const sf::Shape &, uint32_t, const sf::Transformable &, const sf::Transformable &) const;
            float projectPoint(const sf::Shape &, const sf::Vector2f &, uint32_t, const sf::Transformable &, const sf::Transformable &) const;
            bool collides_ptp(const sf::Shape &, const sf::Shape &, sf::Vector2f &, const sf::Transformable &, const sf::Transformable &, const sf::Transformable &, const sf::Transformable &) const;
            bool collides_ctp(const sf::Shape &, const sf::Shape &, sf::Vector2f &, const sf::Transformable &, const sf::Transformable &, const sf::Transformable &, const sf::Transformable &) const;
            bool collides_ctc(const sf::Shape &, const sf::Shape &, sf::Vector2f &, const sf::Transformable &, const sf::Transformable &, const sf::Transformable &, const sf::Transformable &) const;

        public:
            //Public member functions
            ~BoundingShape();
            std::vector<sf::Shape *>::size_type getNumOfShapes() const;
            const sf::Shape *getShape(uint32_t) const;
            std::vector<sf::Shape *>::size_type addShape(sf::Shape &);
            sf::Shape *removeShape(uint32_t);
//            void setOrigin(float, float);
            void setOriginShape(uint32_t, const sf::Vector2f &);
//            void setPosition(float, float);
            void setPositionShape(uint32_t, const sf::Vector2f &);
//            void move(float, float);
            void moveShape(uint32_t, const sf::Vector2f &);
            void setRotationShape(uint32_t, float);
            void rotateShape(uint32_t, float);
//            void setScale(float, float);
            void setScaleShape(uint32_t, const sf::Vector2f &);
//            void scale(float, float);
            void scaleShape(uint32_t, const sf::Vector2f &);
            sf::FloatRect getLocalBounds() const;
            sf::FloatRect getGlobalBounds() const;
            bool collides(const BoundingShape &, sf::Vector2f &, const sf::Transformable &, const sf::Transformable &) const;

    };

}
