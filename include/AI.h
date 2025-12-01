#pragma once

#define AI_H
#include "EstadoSlot.h"

class AI {
public:
  AI();
  AI(ESTADO_SLOT rol);
  bool posibleVictoriaOp(ESTADO_SLOT (*parrilla)[7]);
  bool colocarFicha(ESTADO_SLOT (*parrilla)[7], int col);
  bool colocarFichaOp(ESTADO_SLOT (*parrilla)[7], int col);
  bool columnaValida(ESTADO_SLOT (*parrilla)[7], int col);
  void deshacerJugada(ESTADO_SLOT (*parrilla)[7], int col, ESTADO_SLOT ficha);
  bool jugadaGanadora(ESTADO_SLOT (*parrilla)[7], ESTADO_SLOT ficha);
  int calcularJugada(ESTADO_SLOT (*parrilla)[7]);

private:
  ESTADO_SLOT rolDeJugador;
};
