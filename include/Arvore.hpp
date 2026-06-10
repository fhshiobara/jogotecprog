#ifndef ARVORE_HPP
#define ARVORE_HPP
 
#include "Inimigo.hpp"
#include "Obstaculo.hpp"
#include <list>
 
class Arvore : public Inimigo {
    private:
        float percepcao;
    public:
        Arvore(CoordF position, int hp = 1, float velocidade = 120.0f, float percepcao = 5000.0f);
        ~Arvore();
 
        void executar();
        void salvar();
        void mover();
        void morrer();
        void initialize();
 
        void perseguir(CoordF posJogador, float dt);
};
 
#endif
