//
//  FasePrimeira.cpp
//  main
//
//  Created by Edison Shiobara on 09/06/26.
//

#include "FasePrimeira.hpp"
#include "Espinhos.hpp"

using namespace Personagens;

namespace Fases{

FasePrimeira::FasePrimeira():Fase(),max_inim_Demonio(4),max_obst_Espinhos(4),background(NULL){
    background = new Gerenciadores::SingleFrameAnimation("assets/background.png",CoordF(0.f,0.f),CoordF(800.f,600.f),1.0);
}

FasePrimeira::~FasePrimeira(){}

void FasePrimeira::criarInimigosDemonio(){
    int num_inim_medio = rand()%(max_inim_Demonio +1);
    
    if(num_inim_medio<3){num_inim_medio =3;} //numero minimo de inimigos
    
    int num_demonios_criados = 0;
    
    while(num_demonios_criados<num_inim_medio){
        int aux = rand()%9;
        Grid espaco = static_cast<Grid>(aux);
        if(mapa.estaOcupado(espaco)){
            CoordF pos = mapa.getCoord(espaco);
            pos.y = pos.y-30;
            Demonio* pDemo = NULL;
            pDemo = new Demonio(pos,2,60.f,1.0);
            
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
            pos.y=pos.y- alt_min/2;
            
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
    
    pGC->setJogador(pJ1);
    if(pJ2){
        pGC->setJogador(pJ2);
    }
    
    pGC->setLimite(tam_tela.x,tam_tela.y-10);
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
                
                
                if(pJ2){
                    if(evento.key.code == sf::Keyboard::Right){andDir2=true;}
                    if(evento.key.code == sf::Keyboard::Left){andEsq2=true;}
                    if(evento.key.code == sf::Keyboard::Up){pJ2->pular();}
                }
                
                
            }
            if(evento.type == sf::Event::KeyReleased){
                
                if(evento.key.code == sf::Keyboard::D){andDir=false;}
                if(evento.key.code == sf::Keyboard::A){andEsq=false;}
                
                if(pJ2){
                    if(evento.key.code == sf::Keyboard::Right){andDir2=false;}
                    if(evento.key.code == sf::Keyboard::Left){andEsq2=false;}
                    
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
        
        if(pJ2){
            if(!pJ2->noChao()){
                animacao2 = Animation_ID::jump;
            }
        }
        // Inimigos
        if(pJ2 != NULL)
            executarInimigos(vInimigos, pJ1->getPos(), pJ2->getPos(), dt);
        else
            executarInimigos(vInimigos, pJ1->getPos(), pJ1->getPos(), dt);

        pGC->executar(dt);
        pGG->clear();
        background->render();
        list_ents.percorrer(dt);
        
        pJ1->atualizarAnimacao(animacao, olhandoEsquerda, dt);
        pJ1->desenhar();
        if(pJ2){
            pJ2->atualizarAnimacao(animacao2,olhandoEsquerda2,dt);
            pJ2->desenhar();
        }
        pGG->getWindow()->display();
        
    }
    
}


}