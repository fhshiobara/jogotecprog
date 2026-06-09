#include "Limites.hpp"
 
namespace Obstaculos {
 
    Limites::Limites(float larguraTela, float alturaTela, float alturaJogador)
        : larguraTela(larguraTela), alturaTela(alturaTela), alturaJogador(alturaJogador) {}
 
    Limites::~Limites() {}
 
    void Limites::setTela(float largura, float altura) {
        larguraTela = largura;
        alturaTela = altura;
    }
 
    void Limites::aplicarLimites(Jogador* pJog) const {
        if (pJog == NULL) return;
 
        CoordF pos = pJog->getPos();
        CoordF vel = pJog->getVel();
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

            pJog->setChao(true);
        }
 
        pJog->setPos(pos);
        pJog->setVel(vel);
    }
 
}
