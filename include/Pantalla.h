#pragma once

#define PANTALLA_H

class Pantalla {
public:
  ~Pantalla() = default;
  virtual void dibujarPantalla(float screenWidth, float screenHeight) = 0;
  virtual void actualizarPantalla() = 0;

private:
};
