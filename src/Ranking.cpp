#include "Ranking.hpp"
#include <fstream>
#include <iostream>

Ranking::Ranking(const std::string& arquivo): caminho(arquivo) {
    ler();
}

Ranking::~Ranking() {}

void Ranking::ordenar() {
    // Bubble sort: maior pontuacao primeiro.
    // A cada passada, "empurra" o menor para o fim; repete ate nao haver troca.
    // Provém do Stack Overflow.
    int n = tabela.size();

    for (int i = 0; i < n - 1; i++) {
        bool houveTroca = false;

        for (int j = 0; j < n - 1 - i; j++) {
            if (tabela[j].pontosFinais < tabela[j + 1].pontosFinais) {
                Pontuacao temp = tabela[j];
                tabela[j] = tabela[j + 1];
                tabela[j + 1] = temp;
                houveTroca = true;
            }
        }
        if (!houveTroca)
            break;
    }
}

void Ranking::ler() {
    tabela.clear();

    std::ifstream entrada(caminho);

    if (!entrada.is_open()) // caso nao ache
        return;

    // Cada linha: <pontos> <nome>
    Pontuacao ponts;
    while (entrada >> ponts.pontosFinais >> ponts.nomeJogador) {
        tabela.push_back(ponts);
    }

    entrada.close();
    ordenar();
}

void Ranking::gravar() const {
    std::ofstream saida(caminho);
    
    if (!saida.is_open()) {
        std::cerr << "ERRO: nao foi possivel gravar o ranking em " << caminho << ", Verifique o caminho" << std::endl;
        return;
    }

    for (const Pontuacao& p : tabela)
        saida << p.pontosFinais << " " << p.nomeJogador << "\n";

    saida.close();
}

void Ranking::registrar(const std::string& nome, int pontos) {

    Pontuacao ranking;
    ranking.nomeJogador = nome;
    ranking.pontosFinais = pontos;

    tabela.push_back(ranking);
    ordenar();
    gravar();
}
