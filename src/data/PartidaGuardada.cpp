#include "../../include/PartidaGuardada.h"
#include <fstream>
#include <ios>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

PartidaGuardada::PartidaGuardada(Marcador marcador, MODODEJUEGO modo,
                                 MODALIDAD modalidad, int turno,
                                 bool juegoFinalizado,
                                 ESTADO_SLOT (*tablero)[7])
    : marcador(marcador), modo(modo), modalidad(modalidad), turno(turno),
      juegoFinalizado(juegoFinalizado) {

  // Recreamos el arreglo en la partida guardada para obtener una copia
  for (int i = 0; i < 6; i++) {

    for (int j = 0; j < 7; j++) {
      this->parrilla[i][j] = tablero[i][j];
    }
  }
};

// Serializamos las partidas guardadas en el historial de partidas guardadas del
// estado global del juego en un archivo binario. Por hacer: elaborar una lista
// en la pantalla de historial con todas las partidas jugadas y guardadas
void PartidaGuardada::serializarPartida(
    std::vector<PartidaGuardada> &memoryCard,
    const std::string &nombreArchivo) {

  std::ofstream file(nombreArchivo, std::ios::binary);

  if (file.is_open()) {

    // Si el archivo pudo ser abierto, calculamos el tamano del vector de
    // partidas guardadas
    size_t cantidadObjetos = memoryCard.size();

    file.write(reinterpret_cast<const char *>(&cantidadObjetos),
               sizeof(cantidadObjetos));

    // Por cada partida guardada casteamos las propiedades como un caracter
    // constante para serializarlo
    for (const PartidaGuardada &partida : memoryCard) {
      file.write(reinterpret_cast<const char *>(&partida.marcador),
                 sizeof(partida.marcador));
      file.write(reinterpret_cast<const char *>(&partida.modo),
                 sizeof(partida.modo));
      file.write(reinterpret_cast<const char *>(&partida.modalidad),
                 sizeof(partida.modalidad));
      file.write(reinterpret_cast<const char *>(&partida.turno),
                 sizeof(partida.turno));
      file.write(reinterpret_cast<const char *>(&partida.juegoFinalizado),
                 sizeof(partida.juegoFinalizado));

      file.write(reinterpret_cast<const char *>(partida.parrilla),
                 6 * 7 * sizeof(ESTADO_SLOT));
    }

    file.close();
  } else {
    std::cerr << "Error: No se pudo abrir el archivo para grabar." << std::endl;
  }
}

// Deserializamos las partidas guardadas para cargarlas en memoria en el estado
// global del juego. Por hacer: pantalla de historial
std::vector<PartidaGuardada>
PartidaGuardada::deserializarPartida(const std::string &nombreArchivo) {

  std::vector<PartidaGuardada> memoryCard;

  std::ifstream file(nombreArchivo, std::ios::binary);
  if (!file.is_open()) {
    return memoryCard;
  }

  // Leemos la cantidad de partidas guardadas
  size_t cantidadObjetos;
  file.read(reinterpret_cast<char *>(&cantidadObjetos),
            sizeof(cantidadObjetos));

  // Leemos cada juego
  for (size_t i = 0; i < cantidadObjetos; ++i) {
    // Establecemos los datos que queremos leer de la partida
    Marcador marcador;
    MODODEJUEGO modo;
    MODALIDAD modalidad;
    int turno;
    bool juegoFinalizado;
    ESTADO_SLOT tablero[6][7];

    file.read(reinterpret_cast<char *>(&marcador), sizeof(marcador));
    file.read(reinterpret_cast<char *>(&modo), sizeof(modo));
    file.read(reinterpret_cast<char *>(&modalidad), sizeof(modalidad));
    file.read(reinterpret_cast<char *>(&turno), sizeof(turno));
    file.read(reinterpret_cast<char *>(&juegoFinalizado),
              sizeof(juegoFinalizado));

    // Leemos el tablero (6 filas x 7 columnas)
    file.read(reinterpret_cast<char *>(tablero), 6 * 7 * sizeof(ESTADO_SLOT));

    // Creamos el objeto y lo ponemos en el vector
    memoryCard.emplace_back(marcador, modo, modalidad, turno, juegoFinalizado,
                            tablero);
  }

  file.close();
  return memoryCard;
}

Marcador PartidaGuardada::getMarcador() { return this->marcador; }
int PartidaGuardada::getTurno() { return this->turno; }
bool PartidaGuardada::getJuegoFinalizado() { return this->juegoFinalizado; }
MODODEJUEGO PartidaGuardada::getModoDeJuego() { return this->modo; };
MODALIDAD PartidaGuardada::getModalidad() { return this->modalidad; };
ESTADO_SLOT (*PartidaGuardada::getTablero())[7] { return this->parrilla; }
