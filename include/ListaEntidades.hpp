#ifndef LISTAENTIDADES_HPP
#define LISTAENTIDADES_HPP
 
#include "Entidade.hpp"
#include <list>
#include <iostream>
 
class ListaEntidades {
    private:
        std::list<Entidades::Entidade*> LEs;
    public:
        ListaEntidades();
        ~ListaEntidades();
        void incluir(Entidades::Entidade* pE);
        void percorrer();
};
 
#endif
