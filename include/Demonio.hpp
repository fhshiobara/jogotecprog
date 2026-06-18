#ifndef DEMONIO_HPP
#define DEMONIO_HPP

#include "Inimigo.hpp"

namespace Personagens {

    class Demonio : public Personagens::Inimigo {
        private:
            int fome; // Quanto mais fome, mais rapido
        public:
            Demonio(CoordF position, int hp = 3, float velocidade = 60.0f, int fome = 1);
            ~Demonio();

            void executar();
            void salvar();
            void mover();
            void morrer();
            void initialize();
            void danificar(Jogador* pJog);
            

            void perseguir(CoordF posJogador, float dt);
    };
}
#endif
