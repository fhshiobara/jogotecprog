//
//  FasePrimeira.hpp
//  main
//
//  Created by Edison Shiobara on 09/06/26.
//

#ifndef FasePrimeira_hpp
#define FasePrimeira_hpp
#include <stdio.h>
#include "Fase.hpp"
#include "Demonio.hpp"
#include "Arvore.hpp"

namespace Fases{

class FasePrimeira:public Fase{
private:
    const int max_inim_medio;
    const int max_obst_medio;
    
protected:
    void criar_inim_medio();
    void criar_obst_medio();
    
public:
    FasePrimeira();
    ~FasePrimeira();
    void executar();
    
    void criarInimigos();
    void criarObstaculos();
};
}

#endif /* FasePrimeira_hpp */
