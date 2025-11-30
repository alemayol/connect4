#include "../../include/PantallaJuego.h"
#include "../../include/Partida.h"
#include "../../include/Tablero.h"
#include <iostream>
#include <raylib.h>

PantallaJuego::PantallaJuego(GameState *globalState, float screenWidth,
                             float screenHeight) {
  this->globalState = globalState;
  this->ganador = false;
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;
};

// PantallaJuego::PantallaJuego(float screenWidth, float screenHeight) {};

void PantallaJuego::dibujarPantalla(float screenWidth, float screenHeight) {

  static const float fontSize = 60;
  static Font defaultFont = GetFontDefault();
  static const char *gameTitle = "Juego en marcha";
  static const float spacing = 3.5f;

  Vector2 titleWidth =
      (MeasureTextEx(defaultFont, gameTitle, fontSize, spacing));
  int titleLocationX = (screenWidth - titleWidth.x) / 2;
  int titleLocationY = screenHeight / 12;

  // Dibujando titulos y subtitulos de menu principal
  DrawTextEx(defaultFont, gameTitle,
             {(float)titleLocationX, (float)titleLocationY}, fontSize, spacing,
             DARKGRAY);

  const float posTableroX = (screenWidth - 600) / 2;
  const float posTableroY = (screenHeight - 400) / 2;
  const float ancho = 600;
  const float alto = 400;

  // Tablero::dibujarTablero(this->partida->getLimitesTablero(),
  //                       this->partida->getParrilla());

  this->globalState->getPartidaActual()->inicializarTablero();
}

void PantallaJuego::mostrarGanador() {
  /*
  if (this->ganador) {

    Rectangle popup = {screenWidth - 400, screenHeight - 200, 400,200};

    BeginDrawing();
    // Obscurecer pantalla
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));

    DrawRectangleRounded(popup, 0.05, 6, LIGHTGRAY);
    EndDrawing();
  }
  */
}

void PantallaJuego::actualizarPantalla() {

  this->menu.btnListeners();

  if (this->globalState->getPartidaActual()->getJuegoFinalizado()) {
    this->globalState->setPantallaActual(GameState::PANTALLA_PRINCIPAL);
    return;
  }

  this->globalState->getPartidaActual()->actualizarTablero();
  // Tablero::actualizarTablero(this->partida->getLimitesTablero(),
  //                          this->partida->getParrilla());
}
