//
//  Espinhos.hpp
//  main
//
//  Created by Edison Shiobara on 06/06/26.
//
#ifndef Espinhos_hpp
#define Espinhos_hpp
#include "Obstaculo.hpp"
 
namespace Obstaculos {
    class Espinhos : public Obstaculo {
    private:
        float largura;
        float altura;
 
    public:
        Espinhos(CoordF position, float altura, float largura, float viscosidade);
        ~Espinhos();
        void executar();
        void salvar();
        bool obstruir(CoordF& posJogador, float& velocidadeX,float& velocidadeY, bool& noChao, float alturaJogador) const;
        void desenhar();
    };
}
 
#endif /* Espinhos_hpp */
