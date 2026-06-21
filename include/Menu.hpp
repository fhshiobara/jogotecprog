#ifndef MENU_HPP
#define MENU_HPP
 
#include "Ente.hpp"
#include "SingleFrameAnimation.hpp"
#include "Ranking.hpp"

class Jogo;
 
class Menu : public Ente {
    private:
        Jogo* pJogo;

        std::vector<std::string> opcao;
        int selecionada; 
        /* 0 - x, dependendo qual opcao foi selecionada.
        Aqui utilizei a ideia de Sonar Systems em seu video sobre a classe Menu */

        bool multiplayer;   
        bool ativo;            
        int fase;
 
        sf::Text titulo;
        std::vector<sf::Text> textosOpcoes;
        SingleFrameAnimation* cavEsq;
        SingleFrameAnimation* cavDir;
        SingleFrameAnimation* fundo;
    
    public:
        Menu(Jogo* pJogo);
        ~Menu();
        void executar();
        void desenhar();

        void montarTextos();
 
        void processarEvento(const sf::Event& evento);  // navegação por W-S

        bool getAtivo() const { return ativo; }
        bool getMultiplayer() const { return multiplayer; }
        int getFase() const { return fase; }

        std::string pedirNome(const std::string& titulo); // captura nomes dos jogadores
        void mostrarRanking(Ranking& ranking); 

        void fechar() { ativo = false; }    
};
 
#endif
