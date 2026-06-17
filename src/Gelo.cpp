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

bool Gelo::obstruir(CoordF& posJogador, float& velocidadeX,float& velocidadeY,bool& noChao, float alturaJogador)const{
    float metLargObj = largura / 2.f;
    float metLargJog = 9.f;

    bool colisaoX = std::abs(posJogador.x - this->pos.x) < (metLargObj + metLargJog);
    bool colisaoY = std::abs(posJogador.y - this->pos.y) < (alturaJogador/2.f);

    if (colisaoX && colisaoY) {
        std::cout<<"Jogador escorregou no obstaculo dificil"<<std::endl;
        return true;
    }

        return false;
    }
}//fim do namespace
