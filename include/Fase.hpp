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

namespace Fases{
class Fase:public Ente{
protected:
    ListaEntidades list_ents;
    Gerenciadores::GerenciadorColisoes* pGC;
    short int Max_inimArvore;
public:
    Fase();
    ~Fase();
    
    virtual void executar()=0;

    
protected:
    void criarInimigosArvore();//inimigos faceis
    void criarPlataformas();
    //funcoes extra vem aqui
    virtual void criarInimigos() =0;
    virtual void criarObstaculos() =0;
    void criarCenario();
    //void criarDemonios();
    
    
    
};
}


#endif
