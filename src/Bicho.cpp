#include "Bicho.hpp"
#include <cmath>

namespace Personagens {
 
    Bicho::Bicho(CoordF position, int hp, float velocidade, float percepcao, int valorPontos)
    : Inimigo(position, hp, velocidade, valorPontos), percepcao(percepcao)
    {this->initialize();}
    
    Bicho::~Bicho() {}
    
    
    void Bicho::executar() {
        this->atualizarAnimacao(Animation_ID::idle, olhandoEsquerda, dt_local);
        this->desenhar();
    }

    void Bicho::salvar() {}
    void Bicho::mover() {}
    void Bicho::morrer() {
        vivo = false;
        std::cout << "Bicho morreu!" << std::endl;
    }
    
    void Bicho::perseguir(CoordF posJogador, float dt) {

        this->dt_local = dt;
    
        float dx = posJogador.x - this->pos.x;
        float dy = posJogador.y - this->pos.y;
    
        float distancia = std::sqrt(dx * dx + dy * dy);

        if (distancia > percepcao) return; // Aqui definimos a dist. para o Bicho perseguir
    
        // Só se move no eixo X
        if (distancia > 5.0f) {
            float direcaoX = dx / distancia;
            this->pos.x += direcaoX * velocidade * dt;
            olhandoEsquerda = (dx > 0);
        }
    }

    void Bicho::initialize() {
        this->sprite.addNewAnimation(Animation_ID::idle, "../assets/Bicho/ATTACK.png", 8);
        this->sprite.addNewAnimation(Animation_ID::walk, "../assets/Bicho/WALK.png", 8);
    }

    void Bicho::danificar(Jogador* pJog){
        if(pJog!=NULL){//mesmo caso do demonio, essa funcao so é chamada se o contato já ocorreu,
            pJog->setInvulnerabilidade(0.9); // impede que entre em um loop infinito
            pJog->setDesaceleracao(1.8);
        }
    }
}//fim do namespace


