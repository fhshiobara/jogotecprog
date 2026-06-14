#ifndef Jogo_hpp
#define Jogo_hpp

#include "GerenciadorGrafico.hpp"
#include "Jogador.hpp"
#include "FasePrimeira.hpp"

class Jogo{
    private:
        Gerenciadores::GerenciadorGrafico* pGerenciadorGrafico;
    Gerenciadores::GerenciadorColisoes* pGC;
    Jogador* pJ1;
    Fases::FasePrimeira* pFase1;
    public:
        Jogo();
        ~Jogo();
        
        void executar();
};

#endif
