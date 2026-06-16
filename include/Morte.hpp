#ifndef MORTE_HPP
#define MORTE_HPP

#include "Inimigo.hpp"
#include "Projetil.hpp"

namespace Personagens {

    class Morte : public Personagens::Inimigo {
        private:
            float tempoRecarga;     // segundos entre disparos
            float tempoDeVidaProjetil;
            Entidades::Projetil* projetil;  // Um projetil somente. Reutilizada apos expirar
        public:
            Morte(CoordF position, int hp = 5, float velocidade = 10.0f);
            ~Morte();
    
            void executar();
            void salvar();
            void mover();
            void morrer();
            void initialize();
    
            void perseguir(CoordF posJogador, float dt);
            void iniciarAtirar(CoordF posJogador, float dt);
            void atualizarProjetil(float dt);
            void desenharProjetil();

            Entidades::Projetil* getProjetil() { return projetil; }
    };
}


#endif