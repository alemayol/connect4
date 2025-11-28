#include "../../include/PantallaPrincipal.h"
#include <iostream>
#include <raylib.h>

typedef struct {
  Rectangle btnIniciar;
  Rectangle btnSalir;
} BtnsMenuPrincipal;

PantallaPrincipal::PantallaPrincipal(GameState *globalState, float screenWidth,
                                     float screenHeight) {
  this->globalState = globalState;

  static const float fontSize = 60;
  BtnsMenuPrincipal dimension = {

      // Iniciar partida
      {.x = ((float)MeasureText("Iniciar", fontSize) + 20),
       .y = screenHeight - 70,
       .width = 300,
       .height = 60},
      // Salir del juego
      {.x = (screenWidth - MeasureText("Salir", fontSize) * 3),
       .y = screenHeight - 70,
       .width = 300,
       .height = 60},

  };

  this->menu.agregarBoton(
      Boton(dimension.btnIniciar, "Iniciar Partida", BLUE, [this]() {
        this->globalState->setPantallaActual(GameState::SELECCION_MODO);
        std::cout << "Iniciar Partida 1" << std::endl;
      }));
  this->menu.agregarBoton(Boton(dimension.btnSalir, "Salir", BLUE, [this]() {
    this->globalState->setSalirDelJuego(true);
  }));
}

void PantallaPrincipal::dibujarPantalla(float screenWidth, float screenHeight) {

  static const float fontSize = 60;
  static Font defaultFont = GetFontDefault();
  static const char *gameTitle = "Conecta 4";
  static const float spacing = 0.0f;

  Vector2 titleWidth =
      (MeasureTextEx(defaultFont, gameTitle, fontSize, spacing));
  int titleLocationX = (screenWidth - titleWidth.x) / 2;
  int titleLocationY = screenHeight / 12;

  // Dibujando titulos y subtitulos de menu principal
  DrawTextEx(defaultFont, gameTitle,
             {(float)titleLocationX, (float)titleLocationY}, fontSize, spacing,
             DARKGRAY);
  menu.dibujarBotones();
}

void PantallaPrincipal::actualizarPantalla() { this->menu.btnListeners(); }
