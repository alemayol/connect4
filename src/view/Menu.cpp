#include "../../include/Menu.h"
#include <raylib.h>

// Agregar botones al vector lista de botones del menu
void Menu::agregarBoton(Boton btn) { this->listaDeBotones.push_back(btn); }

// Por cada boton en la lista de botones se activa un listener (funcion que
// actualiza el estado del boton)
void Menu::btnListeners() {
  for (Boton &btn : this->listaDeBotones) {
    btn.btnListener(); // Empezar a rastrear las acciones dirigidas a los
                       // botones
  }
}
// Por cada boton en la lista de botones, se llama a la funcion que dibuja los
// botones en pantalla
void Menu::dibujarBotones() {
  for (Boton &btn : this->listaDeBotones) {
    btn.dibujarBoton(); // Empezar a dibujar los botones
  }
}
