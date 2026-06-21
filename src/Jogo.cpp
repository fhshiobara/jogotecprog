#include "Jogo.hpp"
#include "Menu.hpp"
#include "Demonio.hpp"
#include "Bixo.hpp"
#include "Morte.hpp"
#include "Plataforma.hpp"
#include "GerenciadorColisoes.hpp"
#include "Espinhos.hpp"
#include "SingleFrameAnimation.hpp"

using namespace Obstaculos;
using namespace Personagens;
 
Jogo::Jogo() : pGerenciadorGrafico(Gerenciadores::GerenciadorGrafico::getInstance()),pJ1(NULL),pJ2(NULL),pFase1(NULL),pFase2(NULL),pGC(Gerenciadores::GerenciadorColisoes::getInstance()){
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

    pJ1 = new Personagens::Jogador(CoordF(200.f,200.f),300,0,200.f);
    pJ1->initialize(true);

    pJ2 = NULL;
    if (pMenu->getMultiplayer()) {
        pJ2 = new Personagens::Jogador(CoordF(240.f,200.f),3,0,200.f);
        pJ2->initialize(false);
    }

    if(fase == 1) {
        pFase1 = new Fases::FasePrimeira();
        pFase1->executar(pJ1, pJ2);
        if(pFase1->getConcluida()){
            pFase2 = new Fases::FaseSegunda();
            pFase2->somarPontos(pFase1->getPontosTotais());
            pFase2->executar(pJ1,pJ2);
            
            
        }
    }
    
    else if (fase == 2) {
        pFase2 = new Fases::FaseSegunda();
        pFase2->executar(pJ1,pJ2);
        std::cout << "Fase 2 rodando" << std::endl;
        
        if(pFase2->getConcluida()){
            return;
        }
    }
}
