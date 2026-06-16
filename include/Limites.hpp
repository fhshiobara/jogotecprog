#ifndef LIMITES_HPP
#define LIMITES_HPP
 
#include "Jogador.hpp"

namespace Obstaculos {
 
    class Limites {
    private:
        float larguraTela;
        float alturaTela;
        float alturaJogador;
 
    public:
        Limites(float larguraTela = 800.f, float alturaTela = 600.f, float alturaJogador = 64.f);
        ~Limites();
 
        void aplicarLimites(Personagens::Jogador* pJog) const;
 
        void setTela(float largura, float altura);
    };
}
 
#endif
