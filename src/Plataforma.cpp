#include "Plataforma.hpp"

Plataforma::Plataforma(CoordF position, float largura, float altura)
    : Obstaculo(position, false), largura(largura), altura(altura)
{
    hitbox.setSize(sf::Vector2f(largura, altura));
    hitbox.setPosition(sf::Vector2f(position.x, position.y));
    
    // Para deixar bonito...

    hitbox.setFillColor(sf::Color(100, 60, 20));      
    hitbox.setOutlineColor(sf::Color(60, 30, 10));
    hitbox.setOutlineThickness(2.f);
}

Plataforma::~Plataforma() {}

void Plataforma::executar() {}
void Plataforma::salvar()   {}

bool Plataforma::obstruir(CoordF& pos, float& velocidadeY,float& velocidadeX,
                           bool& noChao, float altura) const {

    float metade = altura / 1.6f; // Dividido para compensar a escala... Resolver depois

    // Limites horizontais — usa metade da altura como aproximação da meia largura
    bool dentroX = pos.x + metade > getEsquerda() &&
                   pos.x - metade < getDireita();

    if (!dentroX) return false;

    float topo = getTopo();

    // Pé do jogador está metade abaixo do centro (origin = centro)
    float peJogador = pos.y + metade;

    if (peJogador >= topo && peJogador <= topo + altura && velocidadeY >= 0.f) {
        pos.y = topo - metade;  // encosta o pé no topo
        velocidadeY = 0.f;

        noChao = true;
        return true;
    }

    return false;
}

void Plataforma::desenhar() {
    pGG->render(&hitbox);
}
