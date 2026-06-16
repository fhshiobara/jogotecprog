#ifndef MENU_HPP
#define MENU_HPP

#include "Ente.hpp"
#include "Jogo.hpp"

class Menu : public Ente {
    private:
        Jogo* pJogo; 
    public:
        Menu();
        ~Menu();
        void executar();

};

#endif