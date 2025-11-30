#include "../../include/Partida.h"
#include "../../include/AI.h"
#include <chrono>
#include <iostream>
#include <raylib.h>
#include <thread>

Partida::Partida(MODODEJUEGO modo, MODALIDAD modalidad, float screenWidth,
                 float screenHeight)
    : tablero(screenWidth, screenHeight), modo(modo), modalidad(modalidad),
      turno(1), marcador({0, 0}) {

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      this->parrilla[i][j] = ESTADO_SLOT::VACIO;
    }
  }

  if (modalidad == MODALIDAD::HVSIA) {
    this->jugador2 = AI();
  } else if (modalidad == MODALIDAD::IAVSIA) {
    this->jugador1 = AI();
    this->jugador2 = AI();
  }
}

void Partida::colocarFicha() {}

const ESTADO_SLOT (*Partida::getParrilla() const)[7] { return this->parrilla; };

ESTADO_SLOT (*Partida::getParrilla())[7] { return this->parrilla; };

Rectangle Partida::getLimitesTablero() { return this->tablero.getLimites(); }

void Partida::inicializarTablero() {

  this->tablero.dibujarTablero(this->parrilla);
}

int Partida::getTurno() { return this->turno; }

bool Partida::getExisteGanador() { return this->existeGanador; }

void Partida::aumentarMarcador() {

  bool conecto4 = this->turno % 2 != 0
                      ? this->verificarVictoria(ESTADO_SLOT::JUGADOR2)
                      : this->verificarVictoria(ESTADO_SLOT::JUGADOR1);

  ESTADO_SLOT puntoAJugador =
      this->turno % 2 != 0 ? ESTADO_SLOT::JUGADOR2 : ESTADO_SLOT::JUGADOR1;

  if (conecto4) {

    if (puntoAJugador == ESTADO_SLOT::JUGADOR1) {
      this->marcador.puntosJ1++;
    } else if (puntoAJugador == ESTADO_SLOT::JUGADOR2) {
      this->marcador.puntosJ2++;
    }

    std::cout << "Conecto 4" << std::endl;
    std::cout << "Marcador" << std::endl;
    std::cout << "J1: " << this->marcador.puntosJ1 << std::endl;
    std::cout << "J2: " << this->marcador.puntosJ2 << std::endl;

    if (this->finalizarJuego()) {

      std::cout << "JUEGO FINALIZADO" << std::endl;
      this->existeGanador = true;
      return;
    }
  }
}

bool Partida::tableroLleno() {

  bool existeSlotVacio = false;

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      if (this->parrilla[i][j] == ESTADO_SLOT::VACIO ||
          this->parrilla[i][j] == ESTADO_SLOT::POSIBLE1 ||
          this->parrilla[i][j] == ESTADO_SLOT::POSIBLE2) {
        existeSlotVacio = true;
        std::cout << "Existe slot vacio: " << existeSlotVacio << std::endl;
        break;
      }
    }
  }

  return existeSlotVacio;
}

bool Partida::finalizarJuego() {
  if (this->modo == MODODEJUEGO::PRIMEROA4) {

    if (this->marcador.puntosJ1 == 1 || this->marcador.puntosJ2 == 1) {
      std::cout << "Modo de juego primero a 4" << std::endl;
      return true;
    }
  }

  if (this->modo == MODODEJUEGO::ACUMULADO) {

    std::cout << "Modo de juego acumulado" << std::endl;
    return !this->tableroLleno();
  }

  return false;
}

void Partida::actualizarTablero() {

  if (this->modalidad == MODALIDAD::HVSH) {

    bool pasoTurno =
        this->tablero.actualizarTablero(this->parrilla, this->turno);
    if (pasoTurno) {

      this->turno = this->turno + 1;
      this->aumentarMarcador();
    }

  } else if (this->modalidad == MODALIDAD::HVSIA) {
    if (this->turno % 2 != 0) {
      bool pasoTurno =
          this->tablero.actualizarTablero(this->parrilla, this->turno);
      if (pasoTurno) {
        this->turno = this->turno + 1;
        this->aumentarMarcador();
      }
    } else {

      std::this_thread::sleep_for(
          std::chrono::milliseconds(500)); // Sleeps for 1 second

      int col = this->jugador2.calcularJugada(this->parrilla);

      std::cout << "Columna calculada: " << col << std::endl;
      this->tablero.actualizarTableroAi(this->parrilla, col);
      this->turno = this->turno + 1;
      this->aumentarMarcador();
    }
  } else if (this->modalidad == MODALIDAD::IAVSIA) {

    // int col = this->jugador2.calcularJugada(this->parrilla);
    // this->tablero.actualizarTableroAi(this->parrilla, col);
  }
}

