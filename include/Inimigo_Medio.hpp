#include "Inimigo.hpp"

class Demonio : public Inimigo {
    public:
        Demonio(CoordF position, int hp = 3, float velocidade = 60.0f);
        ~Demonio();

        void executar();
        void salvar();
        void mover();
        void morrer();
        void initialize();

        void perseguir(CoordF posJogador, float dt);
};
