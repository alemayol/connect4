#include "../../include/AI.h"
#include <cstdlib>

// Constructores de la clase
AI::AI() {}
AI::AI(ESTADO_SLOT rol) : rolDeJugador(rol) {}

// Validamos que la columna solicitada este dentro de los rangos del tablero
bool AI::columnaValida(ESTADO_SLOT (*parrilla)[7], int col) {

  static const int filas = 6;
  static const int columnas = 7;

  return (col >= 0 && col < columnas && parrilla[0][col] == ESTADO_SLOT::VACIO);
}

// Colocamos una ficha en el tablero 6x7 argumento
bool AI::colocarFicha(ESTADO_SLOT (*parrilla)[7], int col) {

  static const int filas = 6;
  static const int columnas = 7;

  // Chequeamos que la columna pasada sea valida para no acceder a memoria fuera
  // de limites
  if (!columnaValida(parrilla, col)) {
    return false;
  }

  // Se recorre el arreglo de forma vertical, marcando la ultima posicion libre
  // con el color de la ficha del jugador (rol)
  for (int i = filas - 1; i >= 0; i--) {

    if (col >= 0 && col < columnas && parrilla[i][col] == ESTADO_SLOT::VACIO) {
      parrilla[i][col] = this->rolDeJugador;
      return true;
    }
  }

  return false;
}

// Basado en la ficha pasada y la columna, elimina la ultima ficha colocada en
// el tablero en dicha columna y deja el slot en estado vacio
void AI::deshacerJugada(ESTADO_SLOT (*parrilla)[7], int col,
                        ESTADO_SLOT ficha) {

  static const int filas = 6;

  for (int i = 0; i < filas; i++) {
    if (parrilla[i][col] == ficha) {
      parrilla[i][col] = ESTADO_SLOT::VACIO;
      return;
    }
  }
}

// Determina si existe una linea de 4 fichas del mismo color en las direcciones
// permitidas, devuelve true de existir
bool AI::jugadaGanadora(ESTADO_SLOT (*parrilla)[7], ESTADO_SLOT ficha) {

  static const int filas = 6;
  static const int columnas = 7;

  // Horizontal
  for (int c = 0; c < filas - 3; c++) {
    for (int r = 0; r < filas; r++) {
      if (parrilla[r][c] == ficha && parrilla[r][c + 1] == ficha &&
          parrilla[r][c + 2] == ficha && parrilla[r][c + 3] == ficha)
        return true;
    }
  }
  // Vertical
  for (int c = 0; c < columnas; c++) {
    for (int r = 0; r < filas - 3; r++) {
      if (parrilla[r][c] == ficha && parrilla[r + 1][c] == ficha &&
          parrilla[r + 2][c] == ficha && parrilla[r + 3][c] == ficha)
        return true;
    }
  }
  // Diagonal Ascendente(/)
  for (int c = 0; c < columnas - 3; c++) {
    for (int r = 0; r < filas - 3; r++) { // Check from top-left down
      if (parrilla[r][c] == ficha && parrilla[r + 1][c + 1] == ficha &&
          parrilla[r + 2][c + 2] == ficha && parrilla[r + 3][c + 3] == ficha)
        return true;
    }
  }
  // Diagonal Descendente(\)
  for (int c = 0; c < columnas - 3; c++) {
    for (int r = 3; r < filas; r++) { // Check from bottom-left up
      if (parrilla[r][c] == ficha && parrilla[r - 1][c + 1] == ficha &&
          parrilla[r - 2][c + 2] == ficha && parrilla[r - 3][c + 3] == ficha)
        return true;
    }
  }
  return false;
}

// Retorna columna en la cual jugara
int AI::calcularJugada(ESTADO_SLOT (*parrilla)[7]) {

  static const int filas = 6;
  static const int columnas = 7;

  // Buscar victoria inmediata
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      if (colocarFicha(parrilla, j)) {
        if (jugadaGanadora(parrilla, this->rolDeJugador)) {
          deshacerJugada(parrilla, j, this->rolDeJugador);
          return j;
        }

        deshacerJugada(parrilla, j, this->rolDeJugador);
      }
    }
  }
  // Buscar bloquear a oponente en caso de victoria inmediata
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      if (colocarFichaOp(parrilla, j)) {

        ESTADO_SLOT ficha = this->rolDeJugador == ESTADO_SLOT::JUGADOR1
                                ? ESTADO_SLOT::JUGADOR2
                                : ESTADO_SLOT::JUGADOR1;
        if (jugadaGanadora(parrilla, ficha)) {
          deshacerJugada(parrilla, j, ficha);
          return j;
        }

        deshacerJugada(parrilla, j, ficha);
      }
    }
  }

  // CENTRO
  if (columnaValida(parrilla, 3))
    return 3;

  // RANDOM
  int col;
  do {
    col = rand() % 7;
  } while (!columnaValida(parrilla, col));
  return col;
}

// Colacamos la ficha del oponente en el tablero (utilizado para calcular una
// posible victoria del rival)
bool AI::colocarFichaOp(ESTADO_SLOT (*parrilla)[7], int col) {

  static const int filas = 6;
  static const int columnas = 7;

  if (!columnaValida(parrilla, col)) {
    return false;
  }

  // Basado en el rol de la AI actual, determinamos la ficha del oponente
  ESTADO_SLOT ficha = this->rolDeJugador == ESTADO_SLOT::JUGADOR1
                          ? ESTADO_SLOT::JUGADOR2
                          : ESTADO_SLOT::JUGADOR1;

  for (int i = filas - 1; i >= 0; i--) {

    if (col >= 0 && col < columnas && parrilla[i][col] == ESTADO_SLOT::VACIO) {
      parrilla[i][col] = ficha;
      return true;
    }
  }

  return false;
}
