#include "Personagem.hpp"

namespace Personagens {
  const float Personagem::IMUN_FRAMES_TOTAL = 1.0f; // Define duracao da imunidade
  
  Personagem::Personagem(CoordF position, CoordF velocidade, int hp,
                        float velocidadeInicial, float speed, bool olhandoEsquerda,
                        bool encostadochao, bool vivo)
      : Entidade(position, velocidade), hp(hp), velocidade(velocidadeInicial), speed(speed),
        olhandoEsquerda(olhandoEsquerda), encostadochao(encostadochao), vivo(vivo) {}
  
  Personagem::~Personagem() {}
  
  void Personagem::salvarDataBuffer() {}

  void Personagem::atualizarAnimacao(Animation_ID id, bool olhandoEsquerda, float dt) {
    this->sprite.update(id, olhandoEsquerda, this->pos, dt);
  }
  
  void Personagem::desenhar() {
    this->sprite.render();
  }

  Personagem& Personagem::operator--() {
    hp--;

    return *this;
  }



  void Personagem::tomarDano() {
      if (imunidade <= 0.0f) {
        --(*this);
        imunidade = IMUN_FRAMES_TOTAL;

        std::cout << "Personagem " << this << " tomou dano! HP restante: " << hp << std::endl;

        if (hp <= 0) {
            morrer();
        }
    }
  }

  void Personagem::tempoImunidade(float dt) {
      if (imunidade > 0.0f) {
          imunidade -= dt;
      }
  }

  void Personagem::gravidade(float dt, float gravidade) {
      vel.y += gravidade * dt;
      pos.y += vel.y * dt;
      encostadochao = false;
  }
}