//
//  Obst_Medio.cpp
//  main
//
//  Created by Edison Shiobara on 06/06/26.
//

#include "Obst_Medio.hpp"
#include "Obst_Medio.hpp"
#include <cmath>

namespace Obstaculos {
    Obst_Medio::Obst_Medio(float vis, float larg, float alt, CoordF position)
        : Obstaculo(position, false), viscosidade(vis), largura(larg), altura(alt) {
            
            
        hitbox.setSize(sf::Vector2f(largura, altura));
        hitbox.setFillColor(sf::Color::Green); //nao sei colocar a cor marrom
        hitbox.setPosition(sf::Vector2f(position.x, position.y));
    }

    Obst_Medio::~Obst_Medio() {}

    bool Obst_Medio::obstruir(CoordF& posJogador, float& velocidadeY, bool& noChao, float alturaJogador) {
        float metLargObj = largura / 2.0; //metade da largura do objeto
        float metLargJog = 32.0f;//metade da largura do jogador 

        bool ColisaoEmX = std::abs(posJogador.x - this->pos.x) < (metLargObj + metLargJog);
        bool ColisaoEmY = std::abs(posJogador.y - this->pos.y) < (alturaJogador / 2.0 + altura / 2.0);

        if (ColisaoEmX && ColisaoEmY) {
            float dir = posJogador.x - this->pos.x;
            posJogador.x = posJogador.x - (dir * (1.0 - viscosidade) * 0.1f);
            return true;
        }
        return false;
    }

    void Obst_Medio::desenhar() {
        if (pGG != NULL) {
            pGG->render(&hitbox);
        }
    }

    void Obst_Medio::executar() { // nao precisa atualizar quando o loop renova
        
    }
}
