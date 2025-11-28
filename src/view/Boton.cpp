#include "../../include/Boton.h"
#include "raylib.h"
#include <iostream>
#include <string>

Boton::Boton(Rectangle rec, std::string texto, Color color,
             std::function<void()> onClick) {
  this->texto = texto;
  this->colorNormal = LIGHTGRAY;
  this->colorEnFoco = GRAY;
  this->colorPresionado = color;
  this->rec = rec;
  this->onClick = onClick;
  this->estado = NORMAL;
  this->isActive = false;
}

Vector2 Boton::calcPosTexto(Rectangle limites) {
  // Calculamos ancho de texto y lo colocamos en el centro del boton
  int anchoTexto = MeasureText(this->getTexto().c_str(), this->fontSize);

  return {
      limites.x + (limites.width - anchoTexto) / 2,
      limites.y + (limites.height - fontSize) / 2,
  };
}

void Boton::btnListener() {

  Vector2 posMouse = GetMousePosition();
  bool colisionMouse = CheckCollisionPointRec(posMouse, this->rec);

  if (colisionMouse) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      this->estado = PRESIONADO;
    } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      onClick();
      this->estado = EN_FOCO;
      this->isActive = !this->isActive;

    } else {
      this->estado = EN_FOCO;

      // std::cout << "Hover" << std::endl;
    }
  } else {
    this->estado = NORMAL;
  }
}

void Boton::dibujarBoton() {

  Color colorActual = this->colorNormal;

  switch (this->estado) {
  case NORMAL:
    colorActual = this->colorNormal;
    break;
  case EN_FOCO:
    colorActual = this->colorEnFoco;
    break;
  case PRESIONADO:
    colorActual = this->colorPresionado;
    break;
  }

  if (this->isActive)
    colorActual = this->colorPresionado;

  DrawRectangleRec(this->rec, colorActual);
  DrawRectangleLinesEx(this->rec, 4, DARKGRAY);

  Vector2 posTexto = this->calcPosTexto(this->rec);

  // Dibujamos texto en pantalla
  DrawText(this->getTexto().c_str(), posTexto.x, posTexto.y, this->fontSize,
           WHITE);
}

Color Boton::getColor() { return this->colorNormal; }

std::string Boton::getTexto() { return this->texto; }

Rectangle Boton::getLimites() { return this->rec; }
