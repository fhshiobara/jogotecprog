#include "GerenciadorColisoes.hpp"
#include "Limites.hpp"
#include <iostream>

namespace Gerenciadores {

    GerenciadorColisoes* GerenciadorColisoes::instance = NULL;
    
    const float GerenciadorColisoes::alturaJogador = 64.f; // Mudar para um get-set

    GerenciadorColisoes* GerenciadorColisoes::getInstance() {
        if (instance == NULL)
            instance = new GerenciadorColisoes();
        return instance;
    }

    GerenciadorColisoes::GerenciadorColisoes() : pJog(nullptr) {}

    GerenciadorColisoes::~GerenciadorColisoes() {}

    void GerenciadorColisoes::setJogador(Jogador* pJogador) {
        pJog = pJogador;
    }

    void GerenciadorColisoes::setLimite(float largura, float altura) {
        Obstaculos::Limites* limiteMapa = new Obstaculos::Limites(largura, altura);
        limites = limiteMapa;
    }


    void GerenciadorColisoes::incluirInimigo(Inimigo* pInimigo) {
        if (pInimigo != NULL)
            ListaInimigos.push_back(pInimigo);
        else
            std::cerr << this << " Inimigo invalido" << std::endl;
    }

    void GerenciadorColisoes::incluirObstaculo(Obstaculos::Obstaculo* pObstaculo) {
        if (pObstaculo != NULL)
            ListaObstaculos.push_back(pObstaculo);
        else
            std::cerr << this << " Obstaculo invalido" << std::endl;
    }

    void GerenciadorColisoes::tratarColisoesObstaculos() {

        CoordF pos = pJog->getPos();
        CoordF vel = pJog->getVel();
        bool chao = pJog->noChao();

        std::list<Obstaculos::Obstaculo*>::iterator iteradorObs;

        for (iteradorObs = ListaObstaculos.begin(); iteradorObs != ListaObstaculos.end(); ++iteradorObs) {

            bool colidiu = (*iteradorObs)->obstruir(pos, vel.y,vel.x, chao, alturaJogador);

            if (colidiu && (*iteradorObs)->isDanoso())
                pJog->morrer();
        }

        pJog->setPos(pos);
        pJog->setVel(vel);
        pJog->setChao(chao);
    }

    void GerenciadorColisoes::TratarColisoesSeres() {

        CoordF posJog = pJog->getPos();

        float metade = alturaJogador / 2.f;

        std::vector<Inimigo*>::iterator iteradorInimigo;

    for (iteradorInimigo = ListaInimigos.begin(); iteradorInimigo != ListaInimigos.end(); ++iteradorInimigo) {
        Inimigo* inimigoAtual = *iteradorInimigo;

        if (!inimigoAtual->estaVivo()) 
            continue;

        CoordF posInimigo = inimigoAtual->getPos();

        float distanciaX = posJog.x - posInimigo.x;
        float distanciaY = posJog.y - posInimigo.y;

        bool colidindoX = std::abs(distanciaX) < metade * 2.f;
        bool colidindoY = std::abs(distanciaY) < metade * 2.f;

        if (colidindoX && colidindoY)
            pJog->morrer(); // Aqui, perder vida ao inves de morrer.

        }
    }

    void GerenciadorColisoes::tratarLimites() {
        limites->aplicarLimites(pJog);
    }


    void GerenciadorColisoes::executar() {
        tratarColisoesObstaculos();
        TratarColisoesSeres();
        tratarLimites();
    }

}