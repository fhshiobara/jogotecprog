//
//  FasePrimeira.cpp
//  main
//
//  Created by Edison Shiobara on 09/06/26.
//

#include "FasePrimeira.hpp"
#include "Obst_Medio.hpp"

namespace Fases{

FasePrimeira::FasePrimeira():Fase(),max_inim_Demonio(4),max_obst_Espinhos(4),background(NULL){
    background = new Gerenciadores::SingleFrameAnimation("../assets/background.png",CoordF(0.f,0.f),CoordF(800.f,600.f),1.0);
}

FasePrimeira::~FasePrimeira(){}

void FasePrimeira::criar_inim_Demonio(){
    int num_inim_medio = rand()%(max_inim_Demonio +1);
    
    if(num_inim_medio<3){num_inim_medio =3;} //numero minimo de inimigos
    if(vPlats.empty()){
        std::cerr<<"Erro: nenhuma plataforma disponivel"<<std::endl;
    }
    
    for(int i = 0;i<num_inim_medio;i++){
        Demonio* pInim = NULL;
        
        Plataforma* plat = NULL;
        
        
        
        if(plat==NULL){
            plat = vPlats[rand()%vPlats.size()];
            
        }
        else{
            std::cout<<"Falha em sortear uma plataforma para criacao de Demonio"<<std::endl;
        }
        int largura = (int)(plat->getDireita() - plat->getEsquerda()); //define a largura da plataforma sorteada
        pInim = new Demonio(CoordF(plat->getEsquerda()+ rand()% largura,plat->getTopo()-60),3,60.f,rand()%2);//aleatoriza a fome do demonio para dar variedade //os parametros podem ser mudados aqui para alterar a dificuldade// esse -60 é referente a altura estimada do inimigo
        if(pInim !=NULL){
            list_ents.incluir(pInim);
            pGC->incluirInimigo(pInim);
        }
        else{std::cerr << "ERRO: falha na alocacao do inimigo medio" << std::endl;}
    }
    
    
}

void FasePrimeira::criar_obst_Espinhos(){
    
    float alt_min = 50;
    float larg_min = 80;
    int num_obst_medio = rand()%(max_obst_Espinhos + 1);
    
    if(num_obst_medio<3){num_obst_medio = 3;} //numero minimo de obstaculos
    
    
    for(int i = 0;i<num_obst_medio;i++){
        Obstaculos::Obst_Medio* pObs = NULL;
        Plataforma* plat = NULL;
        if(plat==NULL){
            plat = vPlats[rand()%vPlats.size()]; // escolhe uma plataforma aleatoria do vector derivado da Fase
            pObs = new Obstaculos::Obst_Medio(CoordF(plat->getEsquerda()+(rand()%(int)plat->getDireita()-80),plat->getTopo()-40), alt_min + rand()%10, larg_min + rand()%20, 0.85);
            
        }
        
        
        if(pObs!= NULL){
            list_ents.incluir(pObs);
            pGC->incluirObstaculo(pObs);
        }
        else{
            std::cerr<<"ERRO: falha na alocacao do ponteiro do objeto medio em FASE Primeira"<<std::endl;
        }

    }
    
    
    
    
}

void FasePrimeira::criarInimigos(){
    criarInimigosArvore();
    criar_inim_Demonio();
    
    
}

void FasePrimeira::criarObstaculos(){
    criar_obst_Espinhos();
}
void FasePrimeira::executar(){}

void FasePrimeira::executar(Jogador* pJog){
    if(pGC==NULL || pJog==NULL){
        
        std::cerr<<"ERRO: pGC nao foi inicializado"<<std::endl;
        return;
    }
    criarCenario();
    criarPlataformas();
    criarInimigos();
    criarObstaculos();
    
    pGC->setJogador(pJog);
    
    pGC->setLimite(tam_tela.x,tam_tela.y-10);
    list_ents.incluir(pJog);
    
    sf::Clock clock;
    //setando o jogador
    bool andDir = false;
    bool andEsq = false;
    bool olhandoEsquerda = false;
    Animation_ID animacao = Animation_ID::idle;
    
    pGG = Gerenciadores::GerenciadorGrafico::getInstance();
    
    while(pGG->windowopen()){
        
        float dt = clock.restart().asSeconds();
        
        sf::Event evento;
        while(pGG->getWindow()->pollEvent(evento)){
            if(evento.type==sf::Event::Closed){pGG->closeWindow();}
            
            if(evento.type ==sf::Event::KeyPressed){
                if(evento.key.code == sf::Keyboard::D){andDir=true;}
                if(evento.key.code == sf::Keyboard::A){andEsq=true;}
                if(evento.key.code == sf::Keyboard::Space){pJog->pular();}
            }
            if(evento.type == sf::Event::KeyReleased){
                
                if(evento.key.code == sf::Keyboard::D){andDir=false;}
                if(evento.key.code == sf::Keyboard::A){andEsq=false;}
            }
            
        }
        animacao = Animation_ID::idle;
        
        if(andDir){
            pJog->moverX(true,dt);
            olhandoEsquerda = false;
            animacao = Animation_ID::walk;
        }
        if(andEsq){
            pJog->moverX(false,dt);
            olhandoEsquerda = true;
            animacao = Animation_ID::walk;
        }
        
        if(!pJog->noChao()){animacao = Animation_ID::jump;}
        
        pGC->executar(dt);
        
        pGG->clear();
        background->render();
        list_ents.percorrer();
        
        pJog->atualizarAnimacao(animacao, olhandoEsquerda, dt);
        pJog->desenhar();
        pGG->getWindow()->display();
        
        
        
        
        
        
        
    }
    
}


}
