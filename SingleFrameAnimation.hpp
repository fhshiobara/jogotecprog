//
//  SingleFrameAnimation.hpp
//  Jogo
//
//  Created by Edison Shiobara on 25/05/26.
//

#ifndef SingleFrameAnimation_hpp
#define SingleFrameAnimation_hpp

#pragma once
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "VectorTL.hpp"
#include "GerenciadorGrafico.hpp"

namespace Gerenciadores{
class SingleFrameAnimation{
private:
    sf::Texture* texture;
    sf::RectangleShape corpo;
public:
    SingleFrameAnimation(const char* path,CoordF position,CoordF size, float scale);
    ~SingleFrameAnimation();
    
    void update(CoordF position);
    void render();
};
}



#endif /* SingleFrameAnimation_hpp */
