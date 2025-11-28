#pragma once

#define HUMANO_H
#include "Jugador.h"

class Humano : public Jugador {
public:
  Humano(Color colorFicha);
  void colocarFicha(int fila, int columna) override;
};
