#include "./include/Principal.h"
#include <cstdlib>
#include <raylib.h>
#include <vector>

int main() {

  std::vector<PartidaGuardada> memoryCard =
      PartidaGuardada::deserializarPartida("partidasConnect4");
  GameState *globalState = new GameState(memoryCard);

  Principal *principal = new Principal(globalState);

  principal->IniciarPantallaPrincipal();

  principal->CerrarPantallaPrincipal();

  free(principal);
  free(globalState);

  return 0;
}
