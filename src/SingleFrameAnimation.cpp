//
//  SingleFrameAnimation.cpp
//  Jogo
//
//  Created by Edison Shiobara on 25/05/26.
//

#include "SingleFrameAnimation.hpp"
//classe inspirada nos videos do Burda canal episodio 7

namespace Gerenciadores{
SingleFrameAnimation::SingleFrameAnimation(const char* path, CoordF position, CoordF size, float scale):texture(NULL),corpo(sf::Vector2f(size.x,size.y)){
    
    texture=Gerenciadores::GerenciadorGrafico::getInstance()->loadTexture(path);
    
    corpo.setPosition(sf::Vector2f(position.x,position.y));
    corpo.setScale(sf::Vector2f(scale,scale));
    
    corpo.setTexture(texture);
    }
    SingleFrameAnimation::~SingleFrameAnimation(){ }
    void SingleFrameAnimation::update(CoordF position){
        corpo.setPosition(sf::Vector2f(position.x,position.y));
    }

    void SingleFrameAnimation::render(){
        Gerenciadores::GerenciadorGrafico::getInstance()->render(&corpo);
    }
}


