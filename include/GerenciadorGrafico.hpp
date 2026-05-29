#ifndef GerenciadorGrafico_hpp
#define GerenciadorGrafico_hpp


#include <iostream>
#include <SFML/Graphics.hpp>

namespace Gerenciadores{
        
    class GerenciadorGrafico{
        private:
            sf::RenderWindow* window;
            sf::View view;
            std::map<const char*,sf::Texture*> texturesMap;
            sf::Font* font;
            sf::Clock clock;
            static float dt;
            
            static Gerenciadores::GerenciadorGrafico* instance;
            GerenciadorGrafico();

        public:
            ~GerenciadorGrafico();
            
            static GerenciadorGrafico* getInstance();
            
            void render(sf::RectangleShape* hitbox);
            
            void render(sf::Text* txt);
            
            bool windowopen()const;
            
            void closeWindow();
            
            void display();
            
            void clear();
            
            sf::RenderWindow* getWindow();
            
            sf::Texture* loadTexture(const char* path);
            
    };
#define pGraphicM Gerenciadores::GerenciadorGrafico::getInstance()
}

#endif
