#include "Espinhos.hpp"
#include <cmath>
 
namespace Obstaculos {
 
    Espinhos::Espinhos(CoordF position, float altura, float largura, float viscosidade)
        : Obstaculo(position, true), altura(altura), largura(largura)
    {
        hitbox.setSize(sf::Vector2f(largura, altura));
        hitbox.setPosition(sf::Vector2f(position.x, position.y));
      
        sprite = new Gerenciadores::SingleFrameAnimation("assets/Obstaculo/Espinhos.png",CoordF(position.x, position.y),CoordF(largura,altura-20.f),1.0);
    }
 
    Espinhos::~Espinhos() {}
 
void Espinhos::executar() {this->desenhar();}
 
    void Espinhos::salvar() {}
 
bool Espinhos::obstruir(CoordF& posJogador, float& velocidadeX,float& velocidadeY,
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
 
    void Espinhos::desenhar() {
        if (pGG != NULL)
            sprite->render();
    }
 
}
