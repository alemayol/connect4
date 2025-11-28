#pragma once

#define PANTALLAPRINCIPAL_H
#include "GameState.h"
#include "Menu.h"
#include "Pantalla.h"

class PantallaPrincipal : public Pantalla {
public:
  PantallaPrincipal(GameState *globalState, float screenWidth,
                    float screenHeight);
  void dibujarPantalla(float screenWidth, float screenHeight) override;
  void actualizarPantalla() override;

private:
  Menu menu;
  GameState *globalState;
};
