#include "Inimigo.hpp"
#include <cmath>
 
Inimigo::Inimigo(CoordF position, int hp, float velocidadeInicial)
    : Personagem(position, CoordF(0.f, 0.f), hp, velocidadeInicial, false, true, true),
      dt_local(0.0f) {}
 
Inimigo::~Inimigo() {}
 
void Inimigo::executar() {}
void Inimigo::salvar()   {}
void Inimigo::mover()    {}
 
void Inimigo::morrer() {
    vivo = false;
}
 
bool Inimigo::estaVivo() const {
    return vivo;
}
 
void Inimigo::perseguir(CoordF posJogador, float dt) {
    this->dt_local = dt;
 
    float dx = posJogador.x - this->pos.x;
    float dy = posJogador.y - this->pos.y;
 
    float distancia = std::sqrt(dx * dx + dy * dy);
 
    if (distancia > 5.0f) {
        this->pos.x += (dx / distancia) * velocidade * dt;
        this->pos.y += (dy / distancia) * velocidade * dt;
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
    this->sprite.addNewAnimation(Animation_ID::idle, "assets/Enemy/IDLE.png",   4);
    this->sprite.addNewAnimation(Animation_ID::walk, "assets/Enemy/FLYING.png", 4);
    this->sprite.addNewAnimation(Animation_ID::hurt, "assets/Enemy/HURT.png",   4);
    // Mudar path caso falha ao encontrar.
}
