#ifndef PROJETIL_HPP
#define PROJETIL_HPP
 
#include "Entidade.hpp"
 
namespace Entidades {
 
    class Projetil : public Entidade {
        private:
            bool ativo;
            float rapidez;

            float tempoVida;
            float tempoDecorrido;
 
        public:
            // vel é um vetor qualquer que define a dir; normalizado e escalado por rapidez.
            Projetil(CoordF position, CoordF vel, float rapidez = 200.f);
            ~Projetil();
 
            void executar();
            void salvar();
 
            void mover(float dt);
            void desenhar();
 
            // origem = nova posição; direcao = para onde ele vai (vetor não-normalizado)
            void atirar(CoordF origem, CoordF direcao);
 
            bool estaAtivo() const { return ativo; }
            void desativar() { ativo = false; }
 
            CoordF getPos() const { return pos; }
 
            void initialize();
    };
 
}
 
#endif
