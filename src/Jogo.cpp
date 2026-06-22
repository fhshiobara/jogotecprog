#include "Jogo.hpp"
#include "Menu.hpp"
#include "Demonio.hpp"
#include "Bicho.hpp"
#include "Morte.hpp"
#include "Plataforma.hpp"
#include "GerenciadorColisoes.hpp"
#include "Espinhos.hpp"
#include "SingleFrameAnimation.hpp"

using namespace Obstaculos;
using namespace Personagens;
 
Jogo::Jogo() : pGerenciadorGrafico(Gerenciadores::GerenciadorGrafico::getInstance()),pJ1(NULL),pJ2(NULL),pFase1(NULL),pFase2(NULL),
pGC(Gerenciadores::GerenciadorColisoes::getInstance()),
ranking("../ranking.txt"),nomeJ1("JogadorDeconhecido1"),nomeJ2("JogadorDeconhecido2"){
    srand((unsigned)time(NULL));
    
    executar(); }
 
Jogo::~Jogo() {
    delete pFase2;
    delete pFase1;
    delete pJ1;
    delete pJ2;
    delete pMenu;
    
}
 
void Jogo::executar() {

    pMenu = new Menu(this);
    pMenu->executar();

    // Se fechou a janela ou escolheu Sair, nao inicia a fase
    if (!pGerenciadorGrafico->windowopen())
        return;

    int fase = pMenu->getFase();

    if(fase == 0)
        return;

    pJ1 = new Personagens::Jogador(CoordF(200.f,200.f),200,0,200.f);
    pJ1->initialize(true);

    pJ2 = NULL;
    if (pMenu->getMultiplayer()) {
        pJ2 = new Personagens::Jogador(CoordF(240.f,200.f),200,0,200.f);
        pJ2->initialize(false);
    }

        if(fase == 1) {
        // Pede o(s) nome(s) antes de comecar a fase 1
        nomeJ1 = pMenu->pedirNome("Jogador 1, digite seu nome:");
        if (!pGerenciadorGrafico->windowopen()) return; // fechou na tela de nome

        if (pJ2 != NULL) {
            nomeJ2 = pMenu->pedirNome("Jogador 2, digite seu nome:");
            if (!pGerenciadorGrafico->windowopen()) return;
        }

        pFase1 = new Fases::FasePrimeira();
        pFase1->executar(pJ1, pJ2);
        
        if(pFase1->getConcluida()){

            pFase2 = new Fases::FaseSegunda();
            pFase2->somarPontos(pFase1->getPontosTotais()); 
            pFase2->atualizarTextoPontos();

            pFase2->executar(pJ1,pJ2);

            if(pFase2->getConcluida()){
                int pontosFinais = pFase2->getPontosTotais(); 

                std::string nomeJogadores = nomeJ1;
                if (pJ2 != NULL)
                    nomeJogadores = nomeJ1 + "_&_" + nomeJ2;

                ranking.registrar(nomeJogadores, pontosFinais);
            }
        }
    }


    else if (fase == 2) {
        pFase2 = new Fases::FaseSegunda();
        pFase2->atualizarTextoPontos();

        pFase2->executar(pJ1,pJ2);
        std::cout << "Fase 2 rodando" << std::endl;
        
        if(pFase2->getConcluida()){
            return;
        }
    }
}
