#include "Morte.hpp"
#include <cmath>
 
namespace Personagens {
    
    Morte::Morte(CoordF position, int hp, float velocidade, int valorPontos)
        : Inimigo(position, hp, velocidade, valorPontos),
        tempoRecarga(2.0f), tempoDeVidaProjetil(0.0f),
        projetil(new Entidades::Projetil(position, CoordF(0.f, 0.f), 250.f)) {this->initialize();}
    
    Morte::~Morte() {
        delete projetil;
    }
    
    void Morte::perseguir(CoordF posJogador, float dt) {
        this->dt_local = dt;

        float dx = posJogador.x - this->pos.x;
        float dy = posJogador.y - this->pos.y;
        float distancia = std::sqrt(dx * dx + dy * dy);

        float distanciaSegura = 200.f; 
        float margem = 30.f; //deadzone, sem isso o morte fica tremendo



        if (distancia > 1.0f) {
            float dirX = dx / distancia;
            float dirY = dy / distancia;

            if (distancia > distanciaSegura + margem) {

                vel.x = dirX * velocidade;
                vel.y = dirY * velocidade;
                olhandoEsquerda = (dx > 0);

            } else if (distancia < distanciaSegura - margem) {
                // perto demais: recua 
                vel.x = -dirX * velocidade;
                vel.y = -dirY * velocidade;
                olhandoEsquerda = (dx > 0);

            } else {
                // na distancia ideal: fica parado atirando
                vel.x = 0.f;
                vel.y = 0.f;
            }
        }

        this->iniciarAtirar(posJogador, dt);

    }



    void Morte::gravidade(float dt, float gravidade) {
        gravidade = gravidade / 4; // Flutua, grav mais fraca

        vel.y += gravidade * dt;

        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
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
        this->sprite.addNewAnimation(Animation_ID::walk, "../assets/Morte/IDLE.png", 8);
    }
    
    void Morte::executar() {
        this->atualizarAnimacao(Animation_ID::walk,!olhandoEsquerda,dt_local);
        this->desenhar();
    }
    
    void Morte::salvar()   {}
    void Morte::mover()    {}
    void Morte::morrer() {
        vivo = false;
        std::cout << "Morte morreu!" << std::endl;
    }

    void Morte::danificar(Jogador* pJog) {}
}
