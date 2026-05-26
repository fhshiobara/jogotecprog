#include "Jogo.hpp"
#include "Jogador.hpp"
#include <iostream>
 
Jogo::Jogo() : pGerenciadorGrafico(Gerenciadores::GerenciadorGrafico::getInstance()) { executar(); }
 
Jogo::~Jogo() {}
 
void Jogo::executar() {
 
    Gerenciadores::GerenciadorGrafico* pGrafico = Gerenciadores::GerenciadorGrafico::getInstance();
    Jogador jogador(100.0f, 100.0f);
 
    while (pGrafico->windowopen()) {
 
        sf::Event evento;

        while (pGrafico->getWindow()->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                pGrafico->closeWindow();
            }
        }
 
        std::cout << "Executando jogo..." << std::endl;
        
        pGrafico->clear();
        pGrafico->render(jogador.getSprite());
        pGrafico->display();

    }
}


