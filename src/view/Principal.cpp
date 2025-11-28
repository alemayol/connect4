#include "../../include/Principal.h"
#include "../../include/Pantalla.h"
#include "../../include/PantallaPrincipal.h"
#include "../../include/PantallaSeleccionModo.h"
#include "raylib.h"
#include <iostream>

typedef struct LimitesBotonesPrincipal {
  Rectangle iniciarPartida;
  Rectangle PrimeroA4;
  Rectangle Acumulado;
  Rectangle JugadorVSJugador;
  Rectangle JugadorVSIa;
  Rectangle IaVSIa;
} LimitesBotonesPrincipal;

Principal::Principal(GameState *globalState) {
  this->globalState = globalState;
}

void Principal::IniciarPantallaPrincipal() {

  const int defaultWidth = 1024,
            defaultHeight =
                768; // Tamano de pantalla por defecto, necesitamos iniciar la
                     // ventana antes de poder obtener el tamano de la pantalla

  const char *gameTitle = "Conecta 4";
  const int fontSizePrincipal = 40;
  const float spacing = 5.5;

  // Comenzamos la ventana en pantalla completa
  // SetConfigFlags(FLAG_FULLSCREEN_MODE);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);

  InitWindow(defaultWidth, defaultHeight, gameTitle);
  MaximizeWindow();

  /*
  SetConfigFlags(FLAG_WINDOW_UNDECORATED);
  SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
  SetConfigFlags(FLAG_WINDOW_TOPMOST);
*/

  // Calcular medidas y posiciones basadas en la pantalla
  float monitorWidth = GetMonitorWidth(0);
  float monitorHeight = GetMonitorHeight(0);
  float screenWidth = GetScreenWidth();
  float screenHeight = GetScreenHeight();

  // Calcular y asignar posicion de botones con respecto a pantalla
  LimitesBotonesPrincipal limitesBotones = {
      // Modalidad: JugadorVSJugador
      {.x = (screenWidth / 10) * 6,
       .y = screenHeight / 2,
       .width = 340,
       .height = 60},
      // Modalidad: JugadorVSIa
      {.x = screenWidth / 10 * 6,
       .y = screenHeight / 2 + 100,
       .width = 340,
       .height = 60},
      // Modalidad: IaVSIa
      {.x = screenWidth / 10 * 6,
       .y = screenHeight / 2 + 200,
       .width = 340,
       .height = 60},
  };

  /*
  Tengo que migrar esto a una nueva subclase de Pantalla
  menu.agregarBoton(
      Boton(limitesBotones.JugadorVSJugador, "Jugador vs Jugador", BLUE,
            [this]() { this->globalState->setModalidad(GameState::HVSH); }));
  menu.agregarBoton(
      Boton(limitesBotones.JugadorVSIa, "Jugador vs Ia", BLUE,
            [this]() { this->globalState->setModalidad(GameState::HVSIA); }));
  menu.agregarBoton(Boton(limitesBotones.IaVSIa, "Ia vs Ia", BLUE, [this]() {
    this->globalState->setModalidad(GameState::IAVSIA);
  }));
*/
  Pantalla *pantallaActual = nullptr;

  while (!WindowShouldClose() && !this->globalState->getSalirDelJuego()) {
    // Update
    switch (this->globalState->getPantallaActual()) {
    case GameState::PANTALLA_PRINCIPAL:
      pantallaActual =
          new PantallaPrincipal(globalState, screenWidth, screenHeight);
      break;
    case GameState::SELECCION_MODO:;
      pantallaActual =
          new PantallaSeleccionModo(globalState, screenWidth, screenHeight);
      break;
    case GameState::SELECCION_MODALIDAD:;
      break;
    case GameState::PARTIDA:;
      break;
    }

    pantallaActual->actualizarPantalla();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw
    pantallaActual->dibujarPantalla(screenWidth, screenHeight);
    EndDrawing();
  }
}

void Principal::CerrarPantallaPrincipal() { CloseWindow(); }
