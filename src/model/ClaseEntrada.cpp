#include "../../include/Principal.h"
#include <cstdlib>
#include <raylib.h>

class ClaseEntrada {};

int main() {

  GameState *globalState = new GameState();

  Principal *principal = new Principal(globalState);

  principal->IniciarPantallaPrincipal();

  principal->CerrarPantallaPrincipal();

  free(principal);
  free(globalState);

  return 0;
}
