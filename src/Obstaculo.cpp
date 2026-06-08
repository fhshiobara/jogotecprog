#include "Obstaculo.hpp"

namespace Obstaculos {

    Obstaculo::Obstaculo(CoordF position, bool danoso)
        : Entidade(position, CoordF(0.f, 0.f)), danoso(danoso) {}

    Obstaculo::~Obstaculo() {}

}
