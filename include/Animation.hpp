//
//  Animation.hpp
//  main
//
//  Created by Edison Shiobara on 25/05/26.
//
#ifndef Animation_hpp
#define Animation_hpp

#include <stdio.h>
#include "GerenciadorGrafico.hpp"
#include <map>
#include "VectorTL.hpp"

enum Animation_ID{
    walk = 0,
    idle = 1,
    attack = 2,
    hurt = 3,
    jump = 4
};

class Animation{
private:
    class SingleAnimation{
        private:
            const unsigned int imageCount;
            unsigned int currentImage;
            sf::Texture* texture;
            float totalTime;
            sf::IntRect rectSize;
            static const float switchTime;
        public:
            SingleAnimation(const char* path, const unsigned int imageCount):imageCount(imageCount),currentImage(0),texture(pGraphicM->loadTexture(path)),totalTime(0.0f),rectSize(){
                if(texture==NULL){
                    std::cerr << "ERRO:carregando textura em SingleAnimation::SingleAnimation" <<std::endl;
                    exit(1);
                }
                rectSize.width = texture->getSize().x/float(imageCount);
                rectSize.height = texture->getSize().y;
            }
            
            ~SingleAnimation(){ }
            
            void update(float dt, bool olhandoesquerda){
                totalTime+=dt;
                
                if(totalTime>=switchTime){
                    totalTime-=switchTime;
                    currentImage++;
                    if(currentImage>=imageCount){currentImage = 0;}
                }
                
                int larguraFrame = texture->getSize().x/imageCount;
                
                if(olhandoesquerda){
                        rectSize.left = (currentImage + 1) * larguraFrame;
                        rectSize.width = -larguraFrame;
                    }
                else{
                        rectSize.left = currentImage * larguraFrame;
                        rectSize.width = larguraFrame;
                    }
            }
            
            void reset(){
                currentImage = 0;
                totalTime = 0;
            }
            sf::IntRect getSize()const{return rectSize;}
            sf::Texture* getTexture(){return texture;}
        };
        private:
            sf::RectangleShape body;
            std::map<Animation_ID, SingleAnimation*>animationMap;
            Animation_ID currentID;
            
        public:
            Animation();
            ~Animation();
            
            void addNewAnimation(Animation_ID id, const char* path, unsigned int imageCount);
            void update(Animation_ID id, bool facingLeft, CoordF position,float dt);
            void render();
            // sf::FloatRect getBounds() const { return body.getGlobalBounds(); }
};


#endif /* Animation_hpp */
