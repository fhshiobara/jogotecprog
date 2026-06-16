//
//  Obstaculo_Dificil.hpp
//  main
//
//  Created by Edison Shiobara on 16/06/26.
//

#ifndef Gelo_hpp
#define Gelo_hpp

#pragma once

#include "Fase.hpp"

#include "Obstaculo.hpp"

namespace Obstaculos{

class Gelo:public Obstaculo{
  
private:
    int temperatura;//quanto menor, mais escorregadio.
    
    float largura;
public:
    Gelo(int temp, CoordF pos,float larg);
    ~Gelo();

    
    bool obstruir(CoordF& posJogador, float& velocidadeX,float& velocidadeY,bool& noChao, float alturaJogador) const;
    
    void executar();
    
    void salvar();
    
    void desenhar();
    
    
    
    
    
    
    
    
    
};
}

#endif /* Obstaculo_Dificil_hpp */
