#include "../../include/Boton.h"
#include "raylib.h"
#include <string>

// Constructores
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

// Calculamos ancho de texto de un boton (rectangulo) y para colocarlo en el
// centro del boton
Vector2 Boton::calcPosTexto(Rectangle limites) {
  int anchoTexto = MeasureText(this->getTexto().c_str(), this->fontSize);

  return {
      limites.x + (limites.width - anchoTexto) / 2,
      limites.y + (limites.height - fontSize) / 2,
  };
}

// Obtenemos la posicion actual del mouse para detectar si existe una colision
// con el boton actual. De existir colision, se verifica la accion actual del
// boton y se cambia el estado (color) actual del boton. De ser un click la
// accion, se llama a la funcion lambda argumento pasada en el constructor del
// boton
void Boton::btnListener() {

  Vector2 posMouse = GetMousePosition();
  bool colisionMouse = CheckCollisionPointRec(posMouse, this->rec);

  if (colisionMouse) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      this->estado = PRESIONADO;
    } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      onClick();
      this->estado = EN_FOCO;

    } else {
      this->estado = EN_FOCO;
    }
  } else {
    this->estado = NORMAL;
  }
}

// Determinamos el color actual del boton basado en su estado y lo dibujamos en
// pantalla
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

  // Dibujamos texto en pantalla en la misma posicion (encima) del boton
  DrawText(this->getTexto().c_str(), posTexto.x, posTexto.y, this->fontSize,
           WHITE);
}

// Retorna color en estado normal (sin hover ni click) del boton
Color Boton::getColor() { return this->colorNormal; }

// Retorna el texto dentro del boton
std::string Boton::getTexto() { return this->texto; }

// Retorna los limites (posicion x,y, ancho y alto) del boton
Rectangle Boton::getLimites() { return this->rec; }
