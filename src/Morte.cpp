#include "Morte.hpp"
#include <cmath>

Morte::Morte(CoordF position, int hp, float velocidade, int morte)
    : Inimigo(position, hp, velocidade) {}

Morte::~Morte() {}

void Morte::perseguir(CoordF posJogador, float dt) {
    this->dt_local = dt;
 
    float dx = posJogador.x - this->pos.x;
    float dy = posJogador.y - this->pos.y;
 
    float distancia = std::sqrt(dx * dx + dy * dy);
 
    if (distancia > 5.0f) {
        this->pos.x += (dx / distancia) * velocidade * dt;
        this->pos.y += (dy / distancia) * velocidade * dt;
        olhandoEsquerda = (dx > 0);
    }
} // Por enquanto, igual ao do demonio

void Morte::initialize() {
    this->sprite.addNewAnimation(Animation_ID::idle, "../assets/Morte/IDLE.png", 8);
    this->sprite.addNewAnimation(Animation_ID::walk, "../assets/Morte/FLYING.png", 13);
    // this->sprite.addNewAnimation(Animation_ID::hurt, "../assets/Morte/HURT.png", 4);
    // Mudar path caso falha ao encontrar.
}

void Morte::executar() {}
void Morte::salvar() {}
void Morte::mover() {}
void Morte::morrer() {
    vivo = false;
    std::cout << "Morte morreu!" << std::endl;
}
