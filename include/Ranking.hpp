#ifndef RANKING_HPP
#define RANKING_HPP

#include <string>
#include <vector>

struct Pontuacao {
    std::string nomeJogador;
    int pontosFinais;
};
// Cada linha do arquivo: <pontos> <nome>

class Ranking {
    private:
        std::string caminho;             
        std::vector<Pontuacao> tabela;  

        void ordenar();

    public:
        Ranking(const std::string& arquivo = "../ranking.txt");
        ~Ranking();

        void ler();                                          
        void gravar() const;                               
        void registrar(const std::string& nome, int pontos); 

        const std::vector<Pontuacao>& getTabela() const { return tabela; }
};

#endif
