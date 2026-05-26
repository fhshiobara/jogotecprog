#ifndef ENTE_HPP
#define ENTE_HPP

#include <SFML/Graphics.hpp>
#include "GerenciadorGrafico.hpp"


class Ente {
    protected:
        static int idCounter;
        int id;
        static Gerenciadores::GerenciadorGrafico *pGG;
        sf::Sprite sprite;
        sf::Texture textura;
    public:
        static void setGG(Gerenciadores::GerenciadorGrafico *p) { pGG = p; }

        Ente(const char* pathToTexture = nullptr);

        void setSprite(sf::Texture& textura) { sprite.setTexture(textura); }
        sf::Sprite* getSprite() { return &sprite; }
        void setTextura(const sf::Texture& textura) { this->textura = textura; }
        sf::Texture* getTextura() { return &textura; }

        virtual ~Ente();
        virtual void executar() = 0;
        void desenhar();
};

#endif