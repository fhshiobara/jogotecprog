#ifndef ENTE_HPP
#define ENTE_HPP

#include <SFML/Graphics.hpp>
#include "GerenciadorGrafico.hpp"


class Ente {
    protected:
        int id;
        static Gerenciadores::GerenciadorGrafico *pGG;
        sf::Sprite sprite;
        static int cont_id;
        sf::RectangleShape hitbox;
    public:
        static void setGG(Gerenciadores::GerenciadorGrafico *p) { pGG = p; }

        Ente();
        virtual ~Ente();
        virtual void executar() = 0;
        void desenhar();

};

#endif
