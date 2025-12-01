#include "../../include/PantallaSeleccionModo.h"

// Definimos estructura para facilitar la lectura y uso de los limites de los
// rectangulos de los botones del menu de la pantalla
typedef struct {
  Rectangle btnPrimeroA4;
  Rectangle btnAcumulado;
} BtnsModos;

// Constructores
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

  // Agregando botones al menu de la pantalla, en caso de click, se ajusta el
  // modo de juego elegido por el usuario en el estado global y se cambia de
  // pantalla
  this->menu.agregarBoton(
      Boton(dimension.btnPrimeroA4, "Primero a 4", BLUE, [this]() {
        this->globalState->setModoDeJuego(MODODEJUEGO::PRIMEROA4);
        this->globalState->setPantallaActual(GameState::SELECCION_MODALIDAD);
      }));
  this->menu.agregarBoton(
      Boton(dimension.btnAcumulado, "Modo Acumulado", BLUE, [this]() {
        this->globalState->setModoDeJuego(MODODEJUEGO::ACUMULADO);
        this->globalState->setPantallaActual(GameState::SELECCION_MODALIDAD);
      }));
};

void PantallaSeleccionModo::dibujarPantalla(float screenWidth,
                                            float screenHeight) {

  static const float fontSize = 60;
  static Font defaultFont = GetFontDefault();
  static const char *title = "Elija un modo de juego";
  static const float spacing = 3.5f;

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
