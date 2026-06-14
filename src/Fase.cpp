//
//  Fase.cpp
//  Jogo
//
//  Created by Edison Shiobara on 08/06/26.
//
#include "Fase.hpp"
#include "SingleFrameAnimation.hpp"
#include "Plataforma.hpp"
#include "Demonio.hpp"
#include "Arvore.hpp"
#define MAX 3

namespace Fases{

Fase::Fase():pGC(Gerenciadores::GerenciadorColisoes::getInstance()),Max_inimArvore(4),tam_tela(800,600),num_max_Plataformas(rand()%10){
    vPlats.clear();
    if(num_max_Plataformas<6){num_max_Plataformas=6;}//estabelece um valor minimo de plataformas
}


Fase::~Fase(){}



void Fase::criarPlataformas(){
    
    for(int i=0;i<num_max_Plataformas;i++){
        Plataforma* pPlat = NULL;
        pPlat = new Plataforma(CoordF(rand()%800,rand()%300+150),rand()%100+80,20.0f); // precisamos randomizar isso depois
        
        if(pPlat!=NULL){
            list_ents.incluir(pPlat);
            vPlats.push_back(pPlat);
            
            pGC->incluirObstaculo(pPlat);
            
            pPlat->desenhar();
            
            
        }
        else{
            std::cerr << "ERRO: Alocacao falha de plataforma em Fase::criarPlataformas" << std::endl;
        }
        
    }   
}

void Fase::criarCenario(){
}

void Fase::criarInimigosArvore(){  // mudar para inimigos faceis
    
    for(int i=0; i<Max_inimArvore;i++){ //quantidade padrao é 3
        Arvore* pInim = NULL;
        pInim = new Arvore(CoordF(0.0f,0.0f)); //os parametros podem ser mudados aqui para alterar a dificuldade
        if(pInim !=NULL){
            list_ents.incluir(pInim);
        }
        else{std::cerr << "ERRO: falha na criacao do inimigo Facil" << std::endl;}
    }
    

}

void Fase::criarLimites(){
    pGC->setLimite(tam_tela.x,tam_tela.y);
    
    
}
}
