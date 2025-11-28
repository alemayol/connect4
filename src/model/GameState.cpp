#include "../../include/GameState.h"
#include "../../include/Pantalla.h"

GameState::GameState() {
  this->partidaActual = nullptr;
  this->modo = NINGUNO;
  this->modalidad = NINGUNA;
  this->pantallaActual = PANTALLA_PRINCIPAL;
}

void GameState::setPartidaActual(Partida *nuevaPartida) {
  if (this->partidaActual != nullptr && nuevaPartida != nullptr) {
    this->partidaActual = nuevaPartida;
  }
}

void GameState::setModoDeJuego(MODODEJUEGO modo) { this->modo = modo; };

void GameState::setModalidad(MODALIDAD modalidad) {
  this->modalidad = modalidad;
};
void GameState::setPantallaActual(PANTALLA pantallaActual) {
  this->pantallaActual = pantallaActual;
};

GameState::PANTALLA GameState::getPantallaActual() {
  return this->pantallaActual;
};

void GameState::setSalirDelJuego(bool salir) { this->salirDelJuego = salir; };
bool GameState::getSalirDelJuego() { return this->salirDelJuego; };
