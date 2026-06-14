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
#include "SingleFrameAnimation.hpp"

namespace Fases{

class FasePrimeira:public Fase{
private:
    const int max_inim_Demonio;
    const int max_obst_Espinhos;
    Gerenciadores::SingleFrameAnimation* background;
    
protected:
    void criar_inim_Demonio();
    void criar_obst_Espinhos();
    
public:
    FasePrimeira();
    ~FasePrimeira();
    void executar(Jogador* pJog);
    void executar();
    
    void criarInimigos();
    void criarObstaculos();
};
}

#endif /* FasePrimeira_hpp */
