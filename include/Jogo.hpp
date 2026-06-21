#ifndef Jogo_hpp
#define Jogo_hpp

#include "GerenciadorGrafico.hpp"
#include "Jogador.hpp"
#include "FasePrimeira.hpp"
#include "FaseSegunda.hpp"
#include "Menu.hpp"
#include "Ranking.hpp"
#include "SingleFrameAnimation.hpp"

class Jogo{
    private:
        Gerenciadores::GerenciadorGrafico* pGerenciadorGrafico;
        Gerenciadores::GerenciadorColisoes* pGC;
        
        Personagens::Jogador* pJ1;
        Personagens::Jogador* pJ2;
        
        Fases::FasePrimeira* pFase1;
        Fases::FaseSegunda* pFase2;
        
        Menu* pMenu;

        Ranking ranking;   // armazenado em ranking.txt
        std::string nomeJ1;
        std::string nomeJ2;

    public:
        Jogo();
        ~Jogo();
        
        void executar();
        Ranking& getRanking() { return ranking; } // Jogo possui ranking. getRanking manda referencia
};

#endif
