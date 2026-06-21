#ifndef PERSONAGEM_hpp
#define PERSONAGEM_hpp

#include "Entidade.hpp"

namespace Personagens {

    class Personagem: public Entidades::Entidade {
        protected:
            int hp;

            float velocidade; // Velocidade atual
            float speed; // Velocidade "max"

            bool olhandoEsquerda;
            bool encostadochao;
            bool vivo;

            static const float IMUN_FRAMES_TOTAL;
            float imunidade;
            
        public:
            Personagem(CoordF position, CoordF velocidade, int hp = 1, float velocidadeInicial = 0.0f, float speed = 1.0f, bool olhandoEsquerda = false, bool encostadochao = true, bool vivo = true, float imunidade = 0);
            ~Personagem();

            void salvarDataBuffer(); // TODO

            bool getVivo() const { return vivo; }

            CoordF getPos() const { return pos; }
            void setPos(const CoordF& newPos) { pos = newPos; }
    
            CoordF getVel() const { return vel; }
            void setVel(const CoordF& v) { vel = v; }
    
            bool noChao() const { return encostadochao; }
            void setChao(bool val) { encostadochao = val; }

            virtual void executar() = 0;
            virtual void salvar() = 0;
            virtual void mover() = 0;
            virtual void morrer() = 0;

            void desenhar();
            void atualizarAnimacao(Animation_ID id, bool olhandoEsquerda, float dt);

            virtual void gravidade(float dt, float gravidade);

            void operator--(); // decrementa vida em 1
            void tomarDano();
            void tempoImunidade(float dt);
            bool estaImune() { return bool(imunidade > 0.0f); }
    };
}

#endif
