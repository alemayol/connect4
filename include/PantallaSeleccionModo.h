#pragma once

#define PANTALLAMODO_H
#include "GameState.h"
#include "Menu.h"
#include "Pantalla.h"

class PantallaSeleccionModo : public Pantalla {
public:
  PantallaSeleccionModo(GameState *globalState, float screenWidth,
                        float screenHeight);
  void dibujarPantalla(float screenWidth, float screenHeight) override;
  void actualizarPantalla() override;

private:
  Menu menu;
  GameState *globalState;
};
