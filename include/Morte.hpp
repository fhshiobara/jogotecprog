#ifndef MORTE_HPP
#define MORTE_HPP

#include "Inimigo.hpp"

class Morte : public Inimigo {
    private:
        int matar; // Ainda nao sei... 
    public:
        Morte(CoordF position, int hp = 5, float velocidade = 10.0f, int morte = 1);
        ~Morte();

        void executar();
        void salvar();
        void mover();
        void morrer();
        void initialize();

        void perseguir(CoordF posJogador, float dt);
        void atirar(); // TODO
};

#endif