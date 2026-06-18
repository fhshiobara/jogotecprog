#include "Menu.hpp"
#include "Jogo.hpp"
#include <iostream>
 
Menu::Menu(Jogo* pJogo)
    : pJogo(pJogo), selecionada(0), multiplayer(false), ativo(true), fase(0),cavEsq(NULL),cavDir(NULL),fundo(NULL)
{
    //cavEsq = new Gerenciadores::SingleFrameAnimation("../assets/Background/cavaleiro_esquerda.png", CoordF(0.f,250.f), CoordF(280.f,300.f), 1.0);
    //cavDir = new Gerenciadores::SingleFrameAnimation("../assets/Background/cavaleiro_direita.png", CoordF(560.f,250.f), CoordF(280.f,300.f), 1.0);
    fundo = new Gerenciadores::SingleFrameAnimation("../assets/Background/plano_de_fundo.png", CoordF(0.f,0.f), CoordF(800.f,600.f), 1.0);
    opcao.push_back("Iniciar Fase 1");
    opcao.push_back("Iniciar Fase 2");
    opcao.push_back("Ver Ranking");
    opcao.push_back("Modo: 1 Jogador");
    opcao.push_back("Sair");
 
    montarTextos();
}
 
Menu::~Menu() {/*
    delete cavEsq;
    cavEsq = NULL;
    delete cavDir;
    cavDir = NULL;*/
    delete fundo;
    fundo = (NULL);
}
 
void Menu::montarTextos() {
    sf::Font* fonte = pGG->getFont();
    if (fonte == NULL) return;
 
    titulo.setFont(*fonte);
    titulo.setString("Dungeon++");
    titulo.setCharacterSize(48);
    titulo.setFillColor(sf::Color::White);
    titulo.setPosition(sf::Vector2f(280.f, 60.f));
 
    textosOpcoes.clear();
    for (size_t i = 0; i < opcao.size(); ++i) {
        sf::Text t;
        t.setFont(*fonte);
        t.setString(opcao[i]);
        t.setCharacterSize(32);
        t.setPosition(sf::Vector2f(300.f, 200.f + i * 60.f));
        textosOpcoes.push_back(t);
    }
}
 
void Menu::executar() {
    while (pGG->windowopen() && ativo) {
        sf::Event evento;

        while (pGG->getWindow()->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                pGG->closeWindow();
            processarEvento(evento);   
        }

        pGG->clear();
        fundo->render();
        desenhar();/*
        cavEsq->render();
        cavDir->render();*/
        pGG->getWindow()->display();
    }
}
 
void Menu::processarEvento(const sf::Event& evento) {
    if (evento.type != sf::Event::KeyPressed) return;
 
    // Navegacao com W e S (as setinhas do meu teclado nao funcionam)
    if (evento.key.code == sf::Keyboard::W) {
        selecionada--;
        if (selecionada < 0) 
            selecionada = opcao.size() - 1;
    }
    else if (evento.key.code == sf::Keyboard::S) {
        selecionada++;
        if (selecionada >= (int)opcao.size()) 
            selecionada = 0;
    }
    // Selecao com Enter
    else if (evento.key.code == sf::Keyboard::Return) {
        switch (selecionada) {
            case 0:
                fase = 1;
                ativo = false;
                std::cout << "Iniciando fase 1" << std::endl;
                break;
            case 1:
                fase = 2;
                ativo = false;
                std::cout << "Iniciando fase 2" << std::endl;
                break; 
            case 2:
                std::cout << "Mostrando Ranking" << std::endl;
                break;
            case 3:
                multiplayer = !multiplayer;
                if(multiplayer)
                    opcao[3] = (std::string)"Modo: 2 jogadores";
                else
                    opcao[3] = (std::string)"Modo: 1 jogador";
                montarTextos();
                break;
            case 4:
                fase = 0;
                ativo = false;
                pGG->closeWindow();
                break;
        } // Esqueleto adaptado de Sonar Systems
    }
}
 
void Menu::desenhar() {
    pGG->render(&titulo);
 
    for (int i = 0; i < textosOpcoes.size(); i++) {
        if (i == selecionada)
            textosOpcoes[i].setFillColor(sf::Color::Red);
        else
            textosOpcoes[i].setFillColor(sf::Color::White);
 
        pGG->render(&textosOpcoes[i]);
    }
}
 
