#include "Entidade.hpp"

using namespace Entidades;

Entidade::Entidade(CoordF position, CoordF velocidade): pos(position), vel(velocidade) {}

Entidade::~Entidade() {}

void Entidade::salvarDataBuffer() {}
