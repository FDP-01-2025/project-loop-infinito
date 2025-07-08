#pragma once
#include "game_structs.h" 

// --- Declaraciones de Funciones ---

// Funcion principal que contiene el bucle del juego
void runGame();

// Funciones de logica y setup
bool loadAreasFromFile(const std::string& filePath, std::vector<Area>& gameAreas);
void showMainMenu(Player& player, const std::vector<Area>& gameAreas);
int getValidInput();
void navigateToArea(Player& player, std::vector<Area>& gameAreas, int areaId);

// Funciones para la logica de cada sala

void executeMedicalLabLogic(Player& player, std::vector<Area>& gameAreas);
void executeHydroponicsGardenLogic(Player& player, std::vector<Area>& gameAreas);
void executeCommandCenter(Player& player, std::vector<Area>& gameAreas);
void executeCrewQuarters(Player& player, std::vector<Area>& gameAreas);
void executeEngineeringBay(Player& player, std::vector<Area>& gameAreas);
void executeResearchLab(Player& player, std::vector<Area>& gameAreas);
void executeArmoryLogic(Player& player, std::vector<Area>& gameAreas); 
