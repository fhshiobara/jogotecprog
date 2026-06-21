#ifndef OBSTACULO_HPP
#define OBSTACULO_HPP

#include "Entidade.hpp"
#include "SingleFrameAnimation.hpp"

class Jogador;

namespace Obstaculos {

    class Obstaculo : public Entidades::Entidade {
        protected:
            bool danoso;
            SingleFrameAnimation* sprite;

        public:
            Obstaculo(CoordF position, bool danoso = false);
            virtual ~Obstaculo();

            bool isDanoso() const { return danoso; }

            virtual void executar() = 0;
            virtual void salvar() = 0;
            virtual bool obstruir(CoordF& posJogador, float& velocidadeX,float& velocidadeY,bool& noChao, float alturaJogador) const = 0;
            virtual void desenhar() = 0; 
    };

}

#endif
