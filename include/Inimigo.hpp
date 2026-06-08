#ifndef INIMIGO_HPP
#define INIMIGO_HPP
 
#include "Personagem.hpp"
#include "Animation.hpp"
 
class Inimigo : public Personagem {
    protected:
        float dt_local;
 
    public:
        Inimigo(CoordF position, int hp = 2, float velocidade = 80.0f);
        ~Inimigo();
 
        void executar();
        void salvar();
        void mover();
        void morrer();
        void initialize();
 
        void perseguir(CoordF posJogador, float dt);
        void atualizarAnimacao(Animation_ID id, bool olhandoEsquerda, float dt);
        void desenhar();
 
        bool estaVivo() const;
        bool estaOlhandoEsquerda() const { return olhandoEsquerda; }

        CoordF getPos() const { return pos; }
};
 
#endif
