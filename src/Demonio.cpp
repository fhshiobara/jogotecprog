#include "Demonio.hpp"
#include <cmath>

namespace Personagens {

    Demonio::Demonio(CoordF position, int hp, float velocidade, int fome, int valorPontos)
    : Inimigo(position, hp, velocidade, valorPontos), fome(fome)
    {this->initialize();}

    Demonio::~Demonio() {}

    void Demonio::perseguir(CoordF posJogador, float dt) {

        this->dt_local = dt;
        float dx = posJogador.x - this->pos.x;
        float dy = posJogador.y - this->pos.y;
        float distancia = sqrt(dx * dx + dy * dy);
    
        vel.x = (dx / distancia) * velocidade * fome;
        vel.y = (dy / distancia) * velocidade * fome;

        olhandoEsquerda = (dx > 0);
    }



    void Demonio::initialize() {
        this->sprite.addNewAnimation(Animation_ID::idle, "../assets/Demonio/IDLE.png", 4);
        this->sprite.addNewAnimation(Animation_ID::walk, "../assets/Demonio/FLYING.png", 4);
        this->sprite.addNewAnimation(Animation_ID::hurt, "../assets/Demonio/HURT.png", 4);
        // Mudar path caso falha ao encontrar.

    }

    void Demonio::executar() {
        this->atualizarAnimacao(Animation_ID::idle, olhandoEsquerda, dt_local);
        this->desenhar();
    }

    void Demonio::salvar() {}

    void Demonio::mover() {}

    void Demonio::morrer() {
        vivo = false;
        std::cout << "Demonio morreu!" << std::endl;
    }

    void Demonio::gravidade(float dt, float gravidade) {
        vel.y += gravidade * dt;
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;

    }
    void Demonio::operator++(){
        fome++;
    }

    void Demonio::danificar(Jogador* pJog){
        //essa funcao so sera chamada caso haja o contato entre o jogador e o inimigo, entao vou abstrair essa parte de verificacao
        if(pJog!=NULL){
            if(!pJog->getInvulneravel()){
                pJog->setInvulnerabilidade(0.9); //o dano é causado em outra funcao, entao posso setar como imune logo que entrou nesse if para evitar que o jogador saia voando
                
                if(olhandoEsquerda){
                    pJog->setPos(CoordF(pJog->getPos().x+60,pJog->getPos().y-30)); // pulinho para tras
                    this->operator++();
                }
                else{
                    pJog->setPos(CoordF(pJog->getPos().x-60,pJog->getPos().y-30)); // pulinho para frente
                    this->operator++();
                    
                    
                }
            }
            
            
        }else{
            std::cerr<<"ERRO:ponteiro nulo em danificar de demonio"<<std::endl;
        }
    
    }

}

