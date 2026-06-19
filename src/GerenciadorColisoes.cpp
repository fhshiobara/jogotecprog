#include "GerenciadorColisoes.hpp"
#include "Bixo.hpp"
#include "Projetil.hpp"
#include "Morte.hpp"
#include <iostream>

using namespace Personagens;

namespace Gerenciadores {

    GerenciadorColisoes* GerenciadorColisoes::instance = NULL;
    
    const float GerenciadorColisoes::alturaJogador = 64.f; // Mudar para um get-set
    const float GerenciadorColisoes::alturaBixo = 50.f; 

    GerenciadorColisoes* GerenciadorColisoes::getInstance() {
        if (instance == NULL)
            instance = new GerenciadorColisoes();
        return instance;
    }

    GerenciadorColisoes::GerenciadorColisoes() : pJog1(NULL), pJog2(NULL), tamTela(800.f, 600.f) {}

    GerenciadorColisoes::~GerenciadorColisoes() {}

    void GerenciadorColisoes::setJogador(Personagens::Jogador* pJogador) {
        if(pJog1){
            pJog2 = pJogador;
        }
        else{
            pJog1 = pJogador;
        }
    }

    void GerenciadorColisoes::setLimite(float largura, float altura) {
        tamTela = CoordF(largura, altura);
    }

    void GerenciadorColisoes::aplicarLimites(Personagens::Personagem* pPersonagem) {
        if (pPersonagem == NULL) return;

        CoordF pos = pPersonagem->getPos();
        CoordF vel = pPersonagem->getVel();

        float metade = alturaJogador / 2.f;

        // Borda esquerda
        if (pos.x - metade < 0.f) {
            pos.x = metade;
            vel.x = 0.f;
        }

        // direita
        if (pos.x + metade > tamTela.x) {
            pos.x = tamTela.x - metade;
            vel.x = 0.f;
        }
        // superior
        if (pos.y - metade < 0.f) {
            pos.y = metade;
            vel.y = 0.f;
        }
        // inferior
        if (pos.y + metade > tamTela.y) {
            pos.y = tamTela.y - metade;
            vel.y = 0.f;
            pPersonagem->setChao(true);
        }
        pPersonagem->setPos(pos);
        pPersonagem->setVel(vel);
    }



    void GerenciadorColisoes::incluirInimigo(Personagens::Inimigo* pInimigo) {
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

        CoordF pos = pJog1->getPos();
        CoordF vel = pJog1->getVel();
        bool chao = pJog1->noChao();

        std::list<Obstaculos::Obstaculo*>::iterator iteradorObs;

        for (iteradorObs = ListaObstaculos.begin(); iteradorObs != ListaObstaculos.end(); ++iteradorObs) {

            bool colidiu = (*iteradorObs)->obstruir(pos, vel.y, vel.x, chao, alturaJogador);

            if (colidiu && (*iteradorObs)->isDanoso())
                pJog1->tomarDano();

        }

        pJog1->setPos(pos);
        pJog1->setVel(vel);
        pJog1->setChao(chao);

        // Func copiada para jog2
        if(pJog2 == NULL)
            return;

        pos = pJog2->getPos();
        vel = pJog2->getVel();
        chao = pJog2->noChao();

        for (iteradorObs = ListaObstaculos.begin(); iteradorObs != ListaObstaculos.end(); ++iteradorObs) {

            bool colidiu = (*iteradorObs)->obstruir(pos, vel.y, vel.x, chao, alturaJogador);

            if (colidiu && (*iteradorObs)->isDanoso())
                pJog2->tomarDano();

        }

        pJog2->setPos(pos);
        pJog2->setVel(vel);
        pJog2->setChao(chao);

    }

    void GerenciadorColisoes::tratarColisoesJogador() {

        CoordF posJog = pJog1->getPos();

        float metade = alturaJogador / 2.f;

        std::vector<Inimigo*>::iterator iteradorInimigo;

    for (iteradorInimigo = ListaInimigos.begin(); iteradorInimigo != ListaInimigos.end(); ++iteradorInimigo) {
        Personagens::Inimigo* inimigoAtual = *iteradorInimigo;

        if (!inimigoAtual->estaVivo()) 
            continue;

        CoordF posInimigo = inimigoAtual->getPos();

        float distanciaX = posJog.x - posInimigo.x;
        float distanciaY = posJog.y - posInimigo.y;

        bool colidindoX = std::abs(distanciaX) < metade * 1.f;
        bool colidindoY = std::abs(distanciaY) < metade * 1.f; // mudar os fatores para regular hitbox com jogador

        if (colidindoX && colidindoY){
            if(pJog1->getAtacando()){
                inimigoAtual->tomarDano();
            }
            else{
                inimigoAtual->danificar(pJog1);
                pJog1->tomarDano(); // Aqui, perder vida ao inves de morrer.
            }
        }
    }

        // Func copiada para jog2
        if(pJog2 == NULL) 
            return;

        CoordF posJog2 = pJog2->getPos();

    for (iteradorInimigo = ListaInimigos.begin(); iteradorInimigo != ListaInimigos.end(); ++iteradorInimigo) {
        Personagens::Inimigo* inimigoAtual = *iteradorInimigo;

        if (!inimigoAtual->estaVivo()) 
            continue;

        CoordF posInimigo = inimigoAtual->getPos();

        float distanciaX = posJog2.x - posInimigo.x;
        float distanciaY = posJog2.y - posInimigo.y;

        bool colidindoX = std::abs(distanciaX) < metade * 2.f;
        bool colidindoY = std::abs(distanciaY) < metade * 2.f;

        if (colidindoX && colidindoY){
            inimigoAtual->danificar(pJog2);
            pJog2->tomarDano(); // Aqui, perder vida ao inves de morrer.
        }
        }
    }

