#include "Personagem.hpp"
 
Personagem::Personagem(CoordF position, CoordF velocidade, int hp,
                       float velocidadeInicial, bool olhandoEsquerda,
                       bool encostadochao, bool vivo)
    : Entidade(position, velocidade), Hp(hp), velocidade(velocidadeInicial),
      olhandoEsquerda(olhandoEsquerda), encostadochao(encostadochao), vivo(vivo) {}
 
Personagem::~Personagem() {}
 
void Personagem::salvarDataBuffer() {}
