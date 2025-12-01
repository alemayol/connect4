cmake_minimum_required(VERSION 3.5)
project(Connect4 CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CUSTOMIZE_BUILD ON) # Para activar las opciones personalizadas de raylib
set(GLFW_BUILD_WAYLAND OFF) # Build the bundled GLFW with Wayland support (de igual manera no pude correrlo en wayland, voy para x11 con i3)
set(GLFW_BUILD_X11 ON)
set(OPENGL_VERSION 2.1) # Mi pc con graficos integrados no pasa de esa version mi loco

# Parametros para raylib

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # no se construyen los ejemeplos
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # ni los juegos

# Buscando paquetes de raylib
#add_subdirectory(libs/raylib)
find_package(raylib QUIET REQUIRED)

add_executable(${PROJECT_NAME} ./main.cpp src/view/Principal.cpp src/view/Boton.cpp src/view/Menu.cpp src/model/GameState.cpp src/view/PantallaPrincipal.cpp src/view/PantallaModos.cpp src/view/PantallaModalidad.cpp src/view/PantallaJuego.cpp src/view/Tablero.cpp src/model/Partida.cpp src/model/AI.cpp src/data/PartidaGuardada.cpp src/view/PantallaHistorial.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)



#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine

#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="relative-path-to-assets-in-the-game-package") # Set the asset path macro in release mode
