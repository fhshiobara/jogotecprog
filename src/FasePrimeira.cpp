#include "FasePrimeira.hpp"
#include "Espinhos.hpp"
 
static void desenharAreaColisao(
    sf::RenderWindow* window,
    CoordF pos,
    float alcance)
{
    sf::RectangleShape debug;
 
    debug.setSize(sf::Vector2f(
        alcance * 2.f,
        alcance * 2.f
    ));
 
    debug.setPosition(
        pos.x - alcance,
        pos.y - alcance
    );
 
    debug.setFillColor(sf::Color::Transparent);
    debug.setOutlineThickness(2.f);
    debug.setOutlineColor(sf::Color::Red);
 
    window->draw(debug);
} // Func helper para debug das colisoes. Feita pelo ChatGPT

 
using namespace Personagens;
 
namespace Fases{
 
FasePrimeira::FasePrimeira():Fase(),max_inim_Demonio(4),max_obst_Espinhos(4),background(NULL){
    background = new Gerenciadores::SingleFrameAnimation("../assets/Background/background.png",CoordF(0.f,0.f),CoordF(800.f,600.f),1.0);
    
}
 
FasePrimeira::~FasePrimeira(){
    delete background;
    background = NULL;
}
 
void FasePrimeira::criarInimigosDemonio(){
    int num_inim_medio = rand()%(max_inim_Demonio +1);
 
    if(num_inim_medio<10){num_inim_medio=1;} //numero minimo de inimigos
 
    int num_demonios_criados = 0;
 
    while(num_demonios_criados<num_inim_medio){
        int aux = rand()%9;
        Grid espaco = static_cast<Grid>(aux);
        if(mapa.estaOcupado(espaco)){
            CoordF pos = mapa.getCoord(espaco);
            pos.y = pos.y-30;
            Demonio* pDemo = NULL;
            pDemo = new Demonio(pos, 2, 10.0f, 1 + (rand() % 10));
 
            if(pDemo!=NULL){
                num_demonios_criados++;
                vInimigos.push_back(pDemo);
 
                list_ents.incluir(pDemo);
                pGC->incluirInimigo(pDemo);
            }
 
            else{
                std::cerr<<"Falha na alocacao do demonio"<<std::endl;
            }
 
        }
    }
 
 
}
 
void FasePrimeira::criarObstaculosEspinhos(){
    float alt_min = 50;
    float larg_min = 80;
    float tam_plat = 0;
 
    int num_obst_medio = rand()%(max_obst_Espinhos + 1);
 
    if(num_obst_medio<3){num_obst_medio = 3;} //numero minimo de obstaculos
 
    int num_obst_criados =0;
 
    while(num_obst_criados<num_obst_medio){
        int aux = rand()%9;
        Grid espaco = static_cast<Grid>(aux);
 
        if(mapa.estaOcupado(espaco)){
            CoordF pos = mapa.getCoord(espaco);
            pos.y= pos.y - alt_min/2;
 
            Obstaculos::Espinhos* pEsp = NULL;
            pEsp = new Obstaculos::Espinhos(pos,alt_min, larg_min + rand()%36,1.0);
 
            if(pEsp!=NULL){
                if(pEsp != NULL){
                num_obst_criados++;
 
                mapa.setOcupado(espaco, false); // Para nao haver espinho nele mesmo
 
                list_ents.incluir(pEsp);
                pGC->incluirObstaculo(pEsp);
                }
            }
            else {
                std::cerr<<"ERRO: na alocação do espinho"<<std::endl;
            }
        }
    }
 
}
 
void FasePrimeira::criarInimigos(){
    criarInimigosBixo();
    criarInimigosDemonio();
}
 
void FasePrimeira::criarObstaculos(){
    criarObstaculosEspinhos();
}
 
void FasePrimeira::executar(){}
 
void FasePrimeira::executar(Personagens::Jogador* pJ1, Personagens::Jogador* pJ2){

    if(pGC==NULL || pJ1==NULL){

        std::cerr<<"ERRO: pGC nao foi inicializado"<<std::endl;
        return;

    }
    
    criarCenario();
    criarPlataformas();
    criarInimigos();
    criarObstaculos();
    inserirPlataformasAtrasado();
    
    pGC->removerJogadores();
 
    pGC->setJogador(pJ1);

    if(pJ2){
        pGC->setJogador(pJ2);
    }

    CoordF tam_tela_compensada = tam_tela;
    tam_tela_compensada.y -= 8.0f; // Deixa a colisao mais bonita com os limites
    pGC->setLimite(tam_tela_compensada);

    //list_ents.incluir(pJ1);

    sf::Clock clock;
    //setando o jogador

    bool andDir = false;
    bool andEsq = false;
    bool andDir2 = false;
    bool andEsq2 = false;

    bool olhandoEsquerda = false;
    bool olhandoEsquerda2 = false;

    Animation_ID animacao = Animation_ID::idle;
    Animation_ID animacao2 = Animation_ID::idle;

    pGG = Gerenciadores::GerenciadorGrafico::getInstance();

    while(pGG->windowopen()){
        
        float dt = clock.restart().asSeconds();

        sf::Event evento;

        while(pGG->getWindow()->pollEvent(evento)){

            if(evento.type==sf::Event::Closed){pGG->closeWindow();}

            if(evento.type ==sf::Event::KeyPressed){
                if(evento.key.code == sf::Keyboard::D){andDir=true;}
                if(evento.key.code == sf::Keyboard::A){andEsq=true;}
                if(evento.key.code == sf::Keyboard::Space){pJ1->pular();}
                if(evento.key.code==sf::Keyboard::E){
                    pJ1->setAtacando(true);
                    std::cout<<"iniciando o ataque P1"<<std::endl;
                }

                if(pJ2){
                    if(evento.key.code == sf::Keyboard::Right){andDir2=true;}
                    if(evento.key.code == sf::Keyboard::Left){andEsq2=true;}
                    if(evento.key.code == sf::Keyboard::Up){pJ2->pular();}
                    if(evento.key.code==sf::Keyboard::O){
                        pJ2->setAtacando(true);
                        std::cout<<"iniciando o ataque P2"<<std::endl;
                    }
                }
            } // E -> ataque player 1, O -> ataque player 2

            if(evento.type == sf::Event::KeyReleased){
                if(evento.key.code == sf::Keyboard::D){andDir=false;}
                if(evento.key.code == sf::Keyboard::A){andEsq=false;}
                if(evento.key.code==sf::Keyboard::E){
                    pJ1->setAtacando(false);
                    std::cout<<"cancelando o ataque P1"<<std::endl;
                }

                if(pJ2){
                    if(evento.key.code == sf::Keyboard::Right){andDir2=false;}
                    if(evento.key.code == sf::Keyboard::Left){andEsq2=false;}
                    if(evento.key.code==sf::Keyboard::O){
                        pJ2->setAtacando(false);
                        std::cout<<"cancelando o ataque P2"<<std::endl;
                    }
                }
            }
        }
        
        animacao = Animation_ID::idle;
        animacao2 = Animation_ID::idle;

        bool andando1 = false;
        bool andando2 = false;

        if(andDir){
            pJ1->moverX(true,dt);
            olhandoEsquerda = false;
            andando1 = true;
        }

        if(andEsq){
            pJ1->moverX(false,dt);
            olhandoEsquerda = true;
            andando1 = true;
        }

        if(pJ2){

            if(andDir2){
                pJ2->moverX(true,dt);
                olhandoEsquerda2 = false;
                andando2 = true;
            }

            if(andEsq2){
                pJ2->moverX(false,dt);
                olhandoEsquerda2 = true;
                andando2 = true;
            }

        }

        executarInimigos(vInimigos, pJ1, pJ2, dt); // se pJ2 == NULL, func ja resolve internamente
        
        pGC->executar(dt);
        

        pGG->clear();
        background->render();
        list_ents.percorrer(dt);
        
        if(!pJ1->setVivo()){
            animacao = Animation_ID::death;
        }
        
        if(pJ2!=NULL){
            if(!pJ2->setVivo()){
                animacao2 = Animation_ID::death;
            }
        }
        
        this->checarInimigos(pJ1, pJ2);
        
        if(this->getConcluida()){
            pGC->removerObstaculos();
            return; // vai fazer o execuat parar, eu acho
        }

        if(pJ2!=NULL){//se há jogador2, ambos precisam morrer para acabar
            if(!pJ1->setVivo() && !pJ2->setVivo()){
                pJ1->setPos(CoordF(1000.f,1000.f)); //joga o jogador para fora da tela
                pJ2->setPos(CoordF(1000.f,1000.f)); //joga o jogador para fora da tela
                pGC->removerJogadores();
                telaDerrota->render();
            }
        } else if(!pJ1->setVivo()) { //so 1 jogador
            std::cout << "flag" << std::endl;
            pJ1->setPos(CoordF(1000.f,1000.f)); //joga o jogador para fora da tela
            pGC->removerJogadores();
            
            telaDerrota->render();
        }

        animacao = decidirAnimacao(pJ1, andando1);

        pJ1->atualizarAnimacao(animacao, olhandoEsquerda, dt);
        pJ1->desenhar();
        //desenharAreaColisao(pGG->getWindow(), pJ1->getPos(), 32.f);

        if(pJ2){
            animacao2 = decidirAnimacao(pJ2, andando2);
            pJ2->atualizarAnimacao(animacao2, olhandoEsquerda2, dt);
            pJ2->desenhar();
        }

        desenharPontos();
        pGG->getWindow()->display();

    }
}
}

