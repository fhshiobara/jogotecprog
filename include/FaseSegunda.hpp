//
//  FaseSegunda.hpp
//  main
//
//  Created by Edison Shiobara on 16/06/26.
//

#ifndef FASESEGUNDA_hpp
#define FASESEGUNDA_hpp

#include "Fase.hpp"
#include "Morte.hpp"
#include "Gelo.hpp"
namespace Fases{
class FaseSegunda:public Fases::Fase{
    
private:
    const int max_Morte;
    const int max_obst_Dificil;
    
    SingleFrameAnimation* background;

protected:

    void criarInimigoMorte();
    void criarObstaculoGelo();
    
public:
    FaseSegunda();
    ~FaseSegunda();
    
    void executar(Personagens::Jogador* pJ1, Personagens::Jogador* pJ2);
    void executar();
    
    void criarInimigos();
    void criarObstaculos();
};
}


#endif /* FaseSegunda_hpp */
