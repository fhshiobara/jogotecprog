#include "Jogo.hpp"
#include "Demonio.hpp"
#include "Bixo.hpp"
#include "Morte.hpp"
#include "Plataforma.hpp"
#include "GerenciadorColisoes.hpp"
#include "Espinhos.hpp"
#include "SingleFrameAnimation.hpp"
#include "Limites.hpp"

using namespace Obstaculos;
using namespace Personagens;
 
Jogo::Jogo() : pGerenciadorGrafico(Gerenciadores::GerenciadorGrafico::getInstance()),pJ1(NULL),pJ2(NULL),pFase1(NULL),pGC(Gerenciadores::GerenciadorColisoes::getInstance()) {
    srand((unsigned)time(NULL));
    executar(); }
 
Jogo::~Jogo() {
    delete pFase1;
    delete pJ1;
    delete pJ2;
    
}
 
void Jogo::executar() {
    
    pJ1 = new Personagens::Jogador(CoordF(200.f,200.f),3,0,200.f);
    
    pJ2 = new Personagens::Jogador(CoordF(240.f,200.f),3,0,200.f);
    std::cout<<"chamando initialize"<<std::endl;
    pJ1->initialize(true);
    pJ2->initialize(false);
    std::cout<<"initialize concluido"<<std::endl;
    pFase1 = new Fases::FasePrimeira();
    pFase1->executar(pJ1,pJ2);
}
