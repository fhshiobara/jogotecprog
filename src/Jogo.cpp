#include "Jogo.hpp"
#include "Inimigo.hpp"
#include "Plataforma.hpp"
#include "GerenciadorColisoes.hpp"
#include "Obst_Medio.hpp" 
 
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
 
    // Inimigo* inimigo = new Inimigo(CoordF(400.0f, 200.0f), 2, 100.0f);
    // inimigo->initialize();
 
    Plataforma* chao = new Plataforma(CoordF(0.f, 500.f), 800.f, 20.f);
    Obst_Medio* obs_medio = new Obst_Medio(CoordF(300.f, 450.f), 70.f, 100.f, 0.85f);
 
    pColisM->setJogador(jogador);
    pColisM->incluirObstaculo(chao);
    pColisM->incluirObstaculo(obs_medio);
    // pColisM->incluirInimigo(inimigo);
 
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
            if(evento.type == sf::Event::KeyReleased){
                if(evento.key.code == sf::Keyboard::D){andDir = false;}
                if(evento.key.code == sf::Keyboard::A){andEsq = false;}
            }
        }
        
        
        animacao = Animation_ID::idle;
        
        if(andDir){
            
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
        jogador->gravidade(dt);
        pColisM->executar();
 
        // Render
        pGerenciadorGrafico->clear();
        chao->desenhar();
        obs_medio->desenhar();
        jogador->atualizarAnimacao(animacao, olhandoEsquerda, dt);
        jogador->desenhar();
        // inimigo->perseguir(jogador->getPos(), dt);
        // inimigo->atualizarAnimacao(Animation_ID::walk, inimigo->estaOlhandoEsquerda(), dt);
        // inimigo->desenhar();
        pGerenciadorGrafico->getWindow()->display();
    }
 
    delete jogador;
    // delete inimigo;
    delete chao;
    delete obs_medio;
}
