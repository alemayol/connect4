#include "../../include/PantallaJuego.h"
#include "../../include/Partida.h"
#include <raylib.h>

// Definimos estructura para facilitar la lectura y uso de los limites de los
// rectangulos de los botones del menu de la pantalla
typedef struct {
  Rectangle btnVolver;
} BtnsMenuJuego;

// Constructores
PantallaJuego::PantallaJuego(GameState *globalState, float screenWidth,
                             float screenHeight) {
  this->globalState = globalState;
  this->ganador = false;
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;
};

// Basado en el tamano de la pantalla del usuario calculamos y dibujamos la
// pantalla
void PantallaJuego::dibujarPantalla(float screenWidth, float screenHeight) {

  // Establecemos el tamano de fuente, la fuente, titulo de la pantalla y
  // espaciado del texto
  static const float fontSize = 60;
  static Font defaultFont = GetFontDefault();
  static const char *gameTitle = "Juego en marcha";
  static const float spacing = 3.5f;

  Vector2 titleWidth =
      (MeasureTextEx(defaultFont, gameTitle, fontSize, spacing));
  int titleLocationX = (screenWidth - titleWidth.x) / 2;
  int titleLocationY = screenHeight / 12;

  // Dibujando titulos y menu
  DrawTextEx(defaultFont, gameTitle,
             {(float)titleLocationX, (float)titleLocationY}, fontSize, spacing,
             DARKGRAY);

  BtnsMenuJuego btns = {
      // Volver al menu principal
      {.x = 10, .y = 50, .width = 150, .height = 60},
  };

  // Agregamos botones al menu de la pantalla
  this->menu.agregarBoton(Boton(btns.btnVolver, "Volver", BLUE, [this]() {
    // En caso de click, se regresa a la pantalla principal
    this->globalState->setPantallaActual(GameState::PANTALLA_PRINCIPAL);
    // En caso de volver durante una partida en marcha, se guarda la partida en
    // la memory card para reestablecerla despues (por hacer)
    this->globalState->pushMemoryCard(this->globalState->getPartidaActual());
  }));

  // Se pinta el tablero en pantalla
  this->globalState->getPartidaActual()->inicializarTablero();
}

// Mostrar al jugador ganador un popup indicando la victoria (POR HACER)
void PantallaJuego::mostrarGanador() {}

void PantallaJuego::actualizarPantalla() {

  // Si la partida finalizo, vamos a la pantalla principal y guardamos partida
  // en el historial de partidas (memory card)
  if (this->globalState->getPartidaActual()->getJuegoFinalizado()) {
    this->globalState->setPantallaActual(GameState::PANTALLA_PRINCIPAL);
    this->globalState->pushMemoryCard(this->globalState->getPartidaActual());
    return;
  }
  // this->menu.btnListeners();

  this->globalState->getPartidaActual()->actualizarTablero();
}
