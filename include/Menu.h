#pragma once

#define MENU_H

#include "Boton.h"
#include <vector>

class Menu {
private:
  std::vector<Boton> listaDeBotones;

public:
  Menu() {};
  void agregarBoton(Boton btn);
  void eliminarBotones();
  void btnListeners();
  void dibujarBotones();
  void marcarBotonActivo();
};
