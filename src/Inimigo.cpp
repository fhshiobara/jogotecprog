#include "Inimigo.hpp"
#include <cmath>

Inimigo::Inimigo(CoordF position, int hp, float velocidade)
    : Personagem(position, hp), velocidade(velocidade), dt_local(0.0f), olhandoEsquerda(false), vivo(true) {
    this->pos = position;
}

Inimigo::~Inimigo() {}

void Inimigo::executar() {}

void Inimigo::salvar() {}

void Inimigo::mover() {}

void Inimigo::morrer() {
    vivo = false;
}

bool Inimigo::estaVivo() const {
    return vivo;
}

// Move o inimigo em direção ao jogador automaticamente
void Inimigo::perseguir(CoordF posJogador, float dt) {
    this->dt_local = dt;

    float dx = posJogador.x - this->pos.x;
    float dy = posJogador.y - this->pos.y;

    // Distância entre inimigo e jogador
    float distancia = std::sqrt(dx * dx + dy * dy);

    // Só persegue se não estiver em cima do jogador
    if (distancia > 5.0f) {
        // Normaliza a direção e aplica velocidade * dt
        this->pos.x += (dx / distancia) * velocidade * dt;
        this->pos.y += (dy / distancia) * velocidade * dt;

        // Define para qual lado o inimigo está olhando
        olhandoEsquerda = (dx > 0);
    }
}

void Inimigo::atualizarAnimacao(Animation_ID id, bool olhandoEsquerda, float dt) {
    this->sprite.update(id, olhandoEsquerda, this->pos, dt);
}

void Inimigo::desenhar() {
    this->sprite.render();
}

void Inimigo::initialize() {
    this->sprite.addNewAnimation(Animation_ID::idle, "../assets/Enemy/IDLE.png", 4);
    this->sprite.addNewAnimation(Animation_ID::walk, "../assets/Enemy/FLYING.png", 4);
    this->sprite.addNewAnimation(Animation_ID::hurt, "../assets/Enemy/HURT.png", 4);
}
