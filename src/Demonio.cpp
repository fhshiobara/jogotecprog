#include "Demonio.hpp"
#include <cmath>

Demonio::Demonio(CoordF position, int hp, float velocidade, int fome)
    : Inimigo(position, hp, velocidade), fome(fome) {}

Demonio::~Demonio() {}

void Demonio::perseguir(CoordF posJogador, float dt) {
    this->dt_local = dt;
 
    float dx = posJogador.x - this->pos.x;
    float dy = posJogador.y - this->pos.y;
 
    float distancia = std::sqrt(dx * dx + dy * dy);
 
    if (distancia > 5.0f) {
        this->pos.x += (dx / distancia) * velocidade * dt * (fome / 100.0f);
        this->pos.y += (dy / distancia) * velocidade * dt * (fome / 100.0f);
        olhandoEsquerda = (dx > 0);
    }
}

void Demonio::initialize() {
    this->sprite.addNewAnimation(Animation_ID::idle, "../assets/Demonio/IDLE.png", 4);
    this->sprite.addNewAnimation(Animation_ID::walk, "../assets/Demonio/FLYING.png", 4);
    this->sprite.addNewAnimation(Animation_ID::hurt, "../assets/Demonio/HURT.png", 4);
    // Mudar path caso falha ao encontrar.
}

void Demonio::executar() { this->desenhar();}
void Demonio::salvar() {}
void Demonio::mover() {}
void Demonio::morrer() {
    vivo = false;
    std::cout << "Demonio morreu!" << std::endl;
}
