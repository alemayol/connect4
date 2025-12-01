#include "../../include/PantallaHistorial.h"
#include <raylib.h>
#include <string>

// Definimos estructura para facilitar la lectura y uso de los limites de los
// rectangulos de los botones del menu de la pantalla
typedef struct {
  Rectangle btnVolver;
  Rectangle btnPartidaGuardada;
} BtnsMenuHistorial;

// Constructores
PantallaHistorial::PantallaHistorial(GameState *globalState, float screenWidth,
                                     float screenHeight)
    : globalState(globalState), screenWidth(screenWidth),
      screenHeight(screenHeight) {

  BtnsMenuHistorial btns = {
      // Volver al menu principal
      {.x = 10, .y = 50, .width = 150, .height = 60},
      // Boton para cargar partida guardada
      {.x = screenWidth / 10 * 6,
       .y = screenHeight / 2 + 100,
       .width = 340,
       .height = 60},
  };

  this->menu.agregarBoton(Boton(btns.btnVolver, "Volver", BLUE, [this]() {
    // Cuando se haga click, se regresa al usuario a la pantalla principal
    this->globalState->setPantallaActual(GameState::PANTALLA_PRINCIPAL);
  }));
}

// Calculamos ancho de texto y lo colocamos en el centro del boton
Vector2 PantallaHistorial::calcularPosTexto(Rectangle rec, std::string texto) {
  int anchoTexto = MeasureText(texto.c_str(), 60);

  return {
      rec.x + (rec.width - anchoTexto) / 2,
      rec.y + (rec.height - 60) / 2,
  };
}

// Basado en el tamano de la pantalla del usuario calculamos y dibujamos la
// pantalla
void PantallaHistorial::dibujarPantalla(float screenWidth, float screenHeight) {

  // Establecemos datos estaticos como fuente, tamano de fuente, titulo y
  // espaciado de texto
  static const float fontSize = 60;
  static Font defaultFont = GetFontDefault();
  static const char *gameTitle = "Historial de Partidas";
  static const float spacing = 3.5f;

  Vector2 titleWidth =
      (MeasureTextEx(defaultFont, gameTitle, fontSize, spacing));
  int titleLocationX = (screenWidth - titleWidth.x) / 2;
  int titleLocationY = screenHeight / 12;

  // Dibujando titulos y  menu
  DrawTextEx(defaultFont, gameTitle,
             {(float)titleLocationX, (float)titleLocationY}, fontSize, spacing,
             DARKGRAY);

  this->menu.dibujarBotones();
}

// LLamamos a las funciones que actualizan el estado de los objetos necesarios
// en pantalla
void PantallaHistorial::actualizarPantalla() { this->menu.btnListeners(); }
