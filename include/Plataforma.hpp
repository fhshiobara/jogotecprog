#ifndef PLATAFORMA_HPP
#define PLATAFORMA_HPP

#include "Obstaculo.hpp"

class Jogador;

class Plataforma : public Obstaculos::Obstaculo {
    private:
        float largura;
        float altura;

    public:
        Plataforma(CoordF position, float largura, float altura);
        ~Plataforma();

        void executar();
        void salvar();

        // True se o player pisar na plataforma
        bool obstruir(CoordF& posJogador, float& velocidadeY, float& velocidadeX, bool& noChao, float alturaJogador) const;

        void desenhar();

        float getTopo() const { return pos.y; }
        float getEsquerda() const { return pos.x; }
        // Topo-esquerda da plataforma define a pos.

        float getBase() const { return pos.y + altura; }
        float getDireita()  const { return pos.x + largura; }
};

#endif
