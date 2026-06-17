#include "Inimigo.hpp"
#include <cmath>
 
namespace Personagens {
  Inimigo::Inimigo(CoordF position, int hp, float velocidadeInicial)
      : Personagem(position, CoordF(0.f, 0.f), hp, velocidadeInicial, false, true, true),
        dt_local(0.0f) {}
  
  Inimigo::~Inimigo() {}

  bool Inimigo::jogadorProximo(CoordF posPlayer1, CoordF posPlayer2) {
      CoordF posInimigo = this->getPos();

      float dist1 =
          (posInimigo.x - posPlayer1.x) * (posInimigo.x - posPlayer1.x) +
          (posInimigo.y - posPlayer1.y) * (posInimigo.y - posPlayer1.y);

      float dist2 =
          (posInimigo.x - posPlayer2.x) * (posInimigo.x - posPlayer2.x) +
          (posInimigo.y - posPlayer2.y) * (posInimigo.y - posPlayer2.y);

      return dist2 < dist1;
  } // Ideia sem utilizar  sqrt() provem do StackOverflow

  void Inimigo::setDt(float dt){dt_local = dt;}
}
