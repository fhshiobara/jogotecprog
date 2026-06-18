#ifndef JOGADOR_HPP
#define JOGADOR_HPP
 
#include "Personagem.hpp"
#include "Animation.hpp"

namespace Personagens {
 
    class Jogador: public Personagem {
    
        protected:
            int pontos;
            float dt_local;

            bool atacando;
            float tempoAtaqueAtual;
            static const float DURACAO_ATAQUE;
        
        float tempoInvulneravel;
        bool Invulneravel;
    
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
            bool getAtacando() { return atacando; }
        
        bool getInvulneravel();
        void setInvulneravel(bool inv);
        
        void tempoImunidade(float dt);
        void setInvulnerabilidade(float tmp);
        bool getOlhandoEsquerda(){return olhandoEsquerda;}
        
    };
}
 
#endif
