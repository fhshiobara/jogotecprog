//
//  GerenciadorGrafico.cpp
//  JOGOSFML
//
//  Created by Edison Shiobara on 19/05/26.
//

#include "GerenciadorGrafico.hpp"

namespace Gerenciadores{
    GerenciadorGrafico* GerenciadorGrafico::instance = NULL;

    GerenciadorGrafico* GerenciadorGrafico::getInstance(){
        if(instance==NULL){
            instance = new GerenciadorGrafico();
        }
        return instance;
    }

    GerenciadorGrafico::GerenciadorGrafico() {
        
            window = new sf::RenderWindow(sf::VideoMode(800, 600), "Gerenciador Grafico");
            window->setFramerateLimit(100);
        }

    GerenciadorGrafico::~GerenciadorGrafico(){
        delete window;
        for (auto& par : texturesMap) {
            delete par.second;
        }
        texturesMap.clear();
    }

    void GerenciadorGrafico::render(sf::RectangleShape* hitbox){
        window->draw(*hitbox);
    }

    void GerenciadorGrafico::render(sf::Text* txt){
        window->draw(*txt);
    }
    bool GerenciadorGrafico::windowopen()const{
        return window->isOpen();
    }

    void GerenciadorGrafico::display(){
        if(windowopen()){
            window->display();
        }
    }

    sf::RenderWindow* GerenciadorGrafico::getWindow(){
        return window;
    }

    void GerenciadorGrafico::closeWindow(){
        window->close();
    }

    void GerenciadorGrafico::clear(){
        window->clear();
    }

    sf::Texture* GerenciadorGrafico::loadTexture(const char* path){
        auto it = texturesMap.find(path);
        if(it!=texturesMap.end()){return it->second;}//achou a textura
        
        sf::Texture* newText = new sf::Texture();//cria um espaco para a textura
        if(!newText->loadFromFile(path)){//se nao achar no files, apaga a nova textura
            delete newText;
            return NULL;
        }
        texturesMap[path]=newText; // salva no map para uso seguinte
        return newText;
            
            

        
    }
}
