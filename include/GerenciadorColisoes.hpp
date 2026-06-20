#ifndef GERENCIADORCOLISOES_HPP
#define GERENCIADORCOLISOES_HPP
 
#include <vector>
#include <list>
#include <cmath>
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Demonio.hpp"
#include "Bixo.hpp"
#include "Obstaculo.hpp"
 
using namespace Personagens;
using namespace Obstaculos;

namespace Gerenciadores {
 
    class GerenciadorColisoes {
        private:
 
            std::vector<Personagens::Inimigo*> ListaInimigos;
            std::list<Obstaculos::Obstaculo*> ListaObstaculos;
            
            Personagens::Jogador* pJog1;
            Personagens::Jogador* pJog2;
            
            CoordF limites;   // substitui classe Limites

            static const float alturaJogador; // Mudar
            static const float alturaBixo;
 
            static GerenciadorColisoes* instance;
            GerenciadorColisoes();
 
        public:
            ~GerenciadorColisoes();

            static GerenciadorColisoes* getInstance();

            void aplicarLimites(Personagens::Personagem* pPersonagem); // logica antes em Limites
 
            void setJogador(Personagens::Jogador* pJogador);
            void setLimite(CoordF tam_tela);
 
            void incluirInimigo(Personagens::Inimigo* pInimigo);
            void removerInimigo(Personagens::Inimigo* pInimigo);
            void incluirObstaculo(Obstaculos::Obstaculo* pObstaculo);
 
            void tratarColisoesObstaculos();
            void tratarColisoesJogador();
            void tratarColisoesObstaculosBixos();
            void tratarColisaoProjetil();
            void tratarAtaqueJogadores();
            
            void tratarLimites();
 
            void executar(float dt);
            void gravitar(float dt);
            
            void atualizarImunidades(float dt);
    };
 
    #define pColisM Gerenciadores::GerenciadorColisoes::getInstance()
 
}
 
#endif
