#include "../../include/PantallaSeleccionModo.h"

typedef struct {
  Rectangle btnPrimeroA4;
  Rectangle btnAcumulado;
} BtnsModos;

PantallaSeleccionModo::PantallaSeleccionModo(GameState *globalState,
                                             float screenWidth,
                                             float screenHeight) {
  this->globalState = globalState;

  BtnsModos dimension = {
      // Modo de Juego: Primero a 4
      {.x = screenWidth / 10,
       .y = screenHeight / 2,
       .width = 340,
       .height = 60},
      // Modo de Juego: Acumulado
      {.x = screenWidth / 10,
       .y = screenHeight / 2 + 100,
       .width = 340,
       .height = 60},
  };

  this->menu.agregarBoton(
      Boton(dimension.btnPrimeroA4, "Primero a 4", BLUE, [this]() {
        this->globalState->setModoDeJuego(GameState::PRIMEROA4);
      }));
  this->menu.agregarBoton(
      Boton(dimension.btnAcumulado, "Modo Acumulado", BLUE, [this]() {
        this->globalState->setModoDeJuego(GameState::ACUMULADO);
      }));
};

void PantallaSeleccionModo::dibujarPantalla(float screenWidth,
                                            float screenHeight) {

  static const float fontSize = 60;
  static Font defaultFont = GetFontDefault();
  static const char *title = "Elija un modo de juego";
  static const float spacing = 0.0f;

  static const Vector2 titleWidth =
      (MeasureTextEx(defaultFont, title, fontSize, spacing));
  static const int titleLocationX = (screenWidth - titleWidth.x) / 2;
  static const int titleLocationY = screenHeight / 12;

  // Dibujando titulos y subtitulos de menu principal
  DrawTextEx(defaultFont, title, {(float)titleLocationX, (float)titleLocationY},
             fontSize, spacing, DARKGRAY);
  menu.dibujarBotones();
};

void PantallaSeleccionModo::actualizarPantalla() { this->menu.btnListeners(); }
