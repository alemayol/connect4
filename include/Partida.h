#pragma once

#include "AI.h"
#define PARTIDA_H
#include "EstadoSlot.h"
#include "Jugador.h"
#include "Modalidad.h"
#include "ModoDeJuego.h"
#include "Tablero.h"
#include <raylib.h>
#include <vector>

typedef struct {
  int puntosJ1;
  int puntosJ2;
} Marcador;

class Partida {
public:
  Partida(MODODEJUEGO modo, MODALIDAD modalidad, float screenWidth,
          float screenHeight);

  // Getters Setters
  int getTurno();

  // Metodos
  const ESTADO_SLOT (*getParrilla() const)[7];
  ESTADO_SLOT (*getParrilla())[7];
  Rectangle getLimitesTablero();
  bool getJuegoFinalizado();
  bool finalizarJuego();
  bool tableroLleno();
  // Tablero::ESTADO_SLOT **getParrilla();
  void colocarFicha();
  bool slotDisponible();
  void actualizarTablero();
  void inicializarTablero();
  bool verificarVictoria(ESTADO_SLOT jugador);
  bool existeGanador();
  void aumentarMarcador();

private:
  Tablero tablero;
  MODODEJUEGO modo;
  MODALIDAD modalidad;
  Marcador marcador;
  int turno;
  bool juegoFinalizado;
  AI jugador1;
  AI jugador2;
  ESTADO_SLOT parrilla[6][7];
};
