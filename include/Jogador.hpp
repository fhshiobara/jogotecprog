#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include "Personagem.hpp"
#include "Animation.hpp"

class Jogador: public Personagem {

    protected:

        int pontos;
        float velocidade;
        float velocidadeY;
        CoordF pos;
        float dt_local;
        bool encostadochao;

    public:

        Jogador(CoordF position, int hp = 3, int pontos = 0, float velocidade = 1.0f);
        ~Jogador();

        CoordF getPos() const { return pos; }
        void setPos(const CoordF& newPos) { pos = newPos; }

        bool noChao() const { return encostadochao; }
        void setChao(bool val) { encostadochao = val; }

        float getVelocidadeY() const { return velocidadeY; }
        void setVelocidadeY(float v)  { velocidadeY = v; }



        void setVelocidade(float vel) { velocidade = vel; }
        float getVelocidade() const { return velocidade; }

        

        void executar();

        void salvar();

        void morrer();

        void initialize();

        void mover();

        void pular();

        void gravidade(float dt);

        void setDt(float dt);

        void atualizarAnimacao(Animation_ID,bool olhandoEsquerda,float dt);

        void desenhar();

        void moverX(bool direcao, float dt); // 0 esquerda, 1 direita
        void moverY(bool direcao);

};

#endif