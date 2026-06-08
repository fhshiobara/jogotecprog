#include "Obst_Medio.hpp"
#include <cmath>
 
namespace Obstaculos {
 
    Obst_Medio::Obst_Medio(CoordF position, float altura, float largura, float viscosidade)
        : Obstaculo(position, false), altura(altura), largura(largura), viscosidade(viscosidade)
    {
        hitbox.setSize(sf::Vector2f(largura, altura));
        hitbox.setPosition(sf::Vector2f(position.x, position.y));
        hitbox.setFillColor(sf::Color(80, 120, 60));  // verde escuro (R, G, B)
        hitbox.setOutlineColor(sf::Color(40, 80, 20));
        hitbox.setOutlineThickness(2.f);
    }
 
    Obst_Medio::~Obst_Medio() {}
 
    void Obst_Medio::executar() {}
 
    void Obst_Medio::salvar() {}
 
    bool Obst_Medio::obstruir(CoordF& posJogador, float& velocidadeY,
                               bool& noChao, float alturaJogador) const
    {
        float metLargObj = largura / 2.f;
        float metLargJog = 32.f;
 
        bool colisaoX = std::abs(posJogador.x - this->pos.x) < (metLargObj + metLargJog);
        bool colisaoY = std::abs(posJogador.y - this->pos.y) < (alturaJogador / 2.f + altura / 2.f);
 
        if (colisaoX && colisaoY) {
            float dir = posJogador.x - this->pos.x;
            posJogador.x -= dir * (1.f - viscosidade) * 0.1f;
            return true;
        }
 
        return false;
    }
 
    void Obst_Medio::desenhar() {
        if (pGG != NULL)
            pGG->render(&hitbox);
    }
 
}
