#include "Jogo.hpp"
#include "Inimigo.hpp"
#include "Plataforma.hpp"

Jogo::Jogo() : pGerenciadorGrafico(Gerenciadores::GerenciadorGrafico::getInstance()) { executar(); }

Jogo::~Jogo() {}

void Jogo::executar() {
    sf::Clock relogio;

    Jogador* jogador = new Jogador(CoordF(200.0f, 200.0f), 3, 0, 200.0f);
    jogador->initialize();

    Inimigo* inimigo = new Inimigo(CoordF(400.0f, 200.0f), 2, 100.0f);
    inimigo->initialize();

    Plataforma* chao = new Plataforma(CoordF(0.f, 500.f), 800.f, 20.f);

    const float alturaJogador = 64.f;
    bool olhandoEsquerda = false;
    Animation_ID animacao = Animation_ID::idle;

    while (pGerenciadorGrafico->windowopen()) {
        float dt = relogio.restart().asSeconds();

        // Eventos
        sf::Event evento;
        while (pGerenciadorGrafico->getWindow()->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                pGerenciadorGrafico->closeWindow();
            if (evento.type == sf::Event::KeyPressed &&
                evento.key.code == sf::Keyboard::Space)
                jogador->pular();
        }

        // Input
        animacao = Animation_ID::idle;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            jogador->moverX(true, dt);
            olhandoEsquerda = false;
            animacao = Animation_ID::walk;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            jogador->moverX(false, dt);
            olhandoEsquerda = true;
            animacao = Animation_ID::walk;
        }

        // Física e colisão
        jogador->gravidade(dt);
        CoordF pos  = jogador->getPos();
        bool   chao_flag = jogador->noChao();
        float velocidade = jogador->getVelocidade();

        chao->obstruir(pos, velocidade, chao_flag, alturaJogador);
        jogador->setPos(pos);
        jogador->setVelocidade(velocidade);
        jogador->setChao(chao_flag);

        // Render
        pGerenciadorGrafico->clear();
        chao->desenhar();
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
}
