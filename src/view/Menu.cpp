#include "../../include/Menu.h"
#include <raylib.h>

// Menu::Menu() {}

void Menu::agregarBoton(Boton btn) { this->listaDeBotones.push_back(btn); }

void Menu::btnListeners() {
  for (Boton &btn : this->listaDeBotones) {
    btn.btnListener(); // Empezar a rastrear las acciones dirigidas a los
                       // botones
  }
}

void Menu::dibujarBotones() {
  for (Boton &btn : this->listaDeBotones) {
    btn.dibujarBoton(); // Empezar a dibujar los botones
  }
}
