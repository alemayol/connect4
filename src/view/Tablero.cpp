#include "../../include/Tablero.h"
#include <algorithm>
#include <raylib.h>

// Constructores
Tablero::Tablero(float screenWidth, float screenHeight) {
  const float posTableroX = (screenWidth - 600) / 2;
  const float posTableroY = (screenHeight - 400) / 2;
  const float ancho = 600;
  const float alto = 400;

  this->limites = {posTableroX, posTableroY, ancho, alto};
};

// Basado en la matriz argumento (la cual espera ser de 7 columnas) se dibuja el
// cuadro principal representando el tablero y luego subsecuentes circulos
// "transparentes" que indican un slot vacio. En caso de que la matriz tenga
// valores de las fichas de los jugadores, pinta circulos del color
// correspondiente
void Tablero::dibujarTablero(ESTADO_SLOT (*parrilla)[7]) {

  Rectangle sombra = limites;
  Rectangle bordeSuperior = this->limites;

  sombra.height += 4.0;
  bordeSuperior.height -= 4.0;

  DrawRectangleRounded(sombra, 0.05, 6, (Color){0, 0, 0, 100});
  DrawRectangleRounded(bordeSuperior, 0.05, 6, LIGHTGRAY);
  DrawRectangleRounded(this->limites, 0.05, 6, DARKBLUE);

  static const int fila = 6;
  static const int col = 7;

  float anchoCelda = this->limites.width / col;  // 7 columnas
  float altoCelda = this->limites.height / fila; // 6 filas
  float radioSlot = std::min(anchoCelda, altoCelda) * 0.4f;

  for (int i = 0; i < fila; i++) {
    for (int j = 0; j < col; j++) {
      float posX = limites.x + (j * anchoCelda) + (anchoCelda / 2);
      float posY = limites.y + (i * altoCelda) + (altoCelda / 2);

      Color colorSlot;

      switch (parrilla[i][j]) {
      case ESTADO_SLOT::VACIO:

        colorSlot = RAYWHITE;
        break;
      case ESTADO_SLOT::JUGADOR1:
        colorSlot = YELLOW;

        break;
      case ESTADO_SLOT::JUGADOR2:
        colorSlot = RED;

        break;
      case ESTADO_SLOT::POSIBLE1:
        colorSlot = Fade(YELLOW, 0.5);
        break;
      case ESTADO_SLOT::POSIBLE2:

        colorSlot = Fade(RED, 0.5);
        break;
      case ESTADO_SLOT::CONECTAJ1:

        colorSlot = YELLOW;
        break;
      case ESTADO_SLOT::CONECTAJ2:

        colorSlot = RED;
        break;
      }
      DrawCircle(posX, posY, radioSlot, colorSlot);
    }
  }
}

// Ya que modificamos el arreglo para hacer sugerencias visuales al usuario,
// debemos restaurarlo para no dar falsos positivos cuando se verifique espacios
// vacios en la matriz
void Tablero::limpiarSugerencia(ESTADO_SLOT (*parrilla)[7]) {

  static const int fila = 6;
  static const int col = 7;

  for (int i = 0; i < fila; i++) {
    for (int j = 0; j < col; j++) {
      if (parrilla[i][j] == ESTADO_SLOT::POSIBLE1 ||
          parrilla[i][j] == ESTADO_SLOT::POSIBLE2) {
        parrilla[i][j] = ESTADO_SLOT::VACIO;
      }
    }
  }
}

