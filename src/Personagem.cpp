#include "Personagem.hpp"

namespace Personagens {
  const float Personagem::IFRAMES_TOTAL = 1.0f; // Define duracao da imunidade
  
  Personagem::Personagem(CoordF position, CoordF velocidade, int hp,
                        float velocidadeInicial, float speed, bool olhandoEsquerda,
                        bool encostadochao, bool vivo)
      : Entidade(position, velocidade), Hp(hp), velocidade(velocidadeInicial), speed(speed),
        olhandoEsquerda(olhandoEsquerda), encostadochao(encostadochao), vivo(vivo) {}
  
  Personagem::~Personagem() {}
  
  void Personagem::salvarDataBuffer() {}

  void Personagem::atualizarAnimacao(Animation_ID id, bool olhandoEsquerda, float dt) {
    this->sprite.update(id, olhandoEsquerda, this->pos, dt);
  }
  
  void Personagem::desenhar() {
    this->sprite.render();
  }

  void Personagem::tomarDano() {
      if (imunidade <= 0.0f) {
        Hp--;
        imunidade = IFRAMES_TOTAL;

        std::cout << "Personagem tomou dano! HP restante: " << Hp << std::endl;

        if (Hp <= 0) {
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