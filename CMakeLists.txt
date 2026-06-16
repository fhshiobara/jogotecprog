cmake_minimum_required(VERSION 3.16)
project(Jogo LANGUAGES CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
set(SFML_DIR "C:/msys64/mingw64/lib/cmake/SFML")
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)
 
include_directories(include)
 
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
 
# Lista explicita de fontes — sem GLOB, para garantir que nada fique de fora
add_executable(Jogo
    src/main.cpp
    src/Jogo.cpp
    src/Menu.cpp
    src/Fase.cpp
    src/FasePrimeira.cpp
    src/Ente.cpp
    src/Entidade.cpp
    src/Personagem.cpp
    src/Jogador.cpp
    src/Inimigo.cpp
    src/Bixo.cpp
    src/Demonio.cpp
    src/Morte.cpp
    src/Projetil.cpp
    src/Obstaculo.cpp
    src/Plataforma.cpp
    src/Espinhos.cpp
    src/Limites.cpp
    src/GerenciadorGrafico.cpp
    src/GerenciadorColisoes.cpp
    src/ListaEntidades.cpp
    src/Animation.cpp
    src/SingleFrameAnimation.cpp
)
 
target_link_libraries(Jogo
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)