    void GerenciadorColisoes::tratarColisoesObstaculosBixos() {

    for (Personagens::Inimigo* inimigo : ListaInimigos) {
        Personagens::Bixo* bixo = dynamic_cast<Personagens::Bixo*>(inimigo); // Dynamic cast da certeza de que o inimigo e uma Bixo.

        if (bixo == nullptr || !bixo->estaVivo())
            continue;

        CoordF pos = bixo->getPos();
        CoordF vel = bixo->getVel();
        bool chao = bixo->noChao();

        for (Obstaculos::Obstaculo* obs : ListaObstaculos)
            obs->obstruir(pos, vel.y, vel.x, chao, alturaBixo);

        bixo->setPos(pos);
        bixo->setVel(vel);
        bixo->setChao(chao);
    }
    }

    void GerenciadorColisoes::gravitar(float dt) {

        float gravidade = 800.f; // Define gravidade geral

        pJog1->gravidade(dt, gravidade);
        if(pJog2 != NULL)
            pJog2->gravidade(dt,gravidade);

        for (Inimigo* inimigo : ListaInimigos) {
            inimigo->gravidade(dt, gravidade);
        }
    }

    void GerenciadorColisoes::tratarLimites() {
        aplicarLimites(pJog1);
        if(pJog2 != NULL)
            aplicarLimites(pJog2);

        for (Personagens::Inimigo* inimigo : ListaInimigos) {
            if (inimigo != nullptr && inimigo->estaVivo())
                aplicarLimites(inimigo);
            }
    }

    void GerenciadorColisoes::tratarColisaoProjetil() {
        if (pJog1 == NULL) return;

        float metade = alturaJogador / 2.f;

        // Procura bosses (Morte) na lista de inimigos

        std::vector<Inimigo*>::iterator it;

        for (it = ListaInimigos.begin(); it != ListaInimigos.end(); it++) {

            Personagens::Morte* boss = dynamic_cast<Personagens::Morte*>(*it);
            if (boss == NULL) continue;

            Entidades::Projetil* proj = boss->getProjetil();

            if (proj == NULL || !proj->estaAtivo())
                continue;

            CoordF posProj = proj->getPos();

            float dx1 = pJog1->getPos().x - posProj.x;
            float dy1 = pJog1->getPos().y - posProj.y;

            if (std::abs(dx1) < metade + 8.f && std::abs(dy1) < metade + 8.f) {
                proj->desativar();
                //if (!pJog1->estaImune())
                    pJog1->setInvulnerabilidade(0.9);
                    pJog1->tomarDano();
                continue; // projetil ja foi consumido, prox boss
            }

            // Checa colisao com o jogador 2 (se existir)

            if (pJog2 != NULL) {
                float dx2 = pJog2->getPos().x - posProj.x;
                float dy2 = pJog2->getPos().y - posProj.y;

                if (std::abs(dx2) < metade + 8.f && std::abs(dy2) < metade + 8.f) {
                    proj->desativar();
                    //if (!pJog2->estaImune())
                        pJog2->setInvulnerabilidade(0.9);
                        pJog2->tomarDano();
                }

            }
        }
    }

    void GerenciadorColisoes::atualizarImunidades(float dt) {
        pJog1->tempoImunidade(dt);
        pJog1->tempoDesacelerado(dt);

        if (pJog2 != NULL){
            pJog2->tempoImunidade(dt);
            pJog2->tempoDesacelerado(dt);
        }

        for (Inimigo* inimigo : ListaInimigos)
            if (inimigo->estaVivo())
                inimigo->tempoImunidade(dt);
    }

    void GerenciadorColisoes::tratarAtaqueJogadores() {
        float alcance = alturaJogador + 2.0f;  // alcance do golpe (corpo-a-corpo), funciona em raio
       
        std::vector<Inimigo*>::iterator it;
        for (it = ListaInimigos.begin(); it != ListaInimigos.end(); ++it) {

            Personagens::Inimigo* inimigo = *it;
            if (!inimigo->estaVivo()) continue;

            CoordF posIni = inimigo->getPos();
            // Ataque do jogador 1
            if (pJog1 != NULL && pJog1->getAtacando()) {
                CoordF posJog = pJog1->getPos();

                if (std::abs(posJog.x - posIni.x) < alcance &&
                    std::abs(posJog.y - posIni.y) < alcance) {
                    /// Adaptado da Func. de colisao do projetil
                
                    if (!inimigo->estaImune())
                        inimigo->tomarDano();
                }
            }
            // Ataque do jogador 2, equivalente ao codigo acima
            

            if (pJog2 != NULL && pJog2->getAtacando()) {
                CoordF posJog2 = pJog2->getPos();

                if (std::abs(posJog2.x - posIni.x) < alcance &&
                    std::abs(posJog2.y - posIni.y) < alcance) {
                    if (!inimigo->estaImune())
                        inimigo->tomarDano();
                }

            }

        }

    }
 
    void GerenciadorColisoes::executar(float dt) {
        if(pJog1 == NULL){
            std::cerr<<"ERRO: faltou o jogador"<<std::endl;
            return;
        }
        gravitar(dt);
        atualizarImunidades(dt);
        
        tratarColisoesObstaculosBixos();
        tratarColisoesObstaculos();
        tratarColisoesJogador();
        tratarColisaoProjetil();
        tratarAtaqueJogadores();
        tratarLimites();
    }


}
