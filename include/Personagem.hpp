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
        virtual void mover() = 0;
        virtual void morrer() = 0;
};

#endif
