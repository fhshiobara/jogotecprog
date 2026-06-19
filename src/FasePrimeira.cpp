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
    background = new Gerenciadores::SingleFrameAnimation("../assets/Background/background.png",CoordF(0.f,0.f),CoordF(800.f,600.f),1.0);
}
 
FasePrimeira::~FasePrimeira(){}
 
void FasePrimeira::criarInimigosDemonio(){
    int num_inim_medio = rand()%(max_inim_Demonio +1);
 
    if(num_inim_medio<10){num_inim_medio =1;} //numero minimo de inimigos
 
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
 
                // mapa.setOcupado(espaco, false); // Para nao haver espinho nele mesmo
 
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
                if(evento.key.code==sf::Keyboard::O){
                    pJ1->setAtacando(true);
                    std::cout<<"iniciando o ataque"<<std::endl;
                }
                
                
                if(pJ2){
                    if(evento.key.code == sf::Keyboard::Right){andDir2=true;}
                    if(evento.key.code == sf::Keyboard::Left){andEsq2=true;}
                    if(evento.key.code == sf::Keyboard::Up){pJ2->pular();}
                    if(evento.key.code==sf::Keyboard::O){
                        pJ2->setAtacando(true);
                        
                    }
                }
 
 
            }
            if(evento.type == sf::Event::KeyReleased){
 
                if(evento.key.code == sf::Keyboard::D){andDir=false;}
                if(evento.key.code == sf::Keyboard::A){andEsq=false;}
                if(evento.key.code==sf::Keyboard::O){
                    pJ1->setAtacando(false);
                    std::cout<<"cancelando o ataque"<<std::endl;
                }
                
                if(pJ2){
                    if(evento.key.code == sf::Keyboard::Right){andDir2=false;}
                    if(evento.key.code == sf::Keyboard::Left){andEsq2=false;}
                    if(evento.key.code==sf::Keyboard::O){pJ2->setAtacando(false);}
                    
                }
            }
 
        }
        animacao = Animation_ID::idle;
        animacao2 = Animation_ID::idle;
 
        if(andDir){
            pJ1->moverX(true,dt);
            olhandoEsquerda = false;
            animacao = Animation_ID::walk;
        }
        if(andEsq){
            pJ1->moverX(false,dt);
            olhandoEsquerda = true;
            animacao = Animation_ID::walk;
        }
 
        if(pJ2){
            if(andDir2){
                pJ2->moverX(true,dt);
                olhandoEsquerda2 = false;
                animacao2 = Animation_ID::walk;
            }
            if(andEsq2){
                pJ2->moverX(false,dt);
                olhandoEsquerda2 = true;
                animacao2 = Animation_ID::walk;
            }
        }
 
        if(!pJ1->noChao()){animacao = Animation_ID::jump;}
 
        if(pJ1->getAtacando()){animacao = Animation_ID::attack;}
 
        pJ1->atualizarGolpe(dt);
 
        if(pJ2){
            if(!pJ2->noChao()){
                animacao2 = Animation_ID::jump;
 
            }
            pJ2->atualizarGolpe(dt);
            if(pJ2->getAtacando()){animacao2 = Animation_ID::attack;}
        }
 
        executarInimigos(vInimigos, pJ1, pJ2, dt);

        pGC->executar(dt);

        pGG->clear();
        background->render();
        list_ents.percorrer(dt);
        this->checarInimigos();
        
        if(pJ1->getInvulneravel()){
            animacao = Animation_ID::hurt;
        }
        if(pJ2!=NULL&&pJ2->getInvulneravel()){
            animacao2 = Animation_ID::hurt;
        }
        
        pJ1->atualizarAnimacao(animacao, olhandoEsquerda, dt);
        pJ1->desenhar();
        //desenharAreaColisao(pGG->getWindow(), pJ1->getPos(), 32.f);
 
        if(pJ2){
            pJ2->atualizarAnimacao(animacao2, olhandoEsquerda2, dt);
            pJ2->desenhar();
        }
 
        pGG->getWindow()->display();
 
    }
}
}
