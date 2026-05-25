#ifndef ENTIDADE_HPP
#define ENTIDADE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

namespace Entidades {

    class Entidade {
        protected:
            sf::Vector2f pos;
            // std::ostream buffer; TODO

            void salvarDataBuffer(); // TODO
        public:
            Entidade(float Xinicial, float inicialY);
            virtual ~Entidade();
            virtual void executar() = 0;
            virtual void salvar() = 0;

    };

}

#endif
