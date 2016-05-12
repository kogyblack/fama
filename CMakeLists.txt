cmake_minimum_required(VERSION 2.8)

project("Framework de Aprendizado de Máquina")

# For YouCompleteMe integration
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Set C++11 as standard compilation
#add_definitions("-std=c++11")

include_directories(.)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_DEBUG_POSTFIX -d)

# Base subdirectories
# Compiled directly into a library
#add_subdirectory(corpus)
#add_subdirectory(avaliador)
#add_subdirectory(treinador)
#add_subdirectory(classificador)


set(BASE_SRCS
  corpus/corpus.cpp
  avaliador/avaliador.cpp
  classificador/classificador.cpp
  treinador/treinador.cpp)
add_library(base ${BASE_SRCS})

set(AVALIADOR_SRCS
  avaliador/avaliador_acuracia.cpp
  avaliador/avaliador_acuracia_respostas_adicionais.cpp
  avaliador/avaliador_diferenca.cpp
  avaliador/avaliadormatrizconfusao.cpp)
add_library(base-avaliador ${AVALIADOR_SRCS})
target_link_libraries(base-avaliador base)

#add_subdirectory(C50)
#add_subdirectory(id3)
#add_subdirectory(libsvm)
#add_subdirectory(outros)
#add_subdirectory(processador)
#add_subdirectory(stump)
#add_subdirectory(testes)
#add_subdirectory(validador)

#add_subdirectory(Interface)
