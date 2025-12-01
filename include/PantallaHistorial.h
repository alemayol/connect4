
#pragma once

#include <string>
#define PANTALLAHISTORIAL_H
#include "GameState.h"
#include "Menu.h"
#include "Pantalla.h"
#include <raylib.h>

class PantallaHistorial : public Pantalla {
public:
  PantallaHistorial(GameState *globalState, float screenWidth,
                    float screenHeight);
  void dibujarPantalla(float screenWidth, float screenHeight) override;
  void actualizarPantalla() override;
  Vector2 calcularPosTexto(Rectangle rec, std::string texto);

private:
  Menu menu;
  GameState *globalState;
  float screenWidth;
  float screenHeight;
};
