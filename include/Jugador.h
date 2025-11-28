#pragma once

#define JUGADOR_H

#include <raylib.h>

class Jugador {
public:
  Jugador(Color colorFicha);
  virtual ~Jugador() = default;
  virtual void colocarFicha(int fila, int columna);

private:
  Color colorFicha;
};
