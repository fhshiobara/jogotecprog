#include "Jogo.hpp"
#include "Inimigo_Medio.hpp"
#include "Inimigo_Facil.hpp"
#include "Plataforma.hpp"
#include "GerenciadorColisoes.hpp"
#include "Obst_Medio.hpp"
#include "SingleFrameAnimation.hpp"
#include "Limites.hpp"

using namespace Obstaculos;
 
Jogo::Jogo() : pGerenciadorGrafico(Gerenciadores::GerenciadorGrafico::getInstance()) { executar(); }
 
Jogo::~Jogo() {}
 
void Jogo::executar() { 
    sf::Clock relogio;
    
    bool andDir = false;
    bool andEsq = false;
    
    andDir = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    andEsq = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
 
    Jogador* jogador = new Jogador(CoordF(200.0f, 200.0f), 3, 0, 200.0f);
    jogador->initialize();
 
    Arvore* inimigo = new Arvore(CoordF(400.0f, 200.0f), 100, 100.0f, 200.0f);
    inimigo->initialize();
 
     Plataforma* chao = new Plataforma(CoordF(200.f, 500.f), 800.f, 20.f);
    
    Plataforma* plat2 = new Plataforma(CoordF(0.f, 400.f),400.f,20.f);
    
    Plataforma* plat3 = new Plataforma(CoordF(260.f,300.f),400.f,20.f);
    
    Plataforma* plat4 = new Plataforma(CoordF(0.f,190.f),400.f,20.f);
    
    Obst_Medio* obs_medio = new Obst_Medio(CoordF(650.f, 450.f), 70.f, 100.f, 0.85f);
    
    Gerenciadores::SingleFrameAnimation* background = new Gerenciadores::SingleFrameAnimation("../assets/background.png",CoordF(0.0f,0.0f),CoordF(800.0f,600.0f),1.0);
 
    pColisM->setJogador(jogador);
    pColisM->incluirObstaculo(plat3);
    pColisM->incluirObstaculo(plat2);
    pColisM->incluirObstaculo(plat4);
    pColisM->incluirObstaculo(chao);
    pColisM->incluirObstaculo(obs_medio);
    pColisM->setLimite(800.f, 600.f);
    pColisM->incluirInimigo(inimigo);
 
    bool olhandoEsquerda = false;
    Animation_ID animacao = Animation_ID::idle;
 
    while (pGerenciadorGrafico->windowopen()) {
        float dt = relogio.restart().asSeconds();
 
        // Eventos
        sf::Event evento;
 
        while (pGerenciadorGrafico->getWindow()->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                pGerenciadorGrafico->closeWindow();
            if (evento.type == sf::Event::KeyPressed){
                if(evento.key.code == sf::Keyboard::Space){jogador->pular();}
                //pode ser feito aqui pois pular é uma acao e nao algo continuo
                
                if(evento.key.code==sf::Keyboard::D){andDir = true;}
                
                if(evento.key.code == sf::Keyboard::A){andEsq = true;}
            }
            if(evento.type == sf::Event::KeyReleased) {
                if(evento.key.code == sf::Keyboard::D){andDir = false;}
                if(evento.key.code == sf::Keyboard::A){andEsq = false;}
            }
        }
        
        animacao = Animation_ID::idle;
        
        if(andDir) {
            jogador->moverX(true,dt);
            olhandoEsquerda = false;
            animacao = Animation_ID::walk;
        }
        
        if(andEsq){
            jogador->moverX(false,dt);
            olhandoEsquerda = true;
            animacao = Animation_ID::walk;
        }

        if (!jogador->noChao())
            animacao = Animation_ID::jump;
 
        // Física e Colisões
        pColisM->executar(dt);
 
        // Render
        pGerenciadorGrafico->clear();
        background->render();
        chao->desenhar();
        plat2->desenhar();
        plat3->desenhar();
        plat4->desenhar();
        obs_medio->desenhar();
        jogador->atualizarAnimacao(animacao, olhandoEsquerda, dt);
        jogador->desenhar();
        inimigo->perseguir(jogador->getPos(), dt);
        inimigo->atualizarAnimacao(Animation_ID::walk, inimigo->estaOlhandoEsquerda(), dt);
        inimigo->desenhar();
        pGerenciadorGrafico->getWindow()->display();
    }
 
    delete jogador;
    delete inimigo;
     delete chao;
    delete obs_medio;
}
