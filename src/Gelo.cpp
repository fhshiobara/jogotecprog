//
//  Obstaculo_Dificil.cpp
//  main
//
//  Created by Edison Shiobara on 16/06/26.
//

#include "Gelo.hpp"

namespace Obstaculos{

Gelo::Gelo(int temp, CoordF pos,float larg): Obstaculo(pos,false), temperatura(temp),largura(larg){
    sprite = new Gerenciadores::SingleFrameAnimation("../assets/Obstaculo/Gelo.png", pos, CoordF(largura,30), 2.0);
    
}

Gelo::~Gelo(){}

void Gelo::salvar(){}

void Gelo::desenhar(){
    if(pGG!=NULL){
        sprite->render();
    }

}

void Gelo::executar(){this->desenhar();}

bool Gelo::obstruir(CoordF& posJogador, float& velocidadeX, float& velocidadeY,
                     bool& noChao, float alturaJogador) const {

    float alturaGelo = 30.f;
    float metLarg    = largura / 2.f;
    float metAltura  = alturaJogador / 2.f;

    float centroGeloX = this->pos.x + metLarg;
    float centroGeloY = this->pos.y + alturaGelo / 2.f;

    bool colisaoX = std::abs(posJogador.x - centroGeloX) < metLarg + metAltura;
    bool colisaoY = std::abs(posJogador.y - centroGeloY) < metAltura + alturaGelo / 2.f;

    if (colisaoX && colisaoY) {
        // tremida lateral aleatória
        float tremida = (rand() % 5) - 2.f; //-2,-1,0,1,2 pixels
        posJogador.x += tremida*temperatura;

        velocidadeX = 80.f/temperatura;
        noChao = false;  //faz o boneco ter animacao de escorregar
        return true;
    }

    return false;
}
}//fim do namespace
