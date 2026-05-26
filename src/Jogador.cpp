#include "Jogador.hpp"


Jogador::Jogador(CoordF position, int hp, int pontos, float velocidade) : Personagem(position,hp), pontos(pontos), velocidade(velocidade) {this->pos=position;}

Jogador::~Jogador() {}

void Jogador::executar() {}

void Jogador::moverX(bool direcao) {
    if (direcao) {
        this->pos.x += 10.0f;
    } else {
        this->pos.x -= 10.0f;
    }
    std::cout<<"Posicao em x mudou para: "<<this->pos.x<<std::endl;
}

void Jogador::mover() {
    // Pode deixar essa função vazia, já que estamos controlando o teclado direto pelo Jogo.cpp!
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
/*void Jogador::mover( ){
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        moverX(true);
    } // pode aumentar para a seta direita para o p2
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        moverX(false);
    } // pode aumentar para a seta esquerda para o p2
    
}*/

void Jogador::atualizarAnimacao(Animation_ID id, bool olhandoEsquerda, float dt){
    this->dt_local = dt;
    this->sprite.update(id,olhandoEsquerda,this->pos,dt);
}

void Jogador::desenhar(){
    this->sprite.render();
}
void Jogador::setDt(float dt){this->dt_local = dt;}


void Jogador::initialize(){
    
    this->sprite.addNewAnimation(Animation_ID::idle,"assets/Knight/IDLE.png",7);
    this->sprite.addNewAnimation(Animation_ID::walk,"assets/Knight/WALK.png",8);
    this->sprite.addNewAnimation(Animation_ID::attack,"assets/Knight/ATTACK 1.png",6);
}
