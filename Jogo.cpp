#include "Jogo.hpp"
#include <iostream>

Jogo::Jogo():pGerenciadorGrafico(Gerenciadores::GerenciadorGrafico::getInstance()){ executar(); }

Jogo::~Jogo(){}

void Jogo::executar() {

    Gerenciadores::GerenciadorGrafico* pGrafico = Gerenciadores::GerenciadorGrafico::getInstance();

    while (pGrafico->windowopen()) {
        
        sf::Event evento;

        while (pGrafico->getWindow()->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                pGrafico->closeWindow();
            }
        }
        
        
        
        pGrafico->clear();
        //os comandos de desenho devem estar aqui
        
        
        pGrafico->display();
    }

}

