#pragma once

#define GAMESTATE_H
#include "Modalidad.h"
#include "ModoDeJuego.h"
#include "PartidaGuardada.h"
#include <vector>

#include "Partida.h"

class GameState {
private:
public:
  GameState(std::vector<PartidaGuardada> memoryCard);
  enum PANTALLA {
    PANTALLA_PRINCIPAL = 0,
    SELECCION_MODO,
    SELECCION_MODALIDAD,
    PARTIDA,
    PANTALLA_HISTORIAL
  };

  // Setters Getters
  void setPartidaActual(Partida *nuevaPartida);
  Partida *getPartidaActual();
  void setModoDeJuego(MODODEJUEGO modo);
  MODODEJUEGO getModoDeJuego();
  void setModalidad(MODALIDAD modalidad);
  MODALIDAD getModalidad();
  void setPantallaActual(PANTALLA pantallaActual);
  PANTALLA getPantallaActual();
  void setSalirDelJuego(bool salirDeJuego);
  bool getSalirDelJuego();
  std::vector<PartidaGuardada> getMemoryCard();
  void pushMemoryCard(Partida *partidaAGuardar);
  std::vector<Partida> getLastSavedGame();

private:
  Partida *partidaActual;
  MODODEJUEGO modo;
  MODALIDAD modalidad;
  PANTALLA pantallaActual;
  bool salirDelJuego;
  std::vector<PartidaGuardada> memoryCard;
};
