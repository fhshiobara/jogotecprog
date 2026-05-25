#include "Jogador.hpp"

Jogador::Jogador(float Xinicial, float inicialY, int hp, int pontos, float velocidade) : Ente(), Personagem(Xinicial, inicialY, hp), pontos(pontos), velocidade(velocidade) {}

Jogador::~Jogador() {}

void Jogador::executar() {}

void Jogador::moverX(bool direcao) {
    if (direcao) {
        this->pos.x += velocidade;
    } else {
        this->pos.x -= velocidade;
    }
}

void Jogador::moverY(bool direcao) {
    if (direcao) {
        this->pos.y += velocidade;
    } else {
        this->pos.y -= velocidade;
    }
}

void Jogador::salvar() {}
void Jogador::morrer() {}
