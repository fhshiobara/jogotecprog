#ifndef INIMIGO_HPP
#define INIMIGO_HPP
 
#include "Personagem.hpp"
#include "Animation.hpp"
#include "Jogador.hpp"

namespace Personagens {
    
    class Inimigo : public Personagem {
        protected:
            float dt_local;

            // Jogador* pJogador1;
            // Jogador* pJogador2;

        public:
            Inimigo(CoordF position, int hp, float velocidade, Jogador* pJogador1 = NULL, Jogador* pJogador2 = NULL);
            ~Inimigo();

            virtual void executar() override=0;
            virtual void salvar() override=0;
            virtual void mover() override=0;
            virtual void morrer() override=0;
            virtual void initialize()=0;
            virtual void perseguir(CoordF posJogador, float dt)=0;
            virtual void danificar(Jogador* pJog)=0;
            
            bool estaOlhandoEsquerda() const { return olhandoEsquerda; }
            void setDt(float dt) override;

            CoordF getPos() const { return pos; }
            bool jogadorProximo(Jogador* pJ1, Jogador* pJ2);
    };
}
 
#endif
