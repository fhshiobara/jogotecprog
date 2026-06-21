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

    void coordUsada(CoordF coord) {
            for (auto& par : CoordGrid) {
                if (par.second.x == coord.x && par.second.y == coord.y) {
                    CoordUsado[par.first] = true;
                    return; // achou, pode sair
                }
            }
            //se chegar aqui, a coordenada não existe no grid
        }

    
        bool estaOcupado(Grid espaco) {
            return CoordUsado[espaco];
        }


        CoordF getCoord(Grid espaco) {
            return CoordGrid[espaco];
        }

        //controle manual, aceita true ou false
        void setOcupado(Grid espaco, bool ocupado) {
            CoordUsado[espaco] = ocupado;
        }
};
    
namespace Fases {
    class Fase: public Ente {
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

            int pontosTotais;
            sf::Text pontosTexto;
        
            SingleFrameAnimation* telaDerrota;

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
            void checarInimigos(Personagens::Jogador* pJ1, Personagens::Jogador* pJ2);
            void executarInimigos(std::vector<Personagens::Inimigo*> &vInimigos, Personagens::Jogador* pJ1, Personagens::Jogador* pJ2, float dt);
            void inserirPlataformasAtrasado(); // Func auxiliar
        
            Animation_ID decidirAnimacao(Personagens::Jogador* pJog, bool andando); // Func auxiliar

            void desenharPontos(); 
        
        public:
            void setConcluida(bool conc);
            bool getConcluida();
            void somarPontos(int pontos) { pontosTotais += pontos; }
            int getPontosTotais() { return pontosTotais; }
            void atualizarTextoPontos(); 
            
        };
}


#endif
