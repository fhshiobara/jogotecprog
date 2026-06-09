#include "Inimigo.hpp"
#include <cmath>
 
Inimigo::Inimigo(CoordF position, int hp, float velocidadeInicial)
    : Personagem(position, CoordF(0.f, 0.f), hp, velocidadeInicial, false, true, true),
      dt_local(0.0f) {}
 
Inimigo::~Inimigo() {}
 
void Inimigo::executar() {}
void Inimigo::morrer() {}
void Inimigo::salvar() {}
void Inimigo::mover() {}

