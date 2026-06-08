//
//  Obst_Medio.hpp
//  main
//
//  Created by Edison Shiobara on 06/06/26.
//
#ifndef Obst_Medio_hpp
#define Obst_Medio_hpp
#pragma once
#include "Obstaculo.hpp"
 
namespace Obstaculos {
    class Obst_Medio : public Obstaculo {
    private:
        float largura;
        float altura;
        float viscosidade;
 
    public:
        Obst_Medio(CoordF position, float altura, float largura, float viscosidade);
        ~Obst_Medio();
        void executar();
        void salvar();
        bool obstruir(CoordF& posJogador, float& velocidadeX,float& velocidadeY, bool& noChao, float alturaJogador) const;
        void desenhar();
    };
}
 
#endif /* Obst_Medio_hpp */
