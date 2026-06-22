#ifndef JOGADOR_HPP
#define JOGADOR_HPP
 
#include "Personagem.hpp"
#include "Animation.hpp"

namespace Personagens {
    
    class Inimigo;

    class Jogador: public Personagem {
    
        protected:
            int pontos;
            float dt_local;

            bool atacando;
            float tempoAtaqueAtual;
            static const float DURACAO_ATAQUE;
        
            float tempoInvulneravel;
            bool Invulneravel;
            float tempoDevagar;
            bool Devagar;        
        public:
            Jogador(CoordF position, int hp = 3, int pontos = 0, float speed = 1.0f);
            ~Jogador();
    
            void executar();
            void salvar();
            void morrer();
            void initialize(bool Jog);
            void mover();
            void pular();
            
            void atualizarAnimacao(Animation_ID, bool olhandoEsquerda, float dt);
            void desenhar();
    
            void moverX(bool direcao, float dt);
        
            void golpear();
            void atualizarGolpe(float dt); // Cuida do tempo do golpe
            void pontuar(int pontosAdiquiridos) { pontos += pontosAdiquiridos; }
            
            void danificar(Inimigo* pInimigo);
            void setAtacando(bool atk){atacando = atk;}
            bool getAtacando() { return atacando; }
            //funcoes para o danificar do demonio
            bool getInvulneravel();
            void setInvulneravel(bool inv);
            void tempoImunidade(float dt);
            void setInvulnerabilidade(float tmp);
            //funcoes para o danificar do Bicho
            
            //estou aplicando os danificar de maneira analoga, um empurra e o outro vai desacelerar, porem os elementos necessarios para aplicacao acabam sendo iguais
            bool getDevagar();
            void setDevagar(bool dev);
            void tempoDesacelerado(float dt);
            void setDesaceleracao(float tmp);
            
            bool getOlhandoEsquerda(){return olhandoEsquerda;}
            void tomarDanoMassivo(int dano);
    };
}
 
#endif
