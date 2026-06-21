#include "Menu.hpp"
#include "Jogo.hpp"
#include "Ranking.hpp"
#include <iostream>
 
Menu::Menu(Jogo* pJogo)
    : pJogo(pJogo), selecionada(0), multiplayer(false), ativo(true), fase(0),cavEsq(NULL),cavDir(NULL),fundo(NULL)
{
    cavEsq = new SingleFrameAnimation("../assets/Background/cavaleiro_esquerda.png", CoordF(0.f,250.f), CoordF(280.f,300.f), 1.0);
    cavDir = new SingleFrameAnimation("../assets/Background/cavaleiro_direita.png", CoordF(560.f,250.f), CoordF(280.f,300.f), 1.0);
    fundo = new SingleFrameAnimation("../assets/Background/plano_de_fundo.png", CoordF(0.f,0.f), CoordF(800.f,600.f), 1.0);
    opcao.push_back("Iniciar Fase 1");
    opcao.push_back("Iniciar Fase 2");
    opcao.push_back("Ver Ranking");
    opcao.push_back("Modo: 1 Jogador");
    opcao.push_back("Sair");
 
    montarTextos();
}
 
Menu::~Menu() {
    delete cavEsq;
    cavEsq = NULL;
    delete cavDir;
    cavDir = NULL;
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
        desenhar();
        cavEsq->render();
        cavDir->render();
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
                mostrarRanking(pJogo->getRanking());
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

std::string Menu::pedirNome(const std::string& titulo) {
    sf::Font* fonte = pGG->getFont();
    std::string nome = "";
 
    sf::Text textoTitulo;
    sf::Text textoNome;
    if (fonte != NULL) {
        textoTitulo.setFont(*fonte);
        textoTitulo.setString(titulo);
        textoTitulo.setCharacterSize(36);
        textoTitulo.setFillColor(sf::Color::White);
        textoTitulo.setPosition(sf::Vector2f(150.f, 200.f));
 
        textoNome.setFont(*fonte);
        textoNome.setCharacterSize(40);
        textoNome.setFillColor(sf::Color::Yellow);
        textoNome.setPosition(sf::Vector2f(150.f, 280.f));
    }
 
    while (pGG->windowopen()) {
        sf::Event evento;

        while (pGG->getWindow()->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                pGG->closeWindow();
                return nome;
            }
 
            if (evento.type == sf::Event::TextEntered) {
                if (evento.text.unicode == 8) {            // Backspace
                    if (!nome.empty()) nome.pop_back();
                }
                else if (evento.text.unicode == 13) {       // Enter
                    if (nome.empty()) nome = "JogadorDesconhecido";
                    return nome;
                }
                else if (evento.text.unicode >= 32 && evento.text.unicode < 127) {
                    if (nome.size() < 12)                    // limite de tamanho
                        nome += static_cast<char>(evento.text.unicode);
                }
            }
        }
 
        textoNome.setString(nome + "_");
 
        pGG->clear();
        pGG->render(&textoTitulo);
        pGG->render(&textoNome);
        pGG->getWindow()->display();
    }
 
    return nome;
}
 
// Mostra o ranking ordenado ate o jogador sair (Esc).
void Menu::mostrarRanking(Ranking& ranking) {

    sf::Font* fonte = pGG->getFont();
    ranking.ler();
 
    sf::Text textoTitulo;
    if (fonte != NULL) {
        textoTitulo.setFont(*fonte);
        textoTitulo.setString("RANKING (Esc para voltar)");
        textoTitulo.setCharacterSize(32);
        textoTitulo.setFillColor(sf::Color::White);
        textoTitulo.setPosition(sf::Vector2f(120.f, 40.f));
    }
 
    std::vector<sf::Text> linhas;
    const std::vector<Pontuacao>& ents = ranking.getTabela();

    for (int i = 0; i < ents.size() && i < 10; ++i) { // 10 linhas de ranking limite. i < ents.size() foi adicionado pelo claude para arrumar bug.

        sf::Text linha; 

        if (fonte != NULL) {
            linha.setFont(*fonte);
            linha.setString(std::to_string(i + 1) + ". " 
                                    + ents[i].nomeJogador + " - " 
                                    + std::to_string(ents[i].pontosFinais)); // Feito pelo Claude. Deixa o placar mais organizado
            linha.setCharacterSize(26);
            linha.setFillColor(sf::Color::White);
            linha.setPosition(sf::Vector2f(150.f, 120.f + i * 40.f));
        }

        linhas.push_back(linha);
    }
 
    while (pGG->windowopen()) {
        sf::Event evento;
        while (pGG->getWindow()->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                pGG->closeWindow();
                return;
            }
            if (evento.type == sf::Event::KeyPressed &&
               (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Escape)) {
                return;
            }
        }
 
        pGG->clear();

        pGG->render(&textoTitulo);
        for (int i = 0; i < linhas.size(); ++i)
            pGG->render(&linhas[i]);

        pGG->getWindow()->display();
    }
}

 
