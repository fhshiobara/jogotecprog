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
    if(num_max_Plataformas<8){num_max_Plataformas=8;}//estabelece um valor minimo de plataformas
}


Fase::~Fase(){}



void Fase::criarPlataformas(){
    
    int num_Plataformas =0;
    int larg_min = 120; //largura minima de uma plataforma
    int alt_min = 20; //altura
    while(num_Plataformas<num_max_Plataformas){
        int aux = rand()%9; // numero precisa ser até 8 no primeiro modelo
        Grid espaco = static_cast<Grid>(aux);
        
        
        if(!mapa.estaOcupado(espaco)){
            CoordF pos = mapa.getCoord(espaco);
            
            Plataforma* plat = NULL;
            plat = new Plataforma(pos,larg_min+rand()%31,alt_min+rand()%11);
            
            if(plat!=NULL){
                num_Plataformas++;
                mapa.setOcupado(espaco,true);
                vPlats.push_back(plat);
                list_ents.incluir(plat);
                pGC->incluirObstaculo(plat); //acredito que tenha dado certo
                plat->desenhar();
            }
            else{
                std::cerr<<"Erro: na alocacao da plataforma"<<std::endl;
            }
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
            pInim->desenhar();
        }
        else{std::cerr << "ERRO: falha na criacao do inimigo Facil" << std::endl;}
    }
    

}

void Fase::criarLimites(){
    pGC->setLimite(tam_tela.x,tam_tela.y);
    
    
}
}
