#ifndef Jogo_hpp
#define Jogo_hpp

#include "GerenciadorGrafico.hpp"
#include "Jogador.hpp"
#include "FasePrimeira.hpp"
#include "FaseSegunda.hpp"
#include "Menu.hpp"

class Jogo{
    private:
        Gerenciadores::GerenciadorGrafico* pGerenciadorGrafico;
        Gerenciadores::GerenciadorColisoes* pGC;

        Personagens::Jogador* pJ1;
        Personagens::Jogador* pJ2;

        Fases::FasePrimeira* pFase1;
        Fases::FaseSegunda* pFase2;
        
        Menu* pMenu;
    public:
        Jogo();
        ~Jogo();
        
        void executar();
};

#endif
