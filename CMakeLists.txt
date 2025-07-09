cmake_minimum_required(VERSION 3.15)
project(validador_api)

# Usa o vcpkg (ajuste o caminho se necessário)
set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

# C++ moderno
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Bibliotecas via vcpkg
find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Fonte principal
add_executable(validador_api
        src/main.cpp
        src/validator.cpp
)

# Linka com as libs
target_link_libraries(validador_api
        PRIVATE
        Crow::Crow
        nlohmann_json::nlohmann_json
)
