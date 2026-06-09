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
    Gerenciadores::GerenciadorColisoes* pGG;
public:
    Fase();
    ~Fase();
    
    virtual void executar() =0;
    
protected:
    void criarInimigosFaceis();
    void criarPlataformas();
    
    virtual void criarInimigos() =0;
    virtual void criarObstaculos() =0;
    void criarCenario();
    void criarInimigosMedios();
    
    
    
    
};
}


#endif