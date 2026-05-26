#include "Ente.hpp"

Gerenciadores::GerenciadorGrafico* Ente::pGG = nullptr;

int Ente::cont_id(0);

Ente::Ente(): id(cont_id++), sprite() {
    this->setGG(Gerenciadores::GerenciadorGrafico::getInstance());
}

Ente::~Ente() {}



