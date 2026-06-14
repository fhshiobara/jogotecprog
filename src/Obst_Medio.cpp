#include "Obst_Medio.hpp"
#include <cmath>
 
namespace Obstaculos {
 
    Obst_Medio::Obst_Medio(CoordF position, float altura, float largura, float viscosidade)
        : Obstaculo(position, true), altura(altura), largura(largura), viscosidade(viscosidade)
    {
        hitbox.setSize(sf::Vector2f(largura, altura));
        hitbox.setPosition(sf::Vector2f(position.x, position.y));
      
        sprite = new Gerenciadores::SingleFrameAnimation("../assets/Obstaculo/Espinhos.png",CoordF(position.x, position.y),CoordF(largura,altura-20.f),1.0);
    }
 
    Obst_Medio::~Obst_Medio() {}
 
void Obst_Medio::executar() {this->desenhar();}
 
    void Obst_Medio::salvar() {}
 
bool Obst_Medio::obstruir(CoordF& posJogador, float& velocidadeX,float& velocidadeY,
                               bool& noChao, float alturaJogador) const
    {
        float metLargObj = largura / 2.f;
        float metLargJog = 9.f;
 
        bool colisaoX = std::abs(posJogador.x - this->pos.x) < (metLargObj + metLargJog);
        bool colisaoY = std::abs(posJogador.y - this->pos.y) < (alturaJogador / 2.f + altura / 2.f);
 
        if (colisaoX && colisaoY) {
            std::cout<<"Jogador levou dano do obstaculo medio"<<std::endl;
            return true;
        }
 
        return false;
    }
 
    void Obst_Medio::desenhar() {
        if (pGG != NULL)
            sprite->render();
    }
 
}
