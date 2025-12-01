#pragma once

#define PARTIDA_H
#include "AI.h"
#include "EstadoSlot.h"
#include "Marcador.h"
#include "Modalidad.h"
#include "ModoDeJuego.h"
#include "Tablero.h"
#include <raylib.h>
#include <vector>

class Partida {
public:
  Partida(MODODEJUEGO modo, MODALIDAD modalidad, float screenWidth,
          float screenHeight);

  Partida(MODODEJUEGO modo, MODALIDAD modalidad, ESTADO_SLOT (*tablero)[7],
          Marcador marcador, int turno, float screenWidth, float screenHeight);

  // Getters Setters
  int getTurno();

  // Metodos
  const ESTADO_SLOT (*getParrilla() const)[7];
  ESTADO_SLOT (*getParrilla())[7];
  Rectangle getLimitesTablero();
  bool getJuegoFinalizado();
  Marcador getMarcador();
  MODODEJUEGO getModoDeJuego();
  MODALIDAD getModalidad();
  bool getFinalizado();
  bool finalizarJuego();
  bool tableroLleno();
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
