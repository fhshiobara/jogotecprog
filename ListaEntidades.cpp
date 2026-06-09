#include "ListaEntidades.hpp"

ListaEntidades:: ListaEntidades(){}

ListaEntidades:: ~ListaEntidades(){}

void ListaEntidades::incluir(Entidades::Entidade* pE){
    
    LEs.incluir(pE);
}

void ListaEntidades::percorrer(){
    LEs.percorrer();
    
}
