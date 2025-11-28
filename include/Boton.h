#pragma once

#include "GameState.h"
#define BOTON_H

#include "raylib.h"
#include <functional>
#include <string>

class Boton {

public:
  Boton(Rectangle rec, std::string texto, Color color,
        std::function<void()> onClick);
  void dibujarBoton();
  void btnListener();
  bool botonEnFoco();
  enum ESTADO_BOTON { NORMAL = 0, PRESIONADO, EN_FOCO };

  // Setters Getters
  void setTexto(std::string text);
  void setColor(Color clr);
  int getPosX();
  int getPosY();
  std::string getTexto();
  Color getColor();

  // Methods
  Vector2 calcPosTexto(Rectangle limites);
  Rectangle getLimites();

private:
  std::string texto;
  Rectangle rec;
  Color colorNormal;
  Color colorEnFoco;
  Color colorPresionado;
  bool isActive;
  static const int fontSize = 30;
  std::function<void()> onClick;
  ESTADO_BOTON estado;
};
