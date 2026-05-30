#include "Jogador.hpp"

static const float GRAVIDADE     = 800.f;  // px/s²

Jogador::Jogador(CoordF position, int hp, int pontos, float velocidade)

    : Personagem(position, hp), pontos(pontos), velocidade(velocidade),

      velocidadeY(0.f), dt_local(0.f), encostadochao(false)

{

    this->pos = position;

}

Jogador::~Jogador() {}



void Jogador::executar() {}



void Jogador::moverX(bool direcao, float dt) {

    if (direcao) {
        this->pos.x += velocidade * dt;
    } else {
        this->pos.x -= velocidade * dt;
    }

}



void Jogador::mover() {
}



void Jogador::moverY(bool direcao) {
    if (direcao) {
        this->pos.y += velocidade*dt_local;
    } else {
        this->pos.y -= velocidade*dt_local;
    }
}

void Jogador::salvar() {}
void Jogador::morrer() {}

void Jogador::pular() {

    if (encostadochao) {

        velocidadeY = -420.f;  // impulso para cima

        encostadochao = false;

    }

}



void Jogador::gravidade(float dt) {

    velocidadeY += 800.f * dt;  // aceleração da gravidade

    pos.y       += velocidadeY * dt;

    encostadochao = false;      // resetado aqui; plataforma reativa se houver colisão

}


void Jogador::atualizarAnimacao(Animation_ID id, bool olhandoEsquerda, float dt){

    this->dt_local = dt;
    this->sprite.update(id,olhandoEsquerda,this->pos,dt);

}

void Jogador::desenhar(){

    this->sprite.render();

}

void Jogador::setDt(float dt) { this->dt_local = dt; }
void Jogador::initialize() {

    this->sprite.addNewAnimation(Animation_ID::idle,"../assets/Knight/IDLE.png",7);

    this->sprite.addNewAnimation(Animation_ID::walk,"../assets/Knight/WALK.png",8);

    this->sprite.addNewAnimation(Animation_ID::attack,"../assets/Knight/ATTACK 1.png",6);

}



