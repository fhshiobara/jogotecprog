//
//  ListTL.hpp
//  Jogo
//
//  Created by Edison Shiobara on 02/06/26.
//
#ifndef LISTTL_HPP
#define LISTTL_HPP
 
#include <iostream>
 
template<class TL>
class Lista {
public:
    class Elemento {
    private:
        TL*        pInfo;  // ponteiro para o DADO
        Elemento*  pProx;  // ponteiro para o PRÓXIMO elemento
    public:
        Elemento() : pInfo(NULL), pProx(NULL) {}
        ~Elemento() {}
 
        void setProx(Elemento* prox) { pProx = prox; }
        Elemento* getProximo() const      { return pProx; }
 
        void incluir(TL* p) { pInfo = p; }
        TL* getInfo()      { return pInfo; }
    };
 
private:
    Elemento* pPrim;
    Elemento* pUltimo;
 
public:
    Lista() : pPrim(NULL), pUltimo(NULL) {}
    ~Lista() { limpar(); }
 
    void incluir(TL* p) {
        if (p == NULL) {
            std::cerr << "Erro, Lista::incluir, ponteiro invalido" << std::endl;
            return;
        }
 
        Elemento* novoElemento = new Elemento();
        novoElemento->incluir(p);
 
        if (pPrim == NULL) {
            pPrim   = novoElemento;
            pUltimo = novoElemento;
        } else {
            pUltimo->setProx(novoElemento);
            pUltimo = novoElemento;
        }
    }
 
    void limpar() {
        Elemento* atual = pPrim;
        Elemento* prox  = NULL;
        while (atual != NULL) {       // era != pUltimo — perdia o último
            prox = atual->getProximo();
            delete atual;
            atual = prox;
        }
        pPrim   = NULL;
        pUltimo = NULL;
    }
    
    void percorrer(){
        Elemento* patual = pPrim;
        while(patual!=NULL){
            patual->getInfo()->executar();
            patual= patual->getProximo();
        }
        
    }
    
    void percorrer(float dt){
        Elemento* pAtual = pPrim;
        while(pAtual!=NULL){
            pAtual->getInfo()->setDt(dt);
            pAtual->getInfo()->executar();
            pAtual = pAtual->getProximo();
        }
    }
    
    void remover(TL *p) {
            if (p == NULL || pPrim == NULL) return; //lista vazia ou ponteiro nulo

            Elemento* atual = pPrim;
            Elemento* anterior = NULL;

            
            while (atual != NULL && atual->getInfo() != p) {
                anterior = atual;
                atual = atual->getProximo();
            }

            if (atual == NULL) return;

            
            if (atual == pPrim) {
                pPrim = pPrim->getProximo();
                if (pPrim == NULL) {
                    pUltimo = NULL;
                }
            }
    
            else {
                anterior->setProx(atual->getProximo());
                if (atual == pUltimo) {
                    pUltimo = anterior;
                }
            }


            delete atual;
        }
    
 
    Elemento* getPrim()   { return pPrim; }
    Elemento* getUltimo() { return pUltimo; }
};
 
#endif
