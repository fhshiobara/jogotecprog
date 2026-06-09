#include "Personagem.hpp"
 
Personagem::Personagem(CoordF position, CoordF velocidade, int hp,
                       float velocidadeInicial, float speed, bool olhandoEsquerda,
                       bool encostadochao, bool vivo)
    : Entidade(position, velocidade), Hp(hp), velocidade(velocidadeInicial), speed(speed),
      olhandoEsquerda(olhandoEsquerda), encostadochao(encostadochao), vivo(vivo) {}
 
Personagem::~Personagem() {}
 
void Personagem::salvarDataBuffer() {}
