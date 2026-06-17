#include "Ente.hpp"
#include <iostream>

Gerenciadores::GerenciadorGrafico* Ente::pGG = nullptr;

int Ente::cont_id(0);

Ente::Ente(): id(cont_id++), sprite() {
    this->setGG(Gerenciadores::GerenciadorGrafico::getInstance());
}

Ente::~Ente() {}

void Ente::desenhar(){
    sprite.render();
}

// void Ente::desenharHitbox() {
//     std::cout << "Desnhando hitbox (debug)" << std::endl;
//     sf::RectangleShape debug = hitbox;

//     debug.setFillColor(sf::Color::Transparent);
//     debug.setOutlineThickness(2.f);
//     debug.setOutlineColor(sf::Color::Red);

//     pGG->getWindow()->draw(debug);
// }

