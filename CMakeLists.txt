cmake_minimum_required(VERSION 3.16)
project(slavednp3 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# adiciona a lib como subprojeto (mantém opendnp3 separado do seu código)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../opendnp3
                 ${CMAKE_BINARY_DIR}/opendnp3-build)

add_executable(slavednp3
    src/main.cpp
    src/board.cpp
)

set_target_properties(slavednp3 PROPERTIES
  BUILD_RPATH "\$ORIGIN"
  INSTALL_RPATH "\$ORIGIN"
)

target_include_directories(slavednp3 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ------------------------------------------------------------------
# Detecta libgpiod: se existir, ativa GPIO; se não, compila sem GPIO
#     target_compile_definitions(slavednp3 PRIVATE GPIOD_SUPPORT=0)

# ------------------------------------------------------------------
find_library(GPIOD_LIB gpiod)

if (GPIOD_LIB)
    message(STATUS "libgpiod encontrada: ${GPIOD_LIB}")
    target_link_libraries(slavednp3 PRIVATE opendnp3 ${GPIOD_LIB})
else()
    message(WARNING "libgpiod NÃO encontrada -> compilando SEM GPIO")
    target_link_libraries(slavednp3 PRIVATE opendnp3)
endif()
