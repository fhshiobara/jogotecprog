#ifndef BIXO_HPP
#define BIXO_HPP
 
#include "Inimigo.hpp"
#include "Obstaculo.hpp"
#include <list>

namespace Personagens {
 
    class Bixo : public Personagens::Inimigo {
        private:
            float percepcao;
        public:
            Bixo(CoordF position, int hp = 1, float velocidade = 120.0f, float percepcao = 150.0f);
            ~Bixo();
    
            void executar();
            void salvar();
            void mover();
            void morrer();
            void initialize();
        void danificar(Jogador* pJog);
    
            void perseguir(CoordF posJogador, float dt);
    };
}
#endif
