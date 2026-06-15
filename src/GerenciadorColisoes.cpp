#include "GerenciadorColisoes.hpp"
#include "Limites.hpp"
#include <iostream>
#include "Projetil.hpp"
#include "Morte.hpp"

namespace Gerenciadores {

    GerenciadorColisoes* GerenciadorColisoes::instance = NULL;
    
    const float GerenciadorColisoes::alturaJogador = 64.f; // Mudar para um get-set

    GerenciadorColisoes* GerenciadorColisoes::getInstance() {
        if (instance == NULL)
            instance = new GerenciadorColisoes();
        return instance;
    }

    GerenciadorColisoes::GerenciadorColisoes() : pJog(NULL) {}

    GerenciadorColisoes::~GerenciadorColisoes() {}

    void GerenciadorColisoes::setJogador(Jogador* pJogador) {
        if(pJog){
            pJog2 = pJogador;
        }
        else{
            pJog = pJogador;
        }
        
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

            bool colidiu = (*iteradorObs)->obstruir(pos, vel.y, vel.x, chao, alturaJogador);

            if (colidiu && (*iteradorObs)->isDanoso())
                pJog->morrer();

        }

        pJog->setPos(pos);
        pJog->setVel(vel);
        pJog->setChao(chao);

        // Func copiada para jog2

        pos = pJog2->getPos();
        vel = pJog2->getVel();
        chao = pJog2->noChao();

        for (iteradorObs = ListaObstaculos.begin(); iteradorObs != ListaObstaculos.end(); ++iteradorObs) {

            bool colidiu = (*iteradorObs)->obstruir(pos, vel.y, vel.x, chao, alturaJogador);

            if (colidiu && (*iteradorObs)->isDanoso())
                pJog2->morrer();

        }

        pJog2->setPos(pos);
        pJog2->setVel(vel);
        pJog2->setChao(chao);
    }

    void GerenciadorColisoes::tratarColisoesJogador() {

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

        // Func copiada para jog2

        CoordF posJog2 = pJog2->getPos();

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
            pJog2->morrer(); // Aqui, perder vida ao inves de morrer.
        }
    }

    void GerenciadorColisoes::tratarColisoesObstaculosArvores() {

    for (Inimigo* inimigo : ListaInimigos) {
        Arvore* arvore = dynamic_cast<Arvore*>(inimigo); // Dynamic cast da certeza de que o inimigo e uma arvore.

        if (arvore == nullptr || !arvore->estaVivo())
            continue;

        CoordF pos = arvore->getPos();
        CoordF vel = arvore->getVel();
        bool chao  = arvore->noChao();

        for (Obstaculos::Obstaculo* obs : ListaObstaculos)
            obs->obstruir(pos, vel.y, vel.x, chao, alturaJogador);

        arvore->setPos(pos);
        arvore->setVel(vel);
        arvore->setChao(chao);
    }
    }

    void GerenciadorColisoes::gravitar(float dt) {

        float gravidade = 800.f; // Define gravidade geral

        pJog->gravidade(dt, gravidade);
        pJog2->gravidade(dt,gravidade);

        for (Inimigo* inimigo : ListaInimigos) {
        if (inimigo->estaVivo() && dynamic_cast<Arvore*>(inimigo)) // Dynamic_cast feito pelo claude. Somente gravita inimigos ARVORE
            inimigo->gravidade(dt, gravidade);
        }
    }

    void GerenciadorColisoes::tratarLimites() { //TODO adicionar colisao com jogador 2
        limites->aplicarLimites(pJog);
        limites->aplicarLimites(pJog2);
    }

    void GerenciadorColisoes::tratarColisaoProjetil() {
    if (pJog == NULL) return;
 
    CoordF posJog = pJog->getPos();
    CoordF posJog2 = pJog2->getPos();
    float metade = alturaJogador / 2.f;
 
    // Procura bosses (Morte) na lista de inimigos
    std::vector<Inimigo*>::iterator it;
    for (it = ListaInimigos.begin(); it != ListaInimigos.end(); ++it) {

        Morte* boss = dynamic_cast<Morte*>(*it);
        if (boss == NULL) continue;
 
        Entidades::Projetil* proj = boss->getProjetil();
        if (proj == NULL || !proj->estaAtivo()) 
            continue;
 
        CoordF posProj = proj->getPos();
        float dx = posJog.x - posProj.x;
        float dy = posJog.y - posProj.y;
 
        // Colisão por bounding box (metade do jogador + raio do projétil)
        // Trecho abaixo feito pelo Claude
        if (std::abs(dx) < metade + 8.f && std::abs(dy) < metade + 8.f) {
            proj->desativar(); // consome o projétil
            if (!pJog->estaImune())
                pJog->tomarDano();
        }
    }
}

 
    void GerenciadorColisoes::executar(float dt) {
        if(pJog == NULL){
            std::cerr<<"ERRO: faltou o jogador"<<std::endl;
            return;
            
        }
        if(limites == NULL){
            std::cerr<<"ERRO: faltou os limites"<<std::endl;
            return;
        }
        gravitar(dt);
        tratarColisoesObstaculosArvores();
        tratarColisoesObstaculos();
        tratarColisoesJogador();
        tratarColisaoProjetil();
        tratarLimites();
    }


}
