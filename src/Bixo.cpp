#include "Bixo.hpp"
#include <cmath>

namespace Personagens {
 
    Bixo::Bixo(CoordF position, int hp, float velocidade, float percepcao)
    : Inimigo(position, hp, velocidade), percepcao(percepcao) {this->initialize();}
    
    Bixo::~Bixo() {}
    
    // void Bixo::executar(CoordF posJogador1, CoordF posJogador2, float dt) {
    //     this->atualizarAnimacao(Animation_ID::idle,olhandoEsquerda,dt_local);
    //     bool jogadorMaisProx = this->jogadorProximo(posJogador1, posJogador2);
    //     if(jogadorMaisProx) // False = jog1, True = jog2
    //         this->perseguir(posJogador2, dt);
    //     else    
    //         this->perseguir(posJogador1, dt);
    //     this->desenhar();
    // }

    void Bixo::executar() {
        this->atualizarAnimacao(Animation_ID::idle, olhandoEsquerda, dt_local);
        this->desenhar();
    }
    void Bixo::salvar() {}
    void Bixo::mover() {}
    void Bixo::morrer() {
        vivo = false;
        std::cout << "Bixo morreu!" << std::endl;
    }
    
    void Bixo::perseguir(CoordF posJogador, float dt) {
        this->dt_local = dt;
    
        float dx = posJogador.x - this->pos.x;
        float dy = posJogador.y - this->pos.y;
    
        float distancia = std::sqrt(dx * dx + dy * dy);

        if (distancia > percepcao) return; // Aqui definimos a dist. para o Bixo perseguir
    
        // Só se move no eixo X
        if (distancia > 5.0f) {
            float direcaoX = dx / distancia;
            this->pos.x += direcaoX * velocidade * dt;
            olhandoEsquerda = (dx > 0);
        }
    }

    void Bixo::initialize() {
        this->sprite.addNewAnimation(Animation_ID::idle, "../assets/Bixo/ATTACK.png", 8);
        this->sprite.addNewAnimation(Animation_ID::walk, "../assets/Bixo/WALK.png", 8);
    }
    void Bixo::danificar(Jogador* pJog){}
}//fim do namespace


