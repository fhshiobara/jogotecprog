#ifndef Personagem_hpp
#define Personagem_hpp

#include "Entidade.hpp"

class Personagem: public Entidades::Entidade {
    protected:
        int Hp;
    public:
        Personagem(float Xinicial, float inicialY, int hp = 1);
        ~Personagem();

        void salvarDataBuffer();

        virtual void executar() = 0;
        virtual void salvar() = 0;

        virtual void moverY(bool direcao) = 0;
        virtual void moverX(bool direcao) = 0;
};

#endif