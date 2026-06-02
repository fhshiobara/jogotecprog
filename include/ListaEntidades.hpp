//
//  ListaEntidades.hpp
//  Jogo
//
//  Created by Edison Shiobara on 02/06/26.
//

#include "Entidade.hpp"
#include "List.hpp"
#include <iostream>

class ListaEntidades{
private:
    Lista<Entidade> LEs;
public:
    ListaEntidades();
    ~ListaEntidades();
    void incluir(Entidade* pE);
    void percorrer();
    //classes da uml base
    
};

