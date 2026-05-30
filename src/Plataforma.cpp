#include "Plataforma.hpp"

Plataforma::Plataforma(CoordF position, float largura, float altura)
    : Entidade(position), largura(largura), altura(altura)
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

bool Plataforma::obstruir(CoordF& posJogador, float& velocidadeY,
                           bool& noChao, float alturaJogador) const
{
    // Limites horizontais da plataforma
    bool dentroX = posJogador.x + alturaJogador > getEsquerda() &&
                   posJogador.x - alturaJogador < getDireita();

    if (!dentroX) return false;

    // Borda de topo da plataforma
    float topo = getTopo();

    // O jogador "pousa" quando o pé dele cruza o topo e está caindo
    float peJogador = posJogador.y + alturaJogador;

    if (peJogador >= topo && peJogador <= topo + altura && velocidadeY >= 0.f) {
        posJogador.y = topo - alturaJogador;
        velocidadeY  = 0.f;
        noChao       = true;
        return true;
    }

    return false;
}

void Plataforma::desenhar() {
    pGG->render(&hitbox);
}