// Calculamos la posicion y accion del mouse del usuario efectuamos las
// operaciones necesarias
bool Tablero::actualizarTablero(ESTADO_SLOT (*parrilla)[7], int turno) {

  Vector2 posMouse = GetMousePosition();
  bool clicked = false;

  limpiarSugerencia(parrilla);

  if (CheckCollisionPointRec(posMouse, this->limites)) {

    // Calculamos los limites que tiene una columna para saber cuando el usuario
    // sobrepone el mouse sobre las distintas columnas
    int columna = (posMouse.x - this->limites.x) / (limites.width / 7);

    for (int i = 6 - 1; i >= 0; i--) {
      if (columna >= 0 && columna < 7 &&
          parrilla[i][columna] == ESTADO_SLOT::VACIO) {

        // Si existe un click se cambia la variable bandera para indicar que se
        // debe cambiar de turno en la partida
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
          parrilla[i][columna] =
              turno % 2 != 0 ? ESTADO_SLOT::JUGADOR1 : ESTADO_SLOT::JUGADOR2;
          clicked = true;
          break;
        }

        // Colocando sugerencia al usuario, color depende del turno
        parrilla[i][columna] =
            turno % 2 != 0 ? ESTADO_SLOT::POSIBLE1 : ESTADO_SLOT::POSIBLE2;
        break;
      }
    }
  }

  return clicked;
}

// Funcion utilizada por la AI para colocar una ficha
void Tablero::actualizarTableroAi(ESTADO_SLOT (*parrilla)[7], int col,
                                  ESTADO_SLOT ficha) {

  for (int i = 6 - 1; i >= 0; i--) {
    if (col >= 0 && col < 7 && parrilla[i][col] == ESTADO_SLOT::VACIO) {
      parrilla[i][col] = ficha;
      break;
    }
  }
}

// Static
void Tablero::dibujarTablero(Rectangle rec, const ESTADO_SLOT (*parrilla)[7]) {

  Rectangle sombra = rec;
  Rectangle bordeSuperior = rec;

  sombra.height += 4.0;
  bordeSuperior.height -= 4.0;

  DrawRectangleRounded(sombra, 0.05, 6, (Color){0, 0, 0, 100});
  DrawRectangleRounded(bordeSuperior, 0.05, 6, LIGHTGRAY);
  DrawRectangleRounded(rec, 0.05, 6, DARKBLUE);

  static const int fila = 6;
  static const int col = 7;

  float anchoCelda = rec.width / col;  // 7 columnas
  float altoCelda = rec.height / fila; // 6 filas
  float radioSlot = std::min(anchoCelda, altoCelda) * 0.4f;

  for (int i = 0; i < fila; i++) {
    for (int j = 0; j < col; j++) {
      float posX = rec.x + (j * anchoCelda) + (anchoCelda / 2);
      float posY = rec.y + (i * altoCelda) + (altoCelda / 2);

      Color colorSlot;

      switch (parrilla[i][j]) {
      case ESTADO_SLOT::VACIO:

        colorSlot = RAYWHITE;
        break;
      case ESTADO_SLOT::JUGADOR1:
        colorSlot = YELLOW;

        break;
      case ESTADO_SLOT::JUGADOR2:
        colorSlot = RED;

        break;
      case ESTADO_SLOT::POSIBLE1:
        colorSlot = Fade(YELLOW, 0.5);
        break;
      case ESTADO_SLOT::POSIBLE2:

        colorSlot = Fade(RED, 0.5);
        break;
      case ESTADO_SLOT::CONECTAJ1:

        colorSlot = YELLOW;
        break;
      case ESTADO_SLOT::CONECTAJ2:

        colorSlot = RED;
        break;
      }
      DrawCircle(posX, posY, radioSlot, colorSlot);
    }
  }
}

void Tablero::actualizarTablero(Rectangle rec, ESTADO_SLOT (*parrilla)[7],
                                int turno) {

  Vector2 posMouse = GetMousePosition();

  if (CheckCollisionPointRec(posMouse, rec)) {

    int columna = (posMouse.x - rec.x) / (rec.width / 7);

    for (int i = 6 - 1; i >= 0; i--) {
      if (columna >= 0 && columna < 7 &&
          parrilla[i][columna] == ESTADO_SLOT::VACIO) {

        parrilla[i][columna] = ESTADO_SLOT::POSIBLE1;
        break;
      }
    }
  }
}

Rectangle Tablero::getLimites() { return this->limites; }
