#include "Jogo.hpp"
#include <iostream>

Jogo::Jogo():pGerenciadorGrafico(Gerenciadores::GerenciadorGrafico::getInstance()){ executar(); }

Jogo::~Jogo(){}

/*void Jogo::executar() {

    Gerenciadores::GerenciadorGrafico* pGrafico = Gerenciadores::GerenciadorGrafico::getInstance();

    while (pGrafico->windowopen()) {
        
        sf::Event evento;

        while (pGrafico->getWindow()->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                pGrafico->closeWindow();
            }
        }
        
        
        
        pGrafico->clear();
        
        sf::RectangleShape rectangle(sf::Vector2f(150.f,100.f));
        Jogador jogador;
        
        
        rectangle.setFillColor(sf::Color::Blue);
        rectangle.setOutlineThickness(5.f);               // Espessura da borda
        rectangle.setOutlineColor(sf::Color::White);
        rectangle.setOrigin(-150.f,-50.f);
        pGrafico->render(&rectangle);
        rectangle.move(sf::Vector2f(0.5f,0.f));
        //os comandos de desenho devem estar aqui
        
        
        pGrafico->display();
    }

}*/

/*void Jogo::executar() {

    Gerenciadores::GerenciadorGrafico* pGrafico = Gerenciadores::GerenciadorGrafico::getInstance();

    // 1. Criamos um relógio para controlar o tempo (dt) das animações
    sf::Clock relogio;

    // 2. Instanciamos o jogador na posição x: 200, y: 200 (com 3 de HP, 0 pontos e velocidade 5.0f)
    // Ajuste o caminho das imagens se o seu grupo guardou em outra pasta!
    Jogador jogador(CoordF(200.0f, 200.0f), 3, 0, 5.0f);
    
    // 3. Inicializamos as animações/sprites dele
    jogador.initialize();

    while (pGrafico->windowopen()) {
        
        // Calcula o tempo que passou desde o último frame (Delta Time)
        float dt = relogio.restart().asSeconds();

        sf::Event evento;
        while (pGrafico->getWindow()->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                pGrafico->closeWindow();
            }
        }

        // LIMPAMOS A TELA
        pGrafico->clear();

        // 4. TESTE: Atualizamos a lógica e a animação do jogador
        // Passamos o dt, se ele está olhando para a esquerda (false) e a posição atual dele
        // (Como você ainda não implementou o update completo, chamamos diretamente as funções necessárias)
        jogador.moverX(true); // Apenas para testar se ele sai do lugar se quiser
        
        // Buscamos o objeto de animação interna do jogador para dar update e renderizar.
        // Se a sua variável 'sprite' dentro de Jogador for pública ou tiver um getSprite(), use-a:
        // jogador.sprite.update(Animation_ID::idle, false, jogador.getPos(), dt);
        // jogador.sprite.render();
        
        // Caso queira usar o método executar do seu próprio jogador (se ele já chamar o update da sprite dentro):
        // jogador.executar(dt);

        // RENDERIZAMOS O JOGADOR
        // Se você criou uma função para desenhar o jogador, chame-a aqui.
        // Caso contrário, para este teste rápido, desenhamos a sprite dele diretamente pelo gerenciador:
        // pGrafico->render(jogador.getSpriteBody());

        // DESENHAMOS A TELA
        // Certifique-se de que seu pGrafico possui um método para mostrar os desenhos na tela (display)
        // pGrafico->display();
    }
}*/

void Jogo::executar() {
    sf::Clock relogio;

    Jogador* jogador = new Jogador(CoordF(200.0f, 200.0f), 3, 0, 200.0f);
    jogador->initialize();
    
    bool olhandoEsquerda = false;
    Animation_ID animacaoAtual = Animation_ID::idle;

    while (pGerenciadorGrafico->windowopen()) {
        float dt = relogio.restart().asSeconds();

        sf::Event evento;
        while (pGerenciadorGrafico->getWindow()->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                pGerenciadorGrafico->closeWindow();
            }
        }

        // 🕹️ CAPTURA DE INPUTS DIRETA E LIMPA
        animacaoAtual = Animation_ID::idle; // Se não apertar nada, fica parado

        if (evento.type == sf::Event::KeyPressed) {
            if(evento.key.code == sf::Keyboard::D){
                jogador->moverX(true);           // Move para a direita
                olhandoEsquerda = false;        // Olha para a direita
                animacaoAtual = Animation_ID::walk; // Ativa animação de andar
            }
            
        }
        if (evento.type == sf::Event::KeyPressed) {
            if(evento.key.code == sf::Keyboard::A){
                jogador->moverX(false);           // Move para a direita
                olhandoEsquerda = true;        // Olha para a direita
                animacaoAtual = Animation_ID::walk; // Ativa animação de andar
            }
            
        }
        
        if(evento.type == sf::Event::KeyReleased){
            if(evento.key.code ==sf::Keyboard::D || evento.key.code == sf::Keyboard::A){
                animacaoAtual = Animation_ID::idle;
            }
        }

        pGerenciadorGrafico->clear();

        // Atualiza os frames da animação por tempo (o dt entra apenas aqui!)
        jogador->atualizarAnimacao(animacaoAtual, olhandoEsquerda, dt);
        
        // Desenha o personagem centralizado
        jogador->desenhar();

        pGerenciadorGrafico->getWindow()->display();
    }

    delete jogador;
}

