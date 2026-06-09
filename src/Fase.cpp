//
//  Fase.cpp
//  Jogo
//
//  Created by Edison Shiobara on 08/06/26.
//
#include "Fase.hpp"
#include "SingleFrameAnimation.hpp"
#include "Plataforma.hpp"
#include "Inimigo_Medio.hpp"
#define MAX 3

namespace Fases{

Fase::Fase():pGG(Gerenciadores::GerenciadorColisoes::getInstance()){}


Fase::~Fase(){}

void Fase::criarInimigosFaceis(){
    //TODO
}

void Fase::criarPlataformas(){
    
    for(int i=0;i<3;i++){
        Plataforma* pPlat = NULL;
        pPlat = new Plataforma(CoordF(0.0f,0.0f),100.0f,20.0f); // precisamos randomizar isso depois
        
        if(pPlat!=NULL){
            list_ents.incluir(pPlat);
            pPlat->desenhar();
            
        }
        else{
            std::cerr << "ERRO: Alocacao falha de plataforma em Fase::criarPlataformas" << std::endl;
        }
        
    }   
}

void Fase::criarCenario(){
    Gerenciadores::SingleFrameAnimation* imagemFundo = NULL;
    imagemFundo = new Gerenciadores::SingleFrameAnimation("assets/background.png",CoordF(0.0f,0.0f),CoordF(800.0f,600.0f),0.79);
    
    imagemFundo->render();
    
}

void Fase::criarDemonios(){  // mudar para inimigos faceis 
    
    for(int i=0; i< MAX;i++){ //quantidade padrao é 3
        Demonio* pInim = NULL;
        pInim = new Demonio(CoordF(0.0f,0.0f)); //os parametros podem ser mudados aqui para alterar a dificuldade
        if(pInim !=NULL){
            list_ents.incluir(pInim);
        }
        else{std::cerr << "ERRO: falha na criacao do inimigo medio" << std::endl;}
    }
    

}
}