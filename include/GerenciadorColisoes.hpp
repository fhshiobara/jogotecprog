#ifndef GERENCIADORCOLISOES_HPP
#define GERENCIADORCOLISOES_HPP

#include <vector>
#include <list>
#include <cmath>
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Obstaculo.hpp"

namespace Gerenciadores {

    class GerenciadorColisoes {
        private:

            std::vector<Inimigo*> ListaInimigos;
            std::list<Obstaculos::Obstaculo*> ListaObstaculos;
            Jogador* pJog;

            static const float alturaJogador; // Mudar

            static GerenciadorColisoes* instance;
            GerenciadorColisoes();

        public:
            ~GerenciadorColisoes();

            static GerenciadorColisoes* getInstance();

            void setJogador(Jogador* pJogador);
            void incluirInimigo(Inimigo* pInimigo);
            void incluirObstaculo(Obstaculos::Obstaculo* pObstaculo);

            void tratarColisoesObstaculos();
            void TratarColisoesSeres();

            void executar();
    };

    #define pColisM Gerenciadores::GerenciadorColisoes::getInstance()

}

#endif