bool Partida::verificarVictoria(ESTADO_SLOT jugador) {

  static const int filas = 6;
  static const int columnas = 7;

  // Horizontal
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas - 3; j++) {
      if (this->parrilla[i][j] == jugador &&
          this->parrilla[i][j + 1] == jugador &&
          this->parrilla[i][j + 2] == jugador &&
          this->parrilla[i][j + 3] == jugador) {

        if (jugador == ESTADO_SLOT::JUGADOR1) {
          this->parrilla[i][j] = ESTADO_SLOT::CONECTAJ1;
          this->parrilla[i][j + 1] = ESTADO_SLOT::CONECTAJ1;
          this->parrilla[i][j + 2] = ESTADO_SLOT::CONECTAJ1;
          this->parrilla[i][j + 3] = ESTADO_SLOT::CONECTAJ1;
        } else {

          this->parrilla[i][j] = ESTADO_SLOT::CONECTAJ2;
          this->parrilla[i][j + 1] = ESTADO_SLOT::CONECTAJ2;
          this->parrilla[i][j + 2] = ESTADO_SLOT::CONECTAJ2;
          this->parrilla[i][j + 3] = ESTADO_SLOT::CONECTAJ2;
        }
        return true;
      }
    }
  }
  // Vertical
  for (int i = 0; i < filas - 3; i++) {
    for (int j = 0; j < columnas; j++) {
      if (this->parrilla[i][j] == jugador &&
          this->parrilla[i + 1][j] == jugador &&
          this->parrilla[i + 2][j] == jugador &&
          this->parrilla[i + 3][j] == jugador) {

        if (jugador == ESTADO_SLOT::JUGADOR1) {
          this->parrilla[i][j] = ESTADO_SLOT::CONECTAJ1;
          this->parrilla[i + 1][j] = ESTADO_SLOT::CONECTAJ1;
          this->parrilla[i + 2][j] = ESTADO_SLOT::CONECTAJ1;
          this->parrilla[i + 3][j] = ESTADO_SLOT::CONECTAJ1;
        } else {

          this->parrilla[i][j] = ESTADO_SLOT::CONECTAJ2;
          this->parrilla[i + 1][j] = ESTADO_SLOT::CONECTAJ2;
          this->parrilla[i + 2][j] = ESTADO_SLOT::CONECTAJ2;
          this->parrilla[i + 3][j] = ESTADO_SLOT::CONECTAJ2;
        }

        return true;
      }
    }
  }
  // Diagonal \ (Descendente)
  for (int i = 0; i < filas - 3; i++) {
    for (int j = 0; j < columnas - 3; j++) {
      if (this->parrilla[i][j] == jugador &&
          this->parrilla[i + 1][j + 1] == jugador &&
          this->parrilla[i + 2][j + 2] == jugador &&
          this->parrilla[i + 3][j + 3] == jugador) {

        if (jugador == ESTADO_SLOT::JUGADOR1) {
          this->parrilla[i][j] = ESTADO_SLOT::CONECTAJ1;
          this->parrilla[i + 1][j + 1] = ESTADO_SLOT::CONECTAJ1;
          this->parrilla[i + 2][j + 2] = ESTADO_SLOT::CONECTAJ1;
          this->parrilla[i + 3][j + 3] = ESTADO_SLOT::CONECTAJ1;
        } else {

          this->parrilla[i][j] = ESTADO_SLOT::CONECTAJ2;
          this->parrilla[i + 1][j + 1] = ESTADO_SLOT::CONECTAJ2;
          this->parrilla[i + 2][j + 2] = ESTADO_SLOT::CONECTAJ2;
          this->parrilla[i + 3][j + 3] = ESTADO_SLOT::CONECTAJ2;
        }

        return true;
      }
    }
  }
  // Diagonal / (Ascendente)
  for (int i = 3; i < filas; i++) {
    for (int j = 0; j < columnas - 3; j++) {
      if (this->parrilla[i][j] == jugador &&
          this->parrilla[i - 1][j + 1] == jugador &&
          this->parrilla[i - 2][j + 2] == jugador &&
          this->parrilla[i - 3][j + 3] == jugador) {

        if (jugador == ESTADO_SLOT::JUGADOR1) {
          this->parrilla[i][j] = ESTADO_SLOT::CONECTAJ1;
          this->parrilla[i - 1][j + 1] = ESTADO_SLOT::CONECTAJ1;
          this->parrilla[i - 2][j + 2] = ESTADO_SLOT::CONECTAJ1;
          this->parrilla[i - 3][j + 3] = ESTADO_SLOT::CONECTAJ1;
        } else {

          this->parrilla[i][j] = ESTADO_SLOT::CONECTAJ2;
          this->parrilla[i - 1][j + 1] = ESTADO_SLOT::CONECTAJ2;
          this->parrilla[i - 2][j + 2] = ESTADO_SLOT::CONECTAJ2;
          this->parrilla[i - 3][j + 3] = ESTADO_SLOT::CONECTAJ2;
        }

        return true;
      }
    }
  }
  return false;
};
