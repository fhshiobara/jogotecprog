#include "Inimigo.hpp"

class Goblin : public Inimigo {
    private:
        float percepcao; // Distância de detecção do jogador
    public:
        Goblin(CoordF position, int hp = 1, float velocidade = 120.0f, float percepcao = 10000.0f);
        ~Goblin();

        void executar();
        void salvar();
        void mover();
        void morrer();

        void initialize();

        void perseguir(CoordF posJogador, float dt); 
};