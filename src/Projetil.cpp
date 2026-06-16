#include "Projetil.hpp"
#include <cmath>
 
namespace Entidades {
 
    Projetil::Projetil(CoordF position, CoordF vel, float rapidez)
        : Entidade(position, CoordF(0.f, 0.f)),   // vel inicial = vetor nulo
          ativo(false), rapidez(rapidez),
          tempoVida(3.0f), tempoDecorrido(0.f)
    {
        hitbox.setSize(sf::Vector2f(16.f, 16.f));
        hitbox.setOrigin(8.f, 8.f);
        hitbox.setFillColor(sf::Color(200, 40, 200));
        hitbox.setOutlineColor(sf::Color(120, 10, 120));
        hitbox.setOutlineThickness(2.f);
        hitbox.setPosition(sf::Vector2f(position.x, position.y));
    }
 
    Projetil::~Projetil() {}
 
    void Projetil::executar() {}
    void Projetil::salvar()   {}
 
    void Projetil::atirar(CoordF origem, CoordF direcao) {
        pos = origem;
        tempoDecorrido = 0.f;
        ativo = true;
 
        // Normaliza a direção e escala pela rapidez
        float mag = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
        if (mag > 0.f) {
            vel.x = (direcao.x / mag) * rapidez;
            vel.y = (direcao.y / mag) * rapidez;
        } else {
            vel.x = 0.f;
            vel.y = 0.f;
        }
 
        hitbox.setPosition(sf::Vector2f(pos.x, pos.y));
    }
 
    void Projetil::mover(float dt) {
        if (!ativo) return;
 
        // pos += vetor velocidade * dt  — coerente com o resto do jogo
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
        hitbox.setPosition(sf::Vector2f(pos.x, pos.y));
 
        tempoDecorrido += dt;
        if (tempoDecorrido >= tempoVida)
            ativo = false;
    }
 
    void Projetil::desenhar() {
        if (ativo)
            pGG->render(&hitbox);
    }
 
    void Projetil::initialize() {}
 
}
