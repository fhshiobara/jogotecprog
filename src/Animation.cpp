//
//  Animation.cpp
//  main
//
//  Created by Edison Shiobara on 25/05/26.
//

#include "Animation.hpp"

const float Animation::SingleAnimation::switchTime = 0.2; // tempo entre frames

Animation::Animation() : body(), animationMap(), currentID(Animation_ID::walk) {
    // Definimos a escala do retângulo para ficar visível (3x maior)
    body.setScale(sf::Vector2f(3, 3));
}

Animation::~Animation() {
    std::map<Animation_ID, SingleAnimation*>::iterator it;
    for (it = animationMap.begin(); it != animationMap.end(); it++) {
        delete (it->second);
    }
    animationMap.clear();
}

void Animation::addNewAnimation(Animation_ID id, const char* path, unsigned int imageCount) {
    
    SingleAnimation* tmp = new SingleAnimation(path, imageCount);
    
    if (tmp == NULL) {
        std::cerr << "Falha na criacao de nova animacao" << std::endl;
        exit(1);
    }
    
    animationMap.insert(std::pair<Animation_ID, SingleAnimation*>(id, tmp));
    
    sf::IntRect rectSize = tmp->getSize();
    
    // Configura o tamanho inicial baseado no tamanho REAL de UM frame (e não da spritesheet inteira)
    body.setSize(sf::Vector2f(abs(rectSize.width), abs(rectSize.height)));
    body.setOrigin(sf::Vector2f(abs(rectSize.width), abs(rectSize.height)) / 2.0f);
}

void Animation::update(Animation_ID id, bool facingLeft, CoordF position, float dt) {
    
    if (currentID != id) {
        currentID = id;
        animationMap[currentID]->reset();
    }

    animationMap[currentID]->update(dt, facingLeft);
    

    body.setPosition(sf::Vector2f(position.x, position.y));
    

    body.setTexture(animationMap[currentID]->getTexture());
    
    body.setTextureRect(animationMap[currentID]->getSize());
    
    sf::IntRect atualRect = animationMap[currentID]->getSize();
    
    body.setTextureRect(atualRect);
    
    body.setOrigin(sf::Vector2f(abs(atualRect.width), abs(atualRect.height)) / 2.0f);
}

void Animation::render() {
    pGraphicM->render(&body);
}
