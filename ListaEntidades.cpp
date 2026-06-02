//
//  ListaEntidades.cpp
//  main
//
//  Created by Edison Shiobara on 02/06/26.
//
#pragma once
#include <stdio.h>

#include "ListaEntidades.hpp"

ListaEntidades(){}

~ListaEntidades(){}
//construtora e destrutora

void ListaEntidades::incluir(Entidade* pE){
    if(pE!=NULL){LEs.incluir(pE);}
    else {
        std::cerr<<"Erro: ListaEntidades::incluir, ponteiro nulo"<<std::endl;
        return 1;
    }
    
}




