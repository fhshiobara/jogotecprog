#ifndef ENTE_HPP
#define ENTE_HPP

#include <SFML/Graphics.hpp>
#include "GerenciadorGrafico.hpp"
#include "Animation.hpp"
#include "VectorTL.hpp"


class Ente {
    protected:
        int id;
        static int cont_id;

        static Gerenciadores::GerenciadorGrafico *pGG;

        sf::RectangleShape hitbox;
        Animation sprite;
    public:
        static void setGG(Gerenciadores::GerenciadorGrafico *p) { pGG = p; }

        Ente();
        virtual ~Ente();
        virtual void executar() = 0;
        void desenhar();
        int getId() const { return id; }
        // void desenharHitbox(); 

};

#endif
