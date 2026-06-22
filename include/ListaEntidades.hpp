#ifndef LISTAENTIDADES_HPP
#define LISTAENTIDADES_HPP
#pragma once
#include "ListTL.hpp"
#include "Entidade.hpp"

class ListaEntidades {
    
private:
    Lista <Entidades::Entidade> LEs;
    
public:
    ListaEntidades();
    ~ListaEntidades();
    
    void incluir(Entidades::Entidade* pE);
    
    void remover(Entidades::Entidade* pE);
    void percorrer();
    void percorrer(float dt);
};
 
#endif
