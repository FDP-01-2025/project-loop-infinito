#include <string>
#include <vector>

// enum para el estado de salud del jugador.
enum PlayerStatus {
    HEALTHY,
    SICK
};

// struct para los datos del jugador.
// Se inicializan con valores por defecto.
struct Player {
    PlayerStatus status = HEALTHY;
    int turnsRemaining = 8;
    int tasksCompleted = 0;
};

// struct para los datos de las areas.
struct Area {
    int id;
    std::string name;
    std::string description;
    bool completed = false;
};