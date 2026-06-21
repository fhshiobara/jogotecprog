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

Fase::Fase():pGC(Gerenciadores::GerenciadorColisoes::getInstance()),Max_inimBixo(4),tam_tela(800,600),num_max_Plataformas(rand()%10),concluida(false), pontosTotais(0) {
    vPlats.clear();
    vInimigos.clear();
    if(num_max_Plataformas<8){num_max_Plataformas=8;}//estabelece um valor minimo de plataformas

        sf::Font* fonte = pGG->getFont();

    if(fonte != NULL){

        pontosTexto.setFont(*fonte);
        pontosTexto.setCharacterSize(24);
        pontosTexto.setFillColor(sf::Color::White);
        pontosTexto.setPosition(sf::Vector2f(10.f, 10.f)); // canto superior esquerdo
        pontosTexto.setString("Pontos: 0");

    }
}

Fase::~Fase(){
    for(int i = 0; i < vPlats.size(); i++) {
            delete vPlats[i];
        }
        vPlats.clear();
    delete telaDerrota;
    telaDerrota = NULL;
}

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

/* Func acima serve para criar Listas e depois inserir em Ents_List. 
Como a ordem de Ent_list define quem desenha quando, isso nos permite 
desenhar as plataformas depois dos espinhos, mesmo com elas ja estando instanciadas.
Deixa o jogo mais bonito, sem espinhos flutuantes */

Animation_ID Fase::decidirAnimacao(Personagens::Jogador* pJog, bool andando) {
    if (pJog->getInvulneravel())  return Animation_ID::hurt;
    if (pJog->getAtacando())      return Animation_ID::attack;
    if (!pJog->noChao())          return Animation_ID::jump;
    if (andando)                  return Animation_ID::walk;
    return Animation_ID::idle;
}
// Func acima define a prioridade das animacoes, assim ela nao sao sobreescritas no loop principal

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

            mapa.setOcupado(espaco, false);

            list_ents.incluir(pInim);
            pGC->incluirInimigo(pInim);
        }
    }
}

void Fase::criarLimites(){
    pGC->setLimite(tam_tela);
}

void Fase::checarInimigos(Personagens::Jogador* pJ1, Personagens::Jogador* pJ2){

    std::vector<Personagens::Inimigo*>::iterator it = vInimigos.begin();

    while(it != vInimigos.end()){
            if((*it)->setVivo()){//ignora
                // std::cout << "Inimigo HP/Vivo: " <<  << std::endl;
                it++;
                
            } else { //nao vivo
                Personagens::Inimigo* morto = *it;

                Personagens::Jogador* pontuador = pJ1;

                if (pJ2 != NULL && morto->jogadorProximo(pJ1, pJ2))
                    pontuador = pJ2;
                morto->concederPontos(pontuador);

                somarPontos(morto->getValorPontos()); // mantem o placar total da fase
                atualizarTextoPontos();

                pGC->removerInimigo(morto);
                list_ents.remover(morto);    
                it = vInimigos.erase(it);   
                 
                delete morto; 
            }
        if(vInimigos.empty()){
            std::cout<<"Vetor de inimigos esta vazio, settando fase como concluida"<<std::endl;
            setConcluida(true);
        }
        }
    
    }

void Fase::setConcluida(bool conc){
    concluida = conc;
}

bool Fase::getConcluida(){
    return concluida;
}

void Fase::atualizarTextoPontos(){
    pontosTexto.setString("Pontos: " + std::to_string(pontosTotais)); // Preciso transformar em String para o sf::Font funcionar
}

void Fase::desenharPontos(){
    pGG->render(&pontosTexto);
}

void Fase::executarInimigos(std::vector<Personagens::Inimigo*> &vInimigos, Personagens::Jogador* pJ1, Personagens::Jogador* pJ2, float dt) {

    if(pJ2 == NULL) {
        CoordF posJogador1 = pJ1->getPos();

    for(Personagens::Inimigo* inimigo : vInimigos) {
        inimigo->perseguir(posJogador1, dt);
    }
        return;
        
    } else {

        CoordF posJogador1 = pJ1->getPos();
        CoordF posJogador2 = pJ2->getPos();

        for(Personagens::Inimigo* inimigo : vInimigos) {

            bool jogadorMaisProx = inimigo->jogadorProximo(pJ1, pJ2);

            if(jogadorMaisProx)
                inimigo->perseguir(posJogador2, dt);
            else 
                inimigo->perseguir(posJogador1, dt);
            }
        }
    }
}
