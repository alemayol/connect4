#include "../../include/GameState.h"
#include <vector>

// Constructores
GameState::GameState(std::vector<PartidaGuardada> memoryCard) {
  this->partidaActual = nullptr;
  this->modo = NINGUNO;
  this->modalidad = NINGUNA;
  this->pantallaActual = PANTALLA_PRINCIPAL;
  this->memoryCard = memoryCard;
}

// Setters Getters

void GameState::setPartidaActual(Partida *nuevaPartida) {
  this->partidaActual = nuevaPartida;
}

Partida *GameState::getPartidaActual() { return this->partidaActual; }

void GameState::setModoDeJuego(MODODEJUEGO modo) { this->modo = modo; };
MODODEJUEGO GameState::getModoDeJuego() { return this->modo; };

void GameState::setModalidad(MODALIDAD modalidad) {
  this->modalidad = modalidad;
};

MODALIDAD GameState::getModalidad() { return this->modalidad; };

void GameState::setPantallaActual(PANTALLA pantallaActual) {
  this->pantallaActual = pantallaActual;
};

GameState::PANTALLA GameState::getPantallaActual() {
  return this->pantallaActual;
};

void GameState::setSalirDelJuego(bool salir) { this->salirDelJuego = salir; };
bool GameState::getSalirDelJuego() { return this->salirDelJuego; };

std::vector<PartidaGuardada> GameState::getMemoryCard() {
  return this->memoryCard;
}

// Metodos

// Obtenemos las partidas guardadas en el estado global y retornamos un vector
// con dichas partidas
std::vector<Partida> GameState::getLastSavedGame() {

  std::vector<Partida> partidas;

  float screenWidth = GetScreenWidth();
  float screenHeight = GetScreenHeight();

  for (PartidaGuardada partida : this->memoryCard) {

    if (!partida.getJuegoFinalizado()) {

      Partida nuevaPartida =
          Partida(partida.getModoDeJuego(), partida.getModalidad(),
                  partida.getTablero(), partida.getMarcador(),
                  partida.getTurno(), screenWidth, screenHeight);

      partidas.push_back(nuevaPartida);
    }
  }

  return partidas;
}

// Con los datos de una partida guardada, creamos (recreamos) un objeto partida
// que guardaremos para mostrar al usuario y restaurar el estado de un juego no
// finalizado (por hacer)
void GameState::pushMemoryCard(Partida *partidaAGuardar) {

  PartidaGuardada partida = PartidaGuardada(
      partidaAGuardar->getMarcador(), partidaAGuardar->getModoDeJuego(),
      partidaAGuardar->getModalidad(), partidaAGuardar->getTurno(),
      partidaAGuardar->getFinalizado(), partidaAGuardar->getParrilla());

  this->memoryCard.push_back(partida);

  // Luego de guardar la partida en el vector en memoria, serializamos el
  // historial para asegurar el guardado inmediato
  PartidaGuardada::serializarPartida(this->memoryCard, "partidasConnect4");
}
