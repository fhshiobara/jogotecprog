cmake_minimum_required(VERSION 3.16)

project(Jogo)

# Garante o padrão C++17 correto para o compilador do Xcode
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configura o caminho interno do SFML
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.6.1/lib/cmake/SFML")

# Encontra os pacotes do SFML
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)


# Isso resolve o problema de o Xcode fechar sem abrir a janela gráfica!
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.6.1/lib")

# Cria o executável com todos os seus arquivos fontes
add_executable(main
    src/main.cpp
    src/Jogo.cpp
    src/GerenciadorGrafico.cpp
    src/Personagem.cpp
    src/Ente.cpp
    src/Entidade.cpp
    src/Jogador.cpp
    src/SingleFrameAnimation.cpp
    src/Animation.cpp
    
    include/Ente.hpp
    include/Entidade.hpp
    include/GerenciadorGrafico.hpp
    include/Jogador.hpp
    include/Jogo.hpp
    include/Personagem.hpp
    include/SingleFrameAnimation.hpp
    include/VectorTL.hpp
    include/Animation.hpp
)

# Inclui os diretórios de headers do seu projeto E da SFML de forma moderna
target_include_directories(main PRIVATE
    include
    ${SFML_INCLUDE_DIR}
)

# Vincula as bibliotecas usando os alvos oficiais da SFML (padrão moderno do CMake)
target_link_libraries(main PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
