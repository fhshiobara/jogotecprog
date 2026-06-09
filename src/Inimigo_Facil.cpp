#include "Inimigo_Facil.hpp"
#include <cmath>
 
Arvore::Arvore(CoordF position, int hp, float velocidade, float percepcao)
    : Inimigo(position, hp, velocidade), percepcao(percepcao) {}
 
Arvore::~Arvore() {}
 
void Arvore::executar() {}
void Arvore::salvar() {}
void Arvore::mover() {}
 
void Arvore::morrer() {
    vivo = false;
    std::cout << "Arvore morreu!" << std::endl;
}
 
void Arvore::perseguir(CoordF posJogador, float dt) {
    this->dt_local = dt;
 
    float dx = posJogador.x - this->pos.x;
    float dy = posJogador.y - this->pos.y;
 
    float distancia = std::sqrt(dx * dx + dy * dy);

    if (distancia > percepcao) return; // Aqui definimos a dist. para o golbin perseguir
 
    // Só se move no eixo X
    if (distancia > 5.0f) {
        float direcaoX = dx / distancia;
        this->pos.x += direcaoX * velocidade * dt;
        olhandoEsquerda = (dx > 0);
    }
}

void Arvore::gravidade(float dt, float gravidade) {
    vel.y += gravidade * dt;
    pos.y += vel.y * dt;
    encostadochao = false;
}
 
void Arvore::initialize() {
    this->sprite.addNewAnimation(Animation_ID::idle, "../assets/Arvore/IDLE.png", 4);
    this->sprite.addNewAnimation(Animation_ID::walk, "../assets/Arvore/WALK.png", 8);
}
