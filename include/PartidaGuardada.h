#pragma once

#define PARTIDAGUARDADA_H

#include "AI.h"
#include "EstadoSlot.h"
#include "Marcador.h"
#include "Modalidad.h"
#include "ModoDeJuego.h"
#include <fstream>
#include <string>
#include <vector>

class PartidaGuardada {
public:
  PartidaGuardada(Marcador marcador, MODODEJUEGO modo, MODALIDAD modalidad,
                  int turno, bool juegoFinalizado, ESTADO_SLOT (*tablero)[7]);
  static void serializarPartida(std::vector<PartidaGuardada> &memoryCard,
                                const std::string &nombreArchivo);
  static std::vector<PartidaGuardada>
  deserializarPartida(const std::string &nombreArchivo);
  Marcador getMarcador();
  MODODEJUEGO getModoDeJuego();
  MODALIDAD getModalidad();
  int getTurno();
  bool getJuegoFinalizado();
  ESTADO_SLOT (*getTablero())[7];

private:
  Marcador marcador;
  MODODEJUEGO modo;
  MODALIDAD modalidad;
  int turno;
  bool juegoFinalizado;
  ESTADO_SLOT parrilla[6][7];
};
