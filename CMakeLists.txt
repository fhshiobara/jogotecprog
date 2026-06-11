cmake_minimum_required(VERSION 3.16)

project(Jogo)

set(CMAKE_CXX_STANDARD 17)

# Organiza os arquivos em pastas (Groups) dentro do Xcode
set(CMAKE_FOLDER "Jogo")

set(SFML_DIR "SFML-2.6.1/lib/cmake/SFML") # path do SFML (2.6.1)

include_directories(include)

# Copia a pasta de assets para o diretório de build
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

# Mapeia todos os arquivos de cabeçalho da pasta include
file(GLOB_RECURSE INCLUDE_FILES "include/*.hpp" "include/*.h")

# Mapeia os arquivos de assets para que apareçam no Xcode
file(GLOB_RECURSE ASSET_FILES "assets/*.*")

# Cria os grupos (pastas virtuais) no Xcode para organizar a lateral
source_group("Headers" FILES ${INCLUDE_FILES})

# ALTERAÇÃO AQUI: Mapeia a árvore de arquivos respeitando as subpastas
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/assets" PREFIX "Assets" FILES ${ASSET_FILES})

source_group("Sources" REGULAR_EXPRESSION "src/.*")

add_executable(main
    ${INCLUDE_FILES}
    ${ASSET_FILES}

    src/Morte.cpp
    src/Arvore.cpp
    src/Demonio.cpp
    src/Limites.cpp
    src/Obst_Medio.cpp
    src/GerenciadorColisoes.cpp
    src/ListaEntidades.cpp
    src/Obstaculo.cpp
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
    src/Fase.cpp
    src/FasePrimeira.cpp
)

target_link_libraries(main
    sfml-graphics
    sfml-window
    sfml-system
)
