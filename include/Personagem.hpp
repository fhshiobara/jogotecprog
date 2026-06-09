#ifndef Personagem_hpp
#define Personagem_hpp

#include "Entidade.hpp"

class Personagem: public Entidades::Entidade {
    protected:
        int Hp;

        float velocidade; // Velocidade atual
        float speed; // Velocidade "max"

        bool olhandoEsquerda;
        bool encostadochao;
        bool vivo;
        
    public:
        Personagem(CoordF position, CoordF velocidade, int hp = 1, float velocidadeInicial = 0.0f, float speed = 1.0f, bool olhandoEsquerda = false, bool encostadochao = true, bool vivo = true);
        ~Personagem();

        void salvarDataBuffer(); // TODO

        bool estaVivo() const { return vivo; }

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

        virtual void gravidade(float dt, float gravidade) = 0;

};

#endif
