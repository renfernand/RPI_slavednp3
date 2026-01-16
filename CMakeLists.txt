cmake_minimum_required(VERSION 3.16)
project(slavednp3 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# adiciona a lib como subprojeto (mantém opendnp3 separado do seu código)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../opendnp3
                 ${CMAKE_BINARY_DIR}/opendnp3-build)

add_executable(slavednp3
    src/main.cpp
)

set_target_properties(slavednp3 PROPERTIES
  BUILD_RPATH "\$ORIGIN"
  INSTALL_RPATH "\$ORIGIN"
)


target_link_libraries(slavednp3 PRIVATE opendnp3)
