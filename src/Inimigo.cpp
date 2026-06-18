#include "Inimigo.hpp"
#include <cmath>
 
namespace Personagens {
  Inimigo::Inimigo(CoordF position, int hp, float velocidadeInicial, Jogador* pJogador1, Jogador* pJogador2)
      : Personagem(position, CoordF(0.f, 0.f), hp, velocidadeInicial, 
      false, true, true), dt_local(0.0f) {}
  
  Inimigo::~Inimigo() {}

  bool Inimigo::jogadorProximo(Jogador* pJ1, Jogador* pJ2) {
    if(pJ2 == NULL) return false;


      CoordF posInimigo = this->getPos();
      CoordF posPlayer1 = pJ1->getPos();
      CoordF posPlayer2 = pJ2->getPos();

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
