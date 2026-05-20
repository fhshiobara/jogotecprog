#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include "Personagem.hpp"
#include "Ente.hpp"

class Jogador: public Ente, public Personagem {
    protected:
        int pontos;
        float velocidade;
    public:
        Jogador(float Xinicial, float inicialY, int hp = 3, int pontos = 0, float velocidade = 1.0f);
        ~Jogador();

        void executar();
        void salvar();
        void morrer();

        void moverX(bool direcao); // 0 esquerda, 1 direita
        void moverY(bool direcao);

};

#endif