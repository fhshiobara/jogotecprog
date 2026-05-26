#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include "Personagem.hpp"
#include "Animation.hpp"

class Jogador: public Personagem {
    protected:
        int pontos;
        float velocidade;
    CoordF pos;
    float dt_local;
    public:
        Jogador(CoordF position, int hp = 3, int pontos = 0, float velocidade = 1.0f);
        ~Jogador();

        void executar();
        void salvar();
        void morrer();
        void initialize();
        void mover();
    void setDt(float dt);
    
    void atualizarAnimacao(Animation_ID,bool olhandoEsquerda,float dt);
    void desenhar();

        void moverX(bool direcao); // 0 esquerda, 1 direita
        void moverY(bool direcao);

};

#endif
