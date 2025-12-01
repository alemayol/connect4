#include "../../include/PantallaSeleccionModalidad.h"
#include <raylib.h>

// Definimos estructura para facilitar la lectura y uso de los limites de los
// rectangulos de los botones del menu de la pantalla
typedef struct {
  Rectangle btnHvsH;
  Rectangle btnHvsIa;
  Rectangle btnIavsIa;
} BtnsModalidad;

// Constructores
PantallaSeleccionModalidad::PantallaSeleccionModalidad(GameState *globalState,
                                                       float screenWidth,
                                                       float screenHeight) {
  this->globalState = globalState;

  BtnsModalidad dimensiones = {
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

  // Agregando botones al menu de la pantalla, en caso de click, se ajusta la
  // modalidad elegida por el usuario en el estado global
  this->menu.agregarBoton(
      Boton(dimensiones.btnHvsH, "Jugador vs Jugador", BLUE,
            [this, screenWidth, screenHeight]() {
              this->globalState->setPantallaActual(GameState::PARTIDA);

              this->globalState->setPartidaActual(
                  new Partida(this->globalState->getModoDeJuego(),
                              MODALIDAD::HVSH, screenWidth, screenHeight));
              this->globalState->setModalidad(MODALIDAD::HVSH);
            }));
  this->menu.agregarBoton(
      Boton(dimensiones.btnHvsIa, "Jugador vs Ia", BLUE,
            [this, screenWidth, screenHeight]() {
              this->globalState->setPantallaActual(GameState::PARTIDA);

              this->globalState->setPartidaActual(
                  new Partida(this->globalState->getModoDeJuego(),
                              MODALIDAD::HVSIA, screenWidth, screenHeight));
              this->globalState->setModalidad(MODALIDAD::HVSIA);
            }));
  this->menu.agregarBoton(
      Boton(dimensiones.btnIavsIa, "Ia vs Ia", BLUE,
            [this, screenWidth, screenHeight]() {
              this->globalState->setPantallaActual(GameState::PARTIDA);

              this->globalState->setPartidaActual(
                  new Partida(this->globalState->getModoDeJuego(),
                              MODALIDAD::IAVSIA, screenWidth, screenHeight));
              this->globalState->setModalidad(MODALIDAD::IAVSIA);
            }));
};

// Basado en el tamano de la pantalla del usuario calculamos y dibujamos la
// pantalla
void PantallaSeleccionModalidad::dibujarPantalla(float screenWidth,
                                                 float screenHeight) {

  static const float fontSize = 60;
  static Font defaultFont = GetFontDefault();
  static const char *gameTitle = "Elija una modalidad";
  static const float spacing = 3.5f;

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

void PantallaSeleccionModalidad::actualizarPantalla() {
  this->menu.btnListeners();
}
