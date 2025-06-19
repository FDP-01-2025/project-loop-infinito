#include "Game.h"
#include <iostream>

int main() {
    try {
        Game game; //Se llama al constructor de Game
        game.run();  //Se llama al metodo principal del juego
    } catch (const std::runtime_error& e) {
        // Si el constructor falla (archivo no encontrado), se captura aqui.
        std::cerr << "The game could not be started. Aborting." << std::endl;
        return 1; // Retornamos un codigo de error
    }
    
    return 0; // Todo salio bien
}