#include "../../include/Partida.h"
#include "../../include/AI.h"
#include <chrono>
#include <raylib.h>
#include <thread>

// Constructores
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
    this->jugador2 = AI(ESTADO_SLOT::JUGADOR2);
  } else if (modalidad == MODALIDAD::IAVSIA) {
    this->jugador1 = AI(ESTADO_SLOT::JUGADOR1);
    this->jugador2 = AI(ESTADO_SLOT::JUGADOR2);
  }
}

// Constructor para reecrear partida a partir de una partida guardada
Partida::Partida(MODODEJUEGO modo, MODALIDAD modalidad, ESTADO_SLOT (*grid)[7],
                 Marcador marcador, int turno, float screenWidth,
                 float screenHeight)
    : tablero(screenWidth, screenHeight), modo(modo), modalidad(modalidad),
      turno(turno), marcador(marcador) {

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      this->parrilla[i][j] = grid[i][j];
    }
  }

  if (modalidad == MODALIDAD::HVSIA) {
    this->jugador2 = AI(ESTADO_SLOT::JUGADOR2);
  } else if (modalidad == MODALIDAD::IAVSIA) {
    this->jugador1 = AI(ESTADO_SLOT::JUGADOR1);
    this->jugador2 = AI(ESTADO_SLOT::JUGADOR2);
  }
}

// Setters Getters

const ESTADO_SLOT (*Partida::getParrilla() const)[7] { return this->parrilla; };

ESTADO_SLOT (*Partida::getParrilla())[7] { return this->parrilla; };

Rectangle Partida::getLimitesTablero() { return this->tablero.getLimites(); }

int Partida::getTurno() { return this->turno; }

bool Partida::getJuegoFinalizado() { return this->juegoFinalizado; }

Marcador Partida::getMarcador() { return this->marcador; }
MODODEJUEGO Partida::getModoDeJuego() { return this->modo; }
MODALIDAD Partida::getModalidad() { return this->modalidad; }
bool Partida::getFinalizado() { return this->juegoFinalizado; }

// Metodos

// Enviamos la señal para dibujar el tablero connect 4 en pantalla, utilizando
// el tablero guardado en el objeto Partida
void Partida::inicializarTablero() {

  this->tablero.dibujarTablero(this->parrilla);
}

// Basado en la condicion del turno actual de la partida, verificamos si existe
// una linea de 4 fichas del jugador cuyo turno ya paso. Es decir, luego de
// jugar el jugador 1, el turno aumenta y se verifica la victoria del jugador 1
void Partida::aumentarMarcador() {

  bool conecto4 = this->turno % 2 != 0
                      ? this->verificarVictoria(ESTADO_SLOT::JUGADOR2)
                      : this->verificarVictoria(ESTADO_SLOT::JUGADOR1);

  ESTADO_SLOT puntoAJugador =
      this->turno % 2 != 0 ? ESTADO_SLOT::JUGADOR2 : ESTADO_SLOT::JUGADOR1;

  // Si se encontro una linea de 4 en el tablero, se le asigna un punto al
  // marcador del jugador correspondiente, calculado a partir del turno
  if (conecto4) {

    if (puntoAJugador == ESTADO_SLOT::JUGADOR1) {
      this->marcador.puntosJ1++;
    } else if (puntoAJugador == ESTADO_SLOT::JUGADOR2) {
      this->marcador.puntosJ2++;
    }
  }
}

// Determina a traves de la funcion finalizarJuego si se acabo el juego, de ser
// cierto, se hace un set de true a la propiedad juegoFinalizado
bool Partida::existeGanador() {
  if (this->finalizarJuego()) {

    this->juegoFinalizado = true;
    return true;
  }

  return false;
}

// Determina si el tablero no tiene espacios disponibles donde jugar
bool Partida::tableroLleno() {

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      // Agregamos los estados POSIBLE1 y POSIBLE2 ya que modificamos el tablero
      // con esos valores para dar indicaciones al usuario pero estas pueden dar
      // un falso positivo para el tablero lleno
      if (this->parrilla[i][j] == ESTADO_SLOT::VACIO ||
          this->parrilla[i][j] == ESTADO_SLOT::POSIBLE1 ||
          this->parrilla[i][j] == ESTADO_SLOT::POSIBLE2) {
        return false;
      }
    }
  }

  return true;
}

// Determina de acuerdo al modo de juego si la partida debe finalizar
bool Partida::finalizarJuego() {
  // Modo primero a 4, la primera linea de 4 finaliza el juego; o si se lleno el
  // tablero antes de que existiese una linea de 4
  if (this->modo == MODODEJUEGO::PRIMEROA4) {

    if (this->marcador.puntosJ1 == 1 || this->marcador.puntosJ2 == 1 ||
        this->tableroLleno()) {
      return true;
    }
  }
  // Modo acumulado, finaliza el juego unicamente cuando no existen espacios
  // disponibles en el tablero (2d array)
  else if (this->modo == MODODEJUEGO::ACUMULADO) {

    return this->tableroLleno();
  }

  return false;
}

// Basado en la modalidad de la partida, actualizamos el tablero segun el turno
// que corresponda
void Partida::actualizarTablero() {

  if (this->modalidad == MODALIDAD::HVSH) {

    bool pasoTurno =
        this->tablero.actualizarTablero(this->parrilla, this->turno);
    if (pasoTurno) {

      this->turno = this->turno + 1;
      this->aumentarMarcador();
      this->existeGanador();
    }

  } else if (this->modalidad == MODALIDAD::HVSIA) {
    if (this->turno % 2 != 0) {
      bool pasoTurno =
          this->tablero.actualizarTablero(this->parrilla, this->turno);
      if (pasoTurno) {
        this->turno = this->turno + 1;
        this->aumentarMarcador();
        this->existeGanador();
      }
    } else {

      int col = this->jugador2.calcularJugada(this->parrilla);

      this->tablero.actualizarTableroAi(this->parrilla, col,
                                        ESTADO_SLOT::JUGADOR2);
      this->turno = this->turno + 1;
      this->aumentarMarcador();
      this->existeGanador();

      // Para fingir pensamiento de la AI, puede ser al azar para añadir
      // realismo (por hacer)
      std::this_thread::sleep_for(
          std::chrono::milliseconds(500)); // Detener proceso por x segundos
    }
  } else if (this->modalidad == MODALIDAD::IAVSIA) {

    if (this->turno % 2 != 0) {

      int col = this->jugador1.calcularJugada(this->parrilla);
      this->tablero.actualizarTableroAi(this->parrilla, col,
                                        ESTADO_SLOT::JUGADOR1);

      this->turno = this->turno + 1;

      this->aumentarMarcador();
      this->existeGanador();
    } else {

      int col = this->jugador2.calcularJugada(this->parrilla);
      this->tablero.actualizarTableroAi(this->parrilla, col,
                                        ESTADO_SLOT::JUGADOR2);

      this->turno = this->turno + 1;

      this->aumentarMarcador();
      this->existeGanador();
    }

    std::this_thread::sleep_for(
        std::chrono::milliseconds(500)); // Detener proceso por x segundos
  }
}

// Parecido a jugadaGanadora, verifica en todas las direcciones permitidas si el
// jugador argumento conecto 4, de ser cierto convierte las fichas en fichas del
// mismo color pero que no serán contadas para aumentar el marcador en futuras
// jugadas
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
