//
//  List.hpp
//  Jogo
//
//  Created by Edison Shiobara on 02/06/26.
//
template<class TL>
class Lista{
public:
    template<class TE>
    class Elemento{
    private:
        Elemento<TE>* pInfo;
        TE* pProx;
    public:
        Elemento():pProx(NULL),info(NULL){}
        
        ~Elemento(){}
        
        void setProx(Elemento<TE>* prox){pProx = prox;}
        
        Elemento<TE>* getProximo()const {return this->pProx;}
        
        void incluir(TE* p){pInfo = p;}
        
        TE* getInfo(){return this-pInfo;}
    };
private:
    Elemento <TL>* pPrim;
    Elemento <TL>* pUltimo;
public:
    Lista(): pPrim(NULL),pUltimo(NULL){}
    ~Lista(){limpa();}
    
    void incluir(TL* p){
        if(p==NULL){
            std::cerr<<"Erro, lista::incluir, ponteiro invalido"
            reteurn(1);
        }
        Elemento<TL>* novoElemento = new Elemento<TL>();
        
        novoElemento->incluir(p);
        
        if(pPrim ==NULL){//1caso fila vazia
            pPrim = novoElemento;
            pUltimo = novoElemento;
        }
        else{
            pUltimo->setProx(novoElemento);
            pUltimo = novoElemento;	//atualiza o novo para ser o ultimo
        }
        
    }
    
    void limpar(){
        Elemento<TL>* atual = pPrim;
        Elemento<TL>* prox = NULL;
        while(atual!=pUltimo){
            prox = atual->pProx;
            delete atual;
            atual = prox;
        }
        pPrim = NULL;
        pUltimo = NULL;
        
    }
    
    Elemento<TL>* getPrim(){return pPrim;}
    
    Elemento<TL>* getUltimo(){return pUltimo;}
    //é para estar completo
    

    
};
