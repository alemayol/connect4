#include "../../include/Principal.h"
#include "../../include/Pantalla.h"
#include "../../include/PantallaHistorial.h"
#include "../../include/PantallaJuego.h"
#include "../../include/PantallaPrincipal.h"
#include "../../include/PantallaSeleccionModalidad.h"
#include "../../include/PantallaSeleccionModo.h"
#include "raylib.h"

// Definimos estructura para facilitar la lectura y uso de los limites de los
// rectangulos de los botones del menu de la pantalla
typedef struct LimitesBotonesPrincipal {
  Rectangle iniciarPartida;
  Rectangle PrimeroA4;
  Rectangle Acumulado;
  Rectangle JugadorVSJugador;
  Rectangle JugadorVSIa;
  Rectangle IaVSIa;
} LimitesBotonesPrincipal;

// Constructores
Principal::Principal(GameState *globalState) {
  this->globalState = globalState;
}

// Funcion principal que inicia la pantalla usando raylib e inicia el bucle
// principal del juego
void Principal::IniciarPantallaPrincipal() {

  const int defaultWidth = 1024,
            defaultHeight =
                768; // Tamano de pantalla por defecto, necesitamos iniciar la
                     // ventana antes de poder obtener el tamano de la pantalla

  const char *gameTitle = "Conecta 4";
  const int fontSizePrincipal = 40;
  const float spacing = 5.5;

  // Asignamos banderas de configuracion para la ventana principal
  // SetConfigFlags(FLAG_FULLSCREEN_MODE);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
  SetConfigFlags(FLAG_WINDOW_TOPMOST);

  InitWindow(defaultWidth, defaultHeight, gameTitle);
  MaximizeWindow();

  // Calcular medidas del monitor y pantalla
  float monitorWidth =
      GetMonitorWidth(0); // Monitor 0 es el monitor principal de usuario
  float monitorHeight = GetMonitorHeight(0);
  float screenWidth = GetScreenWidth();
  float screenHeight = GetScreenHeight();

  // Comenzamos sin una pantalla en particular
  Pantalla *pantallaActual = nullptr;

  // Mientras no se cierre la ventana a traves de señales del sistema (boton x
  // de cerrar ventana) y el jugador no cliquee el boton de salir, se elegirá la
  // pantalla correspondiente y se actualizaran y dibujaran los componentes en
  // ellas
  while (!WindowShouldClose() && !this->globalState->getSalirDelJuego()) {

    // Actualizamos el puntero con la pantalla actual correspondiente
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
      pantallaActual = new PantallaSeleccionModalidad(globalState, screenWidth,
                                                      screenHeight);
      break;
    case GameState::PARTIDA:
      pantallaActual =
          new PantallaJuego(globalState, screenWidth, screenHeight);

      break;
    case GameState::PANTALLA_HISTORIAL:
      pantallaActual =
          new PantallaHistorial(globalState, screenWidth, screenHeight);

      break;
    }

    // Actualizamos el estado de la pantalla antes de continuar
    pantallaActual->actualizarPantalla();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Dibujar la pantalla actual
    pantallaActual->dibujarPantalla(screenWidth, screenHeight);
    EndDrawing();
  }
}

// Se ejecuta cuando el jugador clickea en el boton de cerrar, se finaliza el
// juego
void Principal::CerrarPantallaPrincipal() { CloseWindow(); }
