#include "Ente.hpp"

Gerenciadores::GerenciadorGrafico* Ente::pGG = nullptr;

Ente::Ente(int id): id(id), sprite() {
    this->setGG(Gerenciadores::GerenciadorGrafico::getInstance());
}

Ente::~Ente() {}

void Ente::desenhar() {
    
    // pGG->render(&sprite);
    
}