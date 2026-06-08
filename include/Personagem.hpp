#ifndef Personagem_hpp
#define Personagem_hpp

#include "Entidade.hpp"

class Personagem: public Entidades::Entidade {
    protected:
        int Hp;
        float velocidade;
        bool olhandoEsquerda;
        bool encostadochao;
        bool vivo;
        
    public:
        Personagem(CoordF position, CoordF velocidade, int hp = 1, float velocidadeInicial = 0.0f, bool olhandoEsquerda = false, bool encostadochao = true, bool vivo = true);
        ~Personagem();

        void salvarDataBuffer();

        virtual void executar() = 0;
        virtual void salvar() = 0;
        virtual void mover() = 0;
        virtual void morrer() = 0;
};

#endif
