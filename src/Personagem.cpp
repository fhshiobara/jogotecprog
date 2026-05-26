#include "Personagem.hpp"

Personagem::Personagem(CoordF position, int hp) : Entidade(position), Hp(hp) {}

Personagem::~Personagem() {}

void Personagem::salvarDataBuffer() {}
