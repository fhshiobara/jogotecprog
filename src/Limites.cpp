#include "Limites.hpp"
#include "Personagem.hpp"

using namespace Personagens;

namespace Obstaculos {

    Limites::Limites(float larguraTela, float alturaTela, float alturaJogador)

        : larguraTela(larguraTela), alturaTela(alturaTela), alturaJogador(alturaJogador) {}

    Limites::~Limites() {}

    void Limites::setTela(float largura, float altura) {
        larguraTela = largura;
        alturaTela = altura;
    }

    void Limites::aplicarLimites(Personagens::Personagem* pPersonagem) const {

        if (pPersonagem == NULL) return;

        CoordF pos = pPersonagem->getPos();
        CoordF vel = pPersonagem->getVel();

        float metade = alturaJogador / 2.f;

        // Borda esquerda
        if (pos.x - metade < 0.f) {
            pos.x = metade;
            vel.x = 0.f;
        }

        // Borda direita
        if (pos.x + metade > larguraTela) {
            pos.x = larguraTela - metade;
            vel.x = 0.f;
        }

        // Borda superior
        if (pos.y - metade < 0.f) {
            pos.y = metade;
            vel.y = 0.f;
        }

        // Borda inferior
        if (pos.y + metade > alturaTela) {
            pos.y = alturaTela - metade;
            vel.y = 0.f;
            pPersonagem->setChao(true);
        }
        pPersonagem->setPos(pos);
        pPersonagem->setVel(vel);
    }

 

}

