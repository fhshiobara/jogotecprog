//
//  Fase.hpp
//  Jogo
//
//  Created by Edison Shiobara on 08/06/26.
//

#ifndef Fase_hpp
#define Fase_hpp

#include "Ente.hpp"
#include "ListaEntidades.hpp"
#include "GerenciadorColisoes.hpp"
#include <vector>
#include "Plataforma.hpp"
#include <map>


enum Grid{
  T1=0,T2=1,T3=2, //top
  M1=3,M2=4,M3=5,//meio
  B1=6,B2=7,B3=8 //Baixo
    
};



class Map{
private:
    std::map<Grid,CoordF> CoordGrid;
    std::map<Grid,bool> CoordUsado;
    
public:
    Map() {
        CoordGrid[T1] = CoordF(0.f, 120.f);
        CoordGrid[T2] = CoordF(270.f, 160.f);
        CoordGrid[T3] = CoordF(570.f, 180.f);
        CoordGrid[M1] = CoordF(0.f, 350.f);
        CoordGrid[M2] = CoordF(310.f, 360.f);
        CoordGrid[M3] = CoordF(640.f, 330.f);
        CoordGrid[B1] = CoordF(35.f, 450.f);
        CoordGrid[B2] = CoordF(190.f, 500.f);
        CoordGrid[B3] = CoordF(620.f, 470.f);

        CoordUsado[T1] = false; CoordUsado[T2] = false; CoordUsado[T3] = false;
        CoordUsado[M1] = false; CoordUsado[M2] = false; CoordUsado[M3] = false;
        CoordUsado[B1] = false; CoordUsado[B2] = false; CoordUsado[B3] = false;
    }

    void CoordUsada(CoordF coord) {
        std::map<Grid, CoordF>::iterator it = CoordGrid.begin();

        while (it != CoordGrid.end() && (coord.x != it->second.x || coord.y != it->second.y)) {
            it++;
        }

        if (it != CoordGrid.end()) {
            //se entrou aqui é porque achou a coordenada
            CoordUsado[it->first] = true;
        }
    }
    
    bool estaOcupado(Grid espaco){
        return CoordUsado[espaco];
    }
    CoordF getCoord(Grid espaco){
        return CoordGrid[espaco];
    }
    
    
    void setOcupado(Grid espaco, bool ocupado){
        CoordUsado[espaco] = ocupado; //permite configurar um slot diretamente
    }
};
    
namespace Fases{
class Fase:public Ente{
protected:
    ListaEntidades list_ents;
    Gerenciadores::GerenciadorColisoes* pGC;
    short int Max_inimBixo;
    CoordF tam_tela;
    std::vector<Plataforma*> vPlats;
    std::vector<Personagens::Inimigo*> vInimigos;
    int num_max_Plataformas;
    bool concluida;
    Map mapa;
public:
    Fase();
    ~Fase();
    
    virtual void executar()=0;

    
protected:
    void criarInimigosBixo();//inimigos faceis
    void criarPlataformas();
    //funcoes extra vem aqui
    virtual void criarInimigos() =0;
    virtual void criarObstaculos() =0;
    void criarCenario();
    void criarLimites();
    //void criarDemonios();
    void executarInimigos(std::vector<Personagens::Inimigo*> vInimigos, Personagens::Jogador* pJ1, Personagens::Jogador* pJ2, float dt);
    void inserirPlataformasAtrasado(); // Func auxiliar
    
};
}


#endif
