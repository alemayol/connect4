#include "../../include/PantallaPrincipal.h"
#include <raylib.h>

// Definimos estructura para facilitar la lectura y uso de los limites de los
// rectangulos de los botones del menu de la pantalla
typedef struct {
  Rectangle btnIniciar;
  Rectangle btnSalir;
  Rectangle btnHistorial;
} BtnsMenuPrincipal;

// Constructores
PantallaPrincipal::PantallaPrincipal(GameState *globalState, float screenWidth,
                                     float screenHeight) {
  this->globalState = globalState;

  this->globalState->setPartidaActual(nullptr);
  this->globalState->setModoDeJuego(MODODEJUEGO::NINGUNO);
  this->globalState->setModalidad(MODALIDAD::NINGUNA);

  static const float fontSize = 60;
  BtnsMenuPrincipal dimension = {

      // Iniciar partida
      {.x = 20, .y = screenHeight - 70, .width = 250, .height = 60},
      // Salir del juego
      {.x = (float)((screenWidth - MeasureText("Salir", fontSize)) / 2) - 50.0f,
       .y = screenHeight - 70,
       .width = 250,
       .height = 60},
      // Historial de partidas
      {
          .x = (screenWidth - MeasureText("Historial", fontSize) - 10.0f),
          .y = screenHeight - 70,
          .width = 250,
          .height = 60,
      }};

  // Agregando botones al menu de la pantalla, en caso de click, se cambia de
  // pantalla a aquella correspondiente
  this->menu.agregarBoton(
      Boton(dimension.btnIniciar, "Iniciar", BLUE, [this]() {
        this->globalState->setPantallaActual(GameState::SELECCION_MODO);
      }));
  this->menu.agregarBoton(Boton(dimension.btnSalir, "Salir", BLUE, [this]() {
    this->globalState->setSalirDelJuego(true);
  }));
  this->menu.agregarBoton(
      Boton(dimension.btnHistorial, "Historial", BLUE, [this]() {
        this->globalState->setPantallaActual(GameState::PANTALLA_HISTORIAL);
      }));
}

void PantallaPrincipal::dibujarPantalla(float screenWidth, float screenHeight) {

  static const float fontSize = 60;
  static Font defaultFont = GetFontDefault();
  static const char *gameTitle = "Conecta 4";
  static const float spacing = 3.5f;

  Vector2 titleWidth =
      (MeasureTextEx(defaultFont, gameTitle, fontSize, spacing));
  int titleLocationX = (screenWidth - titleWidth.x) / 2;
  int titleLocationY = screenHeight / 12;

  // Dibujando titulos y menu principal
  DrawTextEx(defaultFont, gameTitle,
             {(float)titleLocationX, (float)titleLocationY}, fontSize, spacing,
             DARKGRAY);
  menu.dibujarBotones();
}

void PantallaPrincipal::actualizarPantalla() { this->menu.btnListeners(); }
