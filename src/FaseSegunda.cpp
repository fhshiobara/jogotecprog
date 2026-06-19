//
//  FaseSegunda.cpp
//  main
//
//  Created by Edison Shiobara on 16/06/26.
//

#include "FaseSegunda.hpp"

namespace Fases{

    FaseSegunda::FaseSegunda():max_Morte(4),max_obst_Dificil(5),background(NULL) {
        background = new Gerenciadores::SingleFrameAnimation("../assets/Background/background2.jpg",CoordF(0.f,0.f),CoordF(800.f,600.f),1.0);

    }

    FaseSegunda::~FaseSegunda(){
        delete background;
        background = NULL;
    }

    void FaseSegunda::criaMorte(){
        int num_inim_dificil = rand()%(max_Morte +1);
        
        if(num_inim_dificil<3){num_inim_dificil =3;} //numero minimo de inimigos
        
        int num_morte_criados = 0;
        
        while(num_morte_criados<num_inim_dificil){
            int aux = rand()%9;
            Grid espaco = static_cast<Grid>(aux);
            if(mapa.estaOcupado(espaco)){
                CoordF pos = mapa.getCoord(espaco);

                pos.y = pos.y-30;
                Morte* pMorte = NULL;
                pMorte = new Morte(pos, 5, 10.f);
                
                if(pMorte!=NULL){
                    num_morte_criados++;
                    vInimigos.push_back(pMorte);


                    list_ents.incluir(pMorte);
                    pGC->incluirInimigo(pMorte);
                }
                
                else{
                    std::cerr<<"Falha na alocacao da morte"<<std::endl;
                }
                
            }
        }
        
    }

    void FaseSegunda::criaObstDificil(){
        int num_Gelo = rand()%(max_obst_Dificil +1);
        
        float larg_min = 100;
        
        if(num_Gelo<3){num_Gelo =3;} //numero minimo de inimigos
        
        int num_Gelo_criados = 0;
        
        while(num_Gelo_criados<num_Gelo){
            int aux = rand()%9;
            Grid espaco = static_cast<Grid>(aux);

            if(mapa.estaOcupado(espaco)){
                CoordF pos = mapa.getCoord(espaco);
                pos.y = pos.y-35;

                Obstaculos::Gelo* pGelo = NULL;
                pGelo = new Obstaculos::Gelo(1,pos,larg_min);
                
                if(pGelo!=NULL){
                    num_Gelo_criados++;

                    mapa.setOcupado(espaco, false); // Para nao haver gelos nele mesmo

                    list_ents.incluir(pGelo);
                    pGC->incluirObstaculo(pGelo);
                }
                
                else{
                    std::cerr<<"Falha na alocacao do Gelo"<<std::endl;
                }
                
            }
        }
    }

    void FaseSegunda::criarInimigos(){
        this->criarInimigosBixo();
        this->criaMorte();
    }

    void FaseSegunda::criarObstaculos(){
        this->criaObstDificil();
    }


    void FaseSegunda::executar(){ }


    void FaseSegunda::executar(Personagens::Jogador* pJ1, Personagens::Jogador* pJ2){
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
            if(pJ2 != NULL){
                executarInimigos(vInimigos, pJ1, pJ2, dt);
            }
            else{
                executarInimigos(vInimigos, pJ1, pJ1, dt);
            }

            for (Personagens::Inimigo* inimigo : vInimigos) {
            Personagens::Morte* boss = dynamic_cast<Personagens::Morte*>(inimigo);
                if (boss != NULL && boss->estaVivo())
                    boss->atualizarProjetil(dt);
            } // Trata os projeteis
            
            pGC->executar(dt);
            
            pGG->clear();
            background->render();
            list_ents.percorrer(dt);

            for (Personagens::Inimigo* inimigo : vInimigos) {
            Personagens::Morte* boss = dynamic_cast<Personagens::Morte*>(inimigo);
                if (boss != NULL && boss->estaVivo())
                    boss->desenharProjetil();
            } // mesma coisa, porem desenha

            if(pJ1->getInvulneravel()){
                animacao = Animation_ID::hurt;
            }
            if(pJ2!=NULL && pJ2->getInvulneravel()){
                animacao2 = Animation_ID::hurt;
            }
            std::cout << "cheguei em flag!" << std::endl;
            pJ1->atualizarAnimacao(animacao, olhandoEsquerda, dt);
            pJ1->desenhar();
            if(pJ2){
                pJ2->atualizarAnimacao(animacao2,olhandoEsquerda2,dt);
                pJ2->desenhar();
            }
            
            // if(concluida){
            //     return;
            // }
            pGG->getWindow()->display();   
        }
    }
}
