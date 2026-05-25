#include "Personagem.hpp"

Personagem::Personagem(float Xinicial, float inicialY, int hp) : Entidade(Xinicial, inicialY), Hp(hp) {}

Personagem::~Personagem() {}

void Personagem::salvarDataBuffer() {}
