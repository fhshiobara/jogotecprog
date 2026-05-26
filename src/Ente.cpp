#include "Ente.hpp"

Gerenciadores::GerenciadorGrafico* Ente::pGG = nullptr;
int Ente::idCounter = 0;

Ente::Ente(const char* pathToTexture): id(idCounter++) {

    this->setGG(Gerenciadores::GerenciadorGrafico::getInstance());
    texture = pGG->loadTexture(pathToTexture);

    if (pathToTexture != nullptr) {
        text.loadFromFile(pathToTexture);
            setSprite(text);
    } else {
            
        std::cerr << "Aviso: Entidade " << id << " criada sem textura." << std::endl;

        /////////////////////////////////////////////////////////////
        // Cria uma imagem 64x64 magenta/preta (placeholder clássico)
        sf::Image img;
        img.create(64, 64, sf::Color::Magenta);

       // Desenha quadrados pretos
       for (unsigned int y = 0; y < 64; y++) {
            for (unsigned int x = 0; x < 64; x++) {
                if ((x / 8 + y / 8) % 2 == 0)
                    img.setPixel(x, y, sf::Color::Black);
            } 
        }
        // Imagem do placeholder criada pelo Chatgpt. Funciona mesmo sem a pasta assets
            textura.loadFromImage(img);
            sprite.setTexture(textura);
        } 
    }

Ente::~Ente() {}

void Ente::desenhar() {
    pGG->render(&sprite);
}