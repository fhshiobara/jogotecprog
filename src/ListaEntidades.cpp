#include "ListaEntidades.hpp"
 
ListaEntidades::ListaEntidades() {}
 
ListaEntidades::~ListaEntidades() {}
 
void ListaEntidades::incluir(Entidades::Entidade* pE) {
    if (pE != NULL) {
        LEs.push_back(pE);
    } else {
        std::cerr << "Erro: ListaEntidades::incluir, ponteiro nulo" << std::endl;
    }
}
 
void ListaEntidades::percorrer() {
    for (auto* e : LEs) {
        e->executar();
    }
}
