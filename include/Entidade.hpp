#pragma once
#ifndef ENTIDADE_HPP
#define ENTIDADE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ente.hpp"


namespace Entidades {

    class Entidade:public Ente{
        protected:
            CoordF pos;
            // std::ostream buffer; TODO

            void salvarDataBuffer(); // TODO
        public:
            Entidade(CoordF position);
            virtual ~Entidade();
            virtual void executar() = 0;
            virtual void salvar() = 0;

    };

}

#endif
