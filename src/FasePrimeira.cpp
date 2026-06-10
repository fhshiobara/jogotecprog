//
//  FasePrimeira.cpp
//  main
//
//  Created by Edison Shiobara on 09/06/26.
//

#include "FasePrimeira.hpp"
#include "Obst_Medio.hpp"

namespace Fases{

FasePrimeira::FasePrimeira():max_inim_medio(4),max_obst_medio(4){ }

FasePrimeira::~FasePrimeira(){}

void FasePrimeira::criar_inim_medio(){
    int num_inim_medio = rand()%(max_inim_medio +1);
    
    if(num_inim_medio<3){num_inim_medio =3;} //numero minimo de inimigos
    
    for(int i = 0;i<num_inim_medio;i++){
        Demonio* pInim = NULL;
        pInim = new Demonio(CoordF(0.0f,0.0f)); //os parametros podem ser mudados aqui para alterar a dificuldade
        if(pInim !=NULL){
            list_ents.incluir(pInim);
        }
        else{std::cerr << "ERRO: falha na alocacao do inimigo medio" << std::endl;}
    
    }
}

void FasePrimeira::criar_obst_medio(){
    int num_obst_medio = rand()%(max_obst_medio + 1);
    
    if(num_obst_medio<3){num_obst_medio = 3;} //numero minimo de obstaculos
    
    
    for(int i = 0;i<num_obst_medio;i++){
        Obstaculos::Obst_Medio* pObj = NULL;
        pObj = new Obstaculos::Obst_Medio(CoordF(0.0f, 0.0f),30.0f, 50.0f, 0.1f); //posicao/altura/ largura/ viscosidade
        
        if(pObj!= NULL){
            list_ents.incluir(pObj);
        }
        else{
            std::cerr<<"ERRO: falha na alocacao do ponteiro do objeto medio em FASE Primeira"<<std::endl;
        }

    }
    
    
    
    
}

void FasePrimeira::criarInimigos(){
    criar_inim_medio();
    
    
}

void FasePrimeira::criarObstaculos(){
    criar_obst_medio();
}

void FasePrimeira::executar(){
    
    this->criarCenario();
    this->criarPlataformas();
    this->criarInimigos();
    this->criarObstaculos();
    
    list_ents.percorrer();
    
}


}
