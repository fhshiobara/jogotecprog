#include "Morte.hpp"
#include <cmath>
 
namespace Personagens {
    
    Morte::Morte(CoordF position, int hp, float velocidade, int morte)
        : Inimigo(position, hp, velocidade),
        tempoRecarga(2.0f), tempoDeVidaProjetil(0.0f),
        projetil(new Entidades::Projetil(position, CoordF(0.f, 0.f), 250.f)) {}
    
    Morte::~Morte() {
        delete projetil;
    }
    
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
    }
    
    void Morte::iniciarAtirar(CoordF posJogador, float dt) {
        if (projetil->estaAtivo()) return;
    
        tempoDeVidaProjetil += dt;
    
        if (tempoDeVidaProjetil >= tempoRecarga) {
            CoordF direcao;
            direcao.x = posJogador.x - this->pos.x;
            direcao.y = posJogador.y - this->pos.y;
    
            projetil->atirar(this->pos, direcao);
            tempoDeVidaProjetil = 0.f;
        }
    }

    
    void Morte::atualizarProjetil(float dt) {
        projetil->mover(dt);
    }
    
    void Morte::desenharProjetil() {
        projetil->desenhar();
    }
    
    void Morte::initialize() {
        this->sprite.addNewAnimation(Animation_ID::walk, "assets/Morte/FLYING.png", 5);
    }
    
    void Morte::executar() {}
    void Morte::salvar()   {}
    void Morte::mover()    {}
    
    void Morte::morrer() {
        vivo = false;
        std::cout << "Morte morreu!" << std::endl;
    }
}
