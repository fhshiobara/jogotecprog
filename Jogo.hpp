#ifndef Jogo_hpp
#define Jogo_hpp

#include "GerenciadorGrafico.hpp"

class Jogo{
    private:
        Gerenciadores::GerenciadorGrafico* pGerenciadorGrafico;
    public:
        Jogo();
        ~Jogo();
        
        void executar();
};

#endif
