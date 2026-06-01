#include "Obstaculo.hpp"

namespace Obstaculos {

    Obstaculo::Obstaculo(CoordF position, bool danoso)
        : Entidade(position), danoso(danoso) {}

    Obstaculo::~Obstaculo() {}

}
