cmake_minimum_required(VERSION 3.16)

project(Jogo)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "SFML-2.6.1/lib/cmake/SFML") # path do SFML (2.6.1)

include_directories(include)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

add_executable(main

    src/Plataforma.cpp
    src/Inimigo.cpp
    src/main.cpp
    src/Jogo.cpp
    src/GerenciadorGrafico.cpp
    src/Personagem.cpp
    src/Ente.cpp
    src/Entidade.cpp
    src/Jogador.cpp
    src/Animation.cpp
    src/SingleFrameAnimation.cpp
)

target_link_libraries(main

    sfml-graphics
    sfml-window
    sfml-system
)