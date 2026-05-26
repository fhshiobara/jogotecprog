#ifndef Personagem_hpp
#define Personagem_hpp

#include "Entidade.hpp"

class Personagem: public Entidades::Entidade {
    protected:
        int Hp;
    CoordF pos;
    public:
        Personagem(CoordF position, int hp = 1);
        ~Personagem();

        void salvarDataBuffer();

        virtual void executar() = 0;
        virtual void salvar() = 0;
        virtual void mover() = 0;
        virtual void morrer() = 0;
};

#endif
