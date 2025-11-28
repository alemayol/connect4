#pragma once

#define GAMESTATE_H

#include "Partida.h"

class GameState {
private:
public:
  GameState();
  enum MODODEJUEGO { NINGUNO = 0, PRIMEROA4, ACUMULADO };
  enum MODALIDAD { NINGUNA = 0, HVSH, HVSIA, IAVSIA };
  enum PANTALLA {
    PANTALLA_PRINCIPAL = 0,
    SELECCION_MODO,
    SELECCION_MODALIDAD,
    PARTIDA
  };

  // Setters Getters
  void setPartidaActual(Partida *nuevaPartida);
  void setModoDeJuego(MODODEJUEGO modo);
  void setModalidad(MODALIDAD modalidad);
  void setPantallaActual(PANTALLA pantallaActual);
  PANTALLA getPantallaActual();
  void setSalirDelJuego(bool salirDeJuego);
  bool getSalirDelJuego();

private:
  Partida *partidaActual;
  MODODEJUEGO modo;
  MODALIDAD modalidad;
  PANTALLA pantallaActual;
  bool salirDelJuego;
};
