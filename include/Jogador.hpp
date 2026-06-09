#ifndef JOGADOR_HPP
#define JOGADOR_HPP
 
#include "Personagem.hpp"
#include "Animation.hpp"
 
class Jogador: public Personagem {
 
    protected:
        int pontos;
        float dt_local;
 
    public:
        Jogador(CoordF position, int hp = 3, int pontos = 0, float speed = 1.0f);
        ~Jogador();
 
        CoordF getPos() const { return pos; }
        void   setPos(const CoordF& newPos) { pos = newPos; }
 
        CoordF getVel() const { return vel; }
        void   setVel(const CoordF& v) { vel = v; }
 
        bool noChao() const { return encostadochao; }
        void setChao(bool val) { encostadochao = val; }
 
        void executar();
        void salvar();
        void morrer();
        void initialize();
        void mover();
        void pular();
        void gravidade(float dt);
        void setDt(float dt);
 
        void atualizarAnimacao(Animation_ID, bool olhandoEsquerda, float dt);
        void desenhar();
 
        void moverX(bool direcao, float dt);
};
 
#endif
