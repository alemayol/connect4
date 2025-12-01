#pragma once

#define PRINCIPAL_H
#include "GameState.h"
#include "Partida.h"

#include "raylib.h"

class Principal {
public:
  Principal(GameState *globalState);
  void IniciarPantallaPrincipal();
  void CerrarPantallaPrincipal();

private:
  GameState *globalState;
};
