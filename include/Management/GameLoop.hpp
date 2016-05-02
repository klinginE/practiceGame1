#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

namespace sg {
    
    class GameLoop {
    
        public:
            static GameLoop & inst();
            
            void init(const sf::Vector2u &windowDimensions,
                      const sf::String &windowName);
    
            void start();
    
            sf::RenderWindow & getRenderWindow();
    
            ~GameLoop() {}
    
        private:
            
            sf::RenderWindow window;
            bool paused = false;
    
            GameLoop() {}
            GameLoop(GameLoop const&) = delete;
            void operator=(GameLoop const&) = delete;
    };
}
