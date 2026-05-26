#include "Jogador.hpp"
#include "Ente.hpp"

Jogador::Jogador(float Xinicial, float inicialY, int hp, int pontos, float velocidade) : Personagem(Xinicial, inicialY, hp), Ente("../assets/knight.png"), pontos(pontos), velocidade(velocidade) {}

Jogador::~Jogador() {}

void Jogador::executar() {}

void Jogador::moverX(bool direcao) {
    if (direcao) {
        this->pos.x += velocidade;
    } else {
        this->pos.x -= velocidade;
    }
    // sprite.setPosition(pos);
}

void Jogador::moverY(bool direcao) {
    if (direcao) {
        this->pos.y += velocidade;
    } else {
        this->pos.y -= velocidade;
    }
    // sprite.setPosition(pos); <- inserir em func. atualizar_pos depois
}

void Jogador::salvar() {}
void Jogador::morrer() {}