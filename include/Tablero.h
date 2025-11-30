#pragma once

#define TABLERO_H
#include "EstadoSlot.h"
#include <raylib.h>
#include <vector>

const Color slotVacio = RAYWHITE;
const Color slotJugador1 = BLUE;
const Color slotJugador2 = RED;

class Tablero {
public:
  Tablero(float screenWidth, float screenHeight);

  // Metodos
  void dibujarTablero(ESTADO_SLOT (*parrilla)[7]);
  bool actualizarTablero(ESTADO_SLOT (*parrilla)[7], int turno);
  void actualizarTableroAi(ESTADO_SLOT (*parrilla)[7], int col,
                           ESTADO_SLOT ficha);
  static void dibujarTablero(Rectangle rec, const ESTADO_SLOT (*parrilla)[7]);
  static void actualizarTablero(Rectangle rec, ESTADO_SLOT (*parrilla)[7],
                                int turno);
  void colocarFicha(ESTADO_SLOT fichaJugador);
  bool slotDisponible(int col, ESTADO_SLOT fichaJugador);
  Rectangle getLimites();
  void limpiarSugerencia(ESTADO_SLOT (*parrilla)[7]);

private:
  Rectangle limites;
  const int filas = 6;
  const int col = 7;
  Color colorTablero;
  Color colorSlot;
};
