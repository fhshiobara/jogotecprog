//
//  FaseSegunda.hpp
//  main
//
//  Created by Edison Shiobara on 16/06/26.
//

#ifndef FaseSegunda_hpp
#define FaseSegunda_hpp


#pragma once
#include "Fase.hpp"
#include "Morte.hpp"
#include "Gelo.hpp"
namespace Fases{
class FaseSegunda:public Fases::Fase{
    
private:
    const int max_Morte;
    const int max_obst_Dificil;
    
    Gerenciadores::SingleFrameAnimation* background;
    
public:
    FaseSegunda();
    ~FaseSegunda();
    
    void executar(Jogador* pJ1, Jogador* pJ2);
    
    void executar();
    
    void CriaMorte();
    void CriaObstDificil();
    
    void CriarInimigos();
    void CriarObstaculos();
    
    
};
}


#endif /* FaseSegunda_hpp */
