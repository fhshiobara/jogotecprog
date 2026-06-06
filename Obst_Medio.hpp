//
//  Obst_Medio.hpp
//  main
//
//  Created by Edison Shiobara on 06/06/26.
//

#ifndef Obst_Medio_hpp
#define Obst_Medio_hpp

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
        Obst_Medio(float vis, float larg, float alt, CoordF position);
        ~Obst_Medio();
        void executar();
        void salvar();
        bool obstruir(CoordF& posJogador, float& velocidadeY, bool& noChao, float alturaJogador);
        void desenhar();
    };
}
#endif

#endif /* Obst_Medio_hpp */
