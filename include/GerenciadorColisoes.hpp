#ifndef GERENCIADORCOLISOES_HPP
#define GERENCIADORCOLISOES_HPP
 
#include <vector>
#include <list>
#include <cmath>
#include "Limites.hpp"
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Demonio.hpp"
#include "Arvore.hpp"
#include "Obstaculo.hpp"
 
namespace Gerenciadores {
 
    class GerenciadorColisoes {
        private:
 
            std::vector<Inimigo*> ListaInimigos;
            std::list<Obstaculos::Obstaculo*> ListaObstaculos;
            Jogador* pJog;
            Jogador* pJog2;
            
            Obstaculos::Limites* limites;
 
            static const float alturaJogador; // Mudar
 
            static GerenciadorColisoes* instance;
            GerenciadorColisoes();
 
        public:
            ~GerenciadorColisoes();
 
            static GerenciadorColisoes* getInstance();
 
            void setJogador(Jogador* pJogador);
            void setLimite(float largura, float altura);
 
            void incluirInimigo(Inimigo* pInimigo);
            void incluirObstaculo(Obstaculos::Obstaculo* pObstaculo);
 
            void tratarColisoesObstaculos();
            void tratarColisoesJogador();
            void tratarColisoesObstaculosArvores();
            void tratarColisaoProjetil();
            
            void tratarLimites();
 
            void executar(float dt);
            void gravitar(float dt);
    };
 
    #define pColisM Gerenciadores::GerenciadorColisoes::getInstance()
 
}
 
#endif
