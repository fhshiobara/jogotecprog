#include "Jogador.hpp"

namespace Personagens {
     const float Jogador::DURACAO_ATAQUE = 0.3f; // 0.3s... Alterar aqui a duracao do ataque

    Jogador::Jogador(CoordF position, int hp, int pontos, float speed)
        : Personagem(position, CoordF(0.f, 0.f), hp, 0.f, speed, false, true, true),
        pontos(pontos), dt_local(0.0f),Invulneravel(false),tempoInvulneravel(0.5),Devagar(false), tempoDevagar(1.0) {}
    
    Jogador::~Jogador() {}
    
    void Jogador::executar() {}
    void Jogador::mover()    {}
    void Jogador::salvar()   {}
    void Jogador::morrer()   { std::cout << "Jogador morreu!" << std::endl; }
    
    void Jogador::moverX(bool direcao, float dt) {
        if(Devagar){
            if (direcao)
                pos.x += speed * dt/2;
            else
                pos.x -= speed * dt/2;
            
        }
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
    
    void Jogador::atualizarAnimacao(Animation_ID id, bool olhandoEsquerda, float dt) {
        this->dt_local = dt;
        this->sprite.update(id, olhandoEsquerda, this->pos, dt);
    }
    
    void Jogador::desenhar() {
        this->sprite.render();
    }
    
    void Jogador::initialize(bool Jog) {
        if(Jog == false){
            this->sprite.addNewAnimation(Animation_ID::idle,   "assets/Knight/IDLE.png",  7);
            this->sprite.addNewAnimation(Animation_ID::walk,   "assets/Knight/WALK.png",  8);
            this->sprite.addNewAnimation(Animation_ID::attack, "assets/Knight/ATTACK 1.png", 6);
            this->sprite.addNewAnimation(Animation_ID::jump,   "assets/Knight/JUMP.png", 5);
            this->sprite.addNewAnimation(Animation_ID::attack, "assets/Knight/ATTACK 3.png", 6);
            this->sprite.addNewAnimation(Animation_ID::hurt, "assets/Knight/HURT.png", 4);
        }
        if(Jog == true){
            this->sprite.addNewAnimation(Animation_ID::idle,   "assets/Knight2/IDLE.png", 7);
            this->sprite.addNewAnimation(Animation_ID::walk,   "assets/Knight2/WALK.png",  8);
            this->sprite.addNewAnimation(Animation_ID::attack, "assets/Knight2/ATTACK 1.png", 6);
            this->sprite.addNewAnimation(Animation_ID::jump,   "assets/Knight2/JUMP.png", 5);
            this->sprite.addNewAnimation(Animation_ID::attack, "assets/Knight2/ATTACK 3.png", 6);
            this->sprite.addNewAnimation(Animation_ID::hurt, "assets/Knight2/HURT.png", 4);
        }
        
        // Verificar path se der erro! Deve-se mudar o path em relacao a onde o jogo esta sendo built.
    }

    void Jogador::golpear() {
        if(!atacando) {
            atacando = true;
            tempoAtaqueAtual = DURACAO_ATAQUE;
        }
    }

    void Jogador::atualizarGolpe(float dt) {
        if(!atacando) return;

        tempoAtaqueAtual -= dt;
        if(tempoAtaqueAtual <= 0.0f)
            atacando = false;
    }
//funcoes suporte para o meu danificar
bool Jogador::getInvulneravel(){
    return Invulneravel;
}

bool Jogador::getDevagar(){
    return Devagar;
}

void Jogador::setInvulneravel(bool inv){
    Invulneravel = inv;
}

void Jogador::setDevagar(bool dev){
    Devagar = dev;
}

void Jogador::tempoImunidade(float dt){
    if(Invulneravel){
        tempoInvulneravel = tempoInvulneravel-dt; // cronometro
        if(tempoInvulneravel<=0.f){
            this->setInvulneravel(false);
        }
    }
}

void Jogador:: tempoDesacelerado(float dt){
    if(Devagar){
        tempoDevagar = tempoDevagar-dt;
        if(tempoDevagar<=0.f){
            this->setDevagar(false);
        }
    }
}

void Jogador::setInvulnerabilidade( float tmp){
    this->setInvulneravel(true);
    tempoInvulneravel = tmp;
}

void Jogador::setDesaceleracao(float tmp){
    this->setDevagar(true);
    tempoDevagar=tmp;
}
}
