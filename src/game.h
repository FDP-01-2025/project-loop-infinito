#pragma once
#include "Player.h"
#include "Area.h"
#include <vector>

class Game {
private:
    Player player;
    bool isGameOver;
    std::vector<Area> gameAreas; // Estructura de datos para las areas

    // Metodos privados de logica interna
    void loadAreasFromFile(const std::string& filePath); // Manejo de archivos
    void showMainMenu();
    void navigateToArea(int areaId);
    int getValidInput(); // Manejo de entrada de usuario

    // Logica especifica de cada area
    void executeMedicalLabLogic();
    void executeHydroponicsGardenLogic();

public:
    Game(); // El constructor puede fallar (si no encuentra el archivo)
    void run();
};