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
 
        virtual void executar() override =0;
        virtual void salvar() override=0;
        virtual void mover() override=0;
        virtual void morrer() override=0;
        virtual void initialize()=0;
        
        bool estaOlhandoEsquerda() const { return olhandoEsquerda; }
    
    void setDt(float dt) override;

        CoordF getPos() const { return pos; }
};
 
#endif
