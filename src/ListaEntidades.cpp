#include "ListaEntidades.hpp"

ListaEntidades:: ListaEntidades(){}

ListaEntidades:: ~ListaEntidades(){}

void ListaEntidades::incluir(Entidades::Entidade* pE){
    
    LEs.incluir(pE);
}

void ListaEntidades::percorrer(){
    LEs.percorrer();
}

void ListaEntidades::percorrer(float dt){
    LEs.percorrer(dt);
}

void ListaEntidades::remover(Entidades::Entidade* pE){
    LEs.remover(pE);
}


