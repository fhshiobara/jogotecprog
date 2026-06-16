//
//  Fase.cpp
//  Jogo
//
//  Created by Edison Shiobara on 08/06/26.
//
#include "Fase.hpp"
#include "ListaEntidades.hpp"
#include "SingleFrameAnimation.hpp"
#include "Plataforma.hpp"
#include "Demonio.hpp"
#include "Bixo.hpp"
#define MAX 3

using namespace Personagens;

namespace Fases{

Fase::Fase():pGC(Gerenciadores::GerenciadorColisoes::getInstance()),Max_inimBixo(4),tam_tela(800,600),num_max_Plataformas(rand()%10){
    vPlats.clear();
    vInimigos.clear();
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
                pGC->incluirObstaculo(plat); //acredito que tenha dado certo
                plat->desenhar();
            }
            else{
                std::cerr<<"Erro: na alocacao da plataforma"<<std::endl;
            }
        }
    }
}

void Fase::inserirPlataformasAtrasado()
{
    for(Plataforma* plat : vPlats)
    {
        list_ents.incluir(plat);
    }
} 

/* Func serve para criar Listas e depois inserir em Ents_List. 
Como a ordem de Ent_list define quem desenha quando, isso nos permite 
desenhar as plataformas depois dos espinhos, mesmo com elas ja estando instanciadas.
Deixa o jogo mais bonito, sem espinhos flutuantes */


void Fase::criarCenario(){}

void Fase::criarInimigosBixo(){
    std::vector<Grid> espacosOcupados;
    for(int i = 0; i < 9; i++){
        Grid g = static_cast<Grid>(i);
        if(mapa.estaOcupado(g)) espacosOcupados.push_back(g);
    }

    for(int i = 0; i < Max_inimBixo; i++){
        Grid espaco = espacosOcupados[rand() % espacosOcupados.size()];
        CoordF pos = mapa.getCoord(espaco);

        Bixo* pInim = new Personagens::Bixo(pos);
        pos.y = pos.y-40;
        if(pInim != NULL){
            vInimigos.push_back(pInim);
            list_ents.incluir(pInim);
            pGC->incluirInimigo(pInim);
        }
    }
}

void Fase::criarLimites(){
    pGC->setLimite(tam_tela.x,tam_tela.y);
}

void Fase::executarInimigos(std::vector<Personagens::Inimigo*> vInimigos, CoordF posJogador1, CoordF posJogador2, float dt) {
    for (Personagens::Inimigo* inimigo : vInimigos) {
        if(inimigo->jogadorProximo(posJogador1, posJogador2))
            inimigo->perseguir(posJogador2, dt);
        else 
            inimigo->perseguir(posJogador1, dt);
    }
}
}
