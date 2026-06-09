#include "Jogador.hpp"
 
static const float GRAVIDADE = 800.f;
 
Jogador::Jogador(CoordF position, int hp, int pontos, float speed)
    : Personagem(position, CoordF(0.f, 0.f), hp, 0.f, speed, false, true, true),
      pontos(pontos), dt_local(0.0f) {}
 
Jogador::~Jogador() {}
 
void Jogador::executar() {}
void Jogador::mover()    {}
void Jogador::salvar()   {}
void Jogador::morrer()   { std::cout << "Morreu!" << std::endl; }
 
void Jogador::moverX(bool direcao, float dt) {
    if (direcao)
        pos.x += speed * dt;
    else
        pos.x -= speed * dt;
}
 
void Jogador::pular() {
    if (encostadochao) {
        vel.y = speed * -2.0f;
        encostadochao = false;
    }
}
 
void Jogador::gravidade(float dt) {
    vel.y += GRAVIDADE * dt;
    pos.y += vel.y * dt;
    encostadochao = false;
}
 
void Jogador::atualizarAnimacao(Animation_ID id, bool olhandoEsquerda, float dt) {
    this->dt_local = dt;
    this->sprite.update(id, olhandoEsquerda, this->pos, dt);
}
 
void Jogador::desenhar() {
    this->sprite.render();
}
 
void Jogador::setDt(float dt) { this->dt_local = dt; }
 
void Jogador::initialize() {
    this->sprite.addNewAnimation(Animation_ID::idle,   "assets/Knight/IDLE.png",     7);
    this->sprite.addNewAnimation(Animation_ID::walk,   "assets/Knight/WALK.png",     8);
    this->sprite.addNewAnimation(Animation_ID::attack, "assets/Knight/ATTACK 1.png", 6);
    this->sprite.addNewAnimation(Animation_ID::jump,   "assets/Knight/JUMP.png",     5);
    // Verificar path se der erro! Deve-se mudar o path em relacao a onde o jogo esta sendo built.
}
