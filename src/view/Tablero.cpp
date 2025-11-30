#include "../../include/Tablero.h"
#include <algorithm>
#include <iostream>
#include <raylib.h>

Tablero::Tablero(float screenWidth, float screenHeight) {
  const float posTableroX = (screenWidth - 600) / 2;
  const float posTableroY = (screenHeight - 400) / 2;
  const float ancho = 600;
  const float alto = 400;

  this->limites = {posTableroX, posTableroY, ancho, alto};
};

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
        // colorSlot = (Color){255, 255, 0, 150};
        colorSlot = Fade(YELLOW, 0.5);
        break;
      case ESTADO_SLOT::POSIBLE2:
        // colorSlot = (Color){255, 0, 0, 150};

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

bool Tablero::actualizarTablero(ESTADO_SLOT (*parrilla)[7], int turno) {

  Vector2 posMouse = GetMousePosition();
  bool clicked = false;

  limpiarSugerencia(parrilla);

  if (CheckCollisionPointRec(posMouse, this->limites)) {

    int columna = (posMouse.x - this->limites.x) / (limites.width / 7);

    for (int i = 6 - 1; i >= 0; i--) {
      if (columna >= 0 && columna < 7 &&
          parrilla[i][columna] == ESTADO_SLOT::VACIO) {

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
          parrilla[i][columna] =
              turno % 2 != 0 ? ESTADO_SLOT::JUGADOR1 : ESTADO_SLOT::JUGADOR2;
          std::cout << "CLICK ON COL: " << columna << std::endl;
          std::cout << "Turno: " << turno << std::endl;
          std::cout << "Estado: " << (int)parrilla[i][columna] << std::endl;
          clicked = true;
          break;
        }

        parrilla[i][columna] =
            turno % 2 != 0 ? ESTADO_SLOT::POSIBLE1 : ESTADO_SLOT::POSIBLE2;
        break;
      }
    }
  }

  return clicked;
}

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

    // std::cout << "Columna: " << columna << std::endl;
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

/*
void Tablero::colocarFicha(Tablero::ESTADO_SLOT fichaJugador) {

  for (int i = 0; i < 6 * 7; i++) {
    int fila = i / 7;
    int colum = i % 7;

    if (fila >= 0 && fila < 6 && colum >= 0 && colum < 7) {
      this->parrilla[fila][colum] = fichaJugador;
    }
  }
}
*/
/*
bool Tablero::slotDisponible(int col, Tablero::ESTADO_SLOT fichaJugador) {
  if (col < 0 || col >= 7)
    return false; // Fuera de limites, se accederia a memoria fuera de nuestros
                  // limites

  static const int fila = 6;

  for (int i = fila - 1; i >= 0; i--) {
    if (this->parrilla[i][col] == ESTADO_SLOT::VACIO) {
      this->parrilla[i][col] = fichaJugador;
      return true;
    }
  }

  return false;
}*/
