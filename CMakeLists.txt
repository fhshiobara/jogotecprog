cmake_minimum_required(VERSION 3.16)
project(Jogo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/msys64/mingw64/lib/cmake/SFML")
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)

include_directories(include)

# Mantém a cópia dos assets para a pasta de build
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Coleta headers e assets para aparecerem na IDE
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS
    "include/*.h"
    "include/*.hpp"
)

file(GLOB_RECURSE ASSET_FILES CONFIGURE_DEPENDS
    "assets/*"
)

add_executable(Jogo
    src/main.cpp
    src/Ranking.cpp
    src/Jogo.cpp
    src/Menu.cpp
    src/Fase.cpp
    src/FasePrimeira.cpp
    src/Ente.cpp
    src/Entidade.cpp
    src/Personagem.cpp
    src/Jogador.cpp
    src/Inimigo.cpp
    src/Bicho.cpp
    src/Demonio.cpp
    src/Morte.cpp
    src/Projetil.cpp
    src/Obstaculo.cpp
    src/Plataforma.cpp
    src/Espinhos.cpp
    src/GerenciadorGrafico.cpp
    src/GerenciadorColisoes.cpp
    src/ListaEntidades.cpp
    src/Animation.cpp
    src/SingleFrameAnimation.cpp
    src/FaseSegunda.cpp
    src/Gelo.cpp

    # Apenas para aparecerem na IDE
    ${HEADER_FILES}
    ${ASSET_FILES}
)

# Faz a IDE recriar a estrutura de pastas
source_group(TREE "${CMAKE_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_FILES})
source_group(TREE "${CMAKE_SOURCE_DIR}/assets" PREFIX "Assets" FILES ${ASSET_FILES})

target_link_libraries(Jogo
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)
