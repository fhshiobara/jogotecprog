#ifndef INIMIGO_HPP
#define INIMIGO_HPP
 
#include "Personagem.hpp"
#include "Animation.hpp"
 
class Inimigo : public Personagem {
    protected:
        
        float dt_local;
 
    public:
        Inimigo(CoordF position, int hp, float velocidade);
        ~Inimigo();
 
        void executar();
        void salvar();
        void mover();
        void morrer();
        void initialize();
        
        bool estaOlhandoEsquerda() const { return olhandoEsquerda; }

        CoordF getPos() const { return pos; }
};
 
#endif
