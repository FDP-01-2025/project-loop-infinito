#include "game.h"
#include <iostream>
#include <fstream>  
#include <sstream>   
#include <stdexcept> 
#include <limits>   



Game::Game() : isGameOver(false) {
  
    try {
        loadAreasFromFile("data/areas.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << "FATAL ERROR: " << e.what() << std::endl;
        throw;
    }
}

// Manejo de Archivos
void Game::loadAreasFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        // se muestra una excepcion si el archivo no se puede abrir
        throw std::runtime_error("Could not open area data file: " + filePath);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string segment;
        Area newArea;
        newArea.completed = false;

        std::getline(ss, segment, ',');
        newArea.id = std::stoi(segment);
        std::getline(ss, segment, ',');
        newArea.name = segment;
        std::getline(ss, segment, ',');
        newArea.description = segment;
        
        gameAreas.push_back(newArea);
    }
    file.close();
}


// -- BUCLE PRINCIPAL Y NAVEGACION --

void Game::run() {
    std::cout << "--- WELCOME TO SPACE STATION ZERO ---" << std::endl;
    std::cout << "The self-destruct protocol has been activated. You have " << player.turnsRemaining << " turns to complete 5 tasks and escape." << std::endl;

    while (!isGameOver) {
        if (player.tasksCompleted >= 5) {
            std::cout << "\nCONGRATULATIONS! You have survived!" << std::endl;
            isGameOver = true;
            continue;
        }
        if (player.turnsRemaining <= 0) {
            std::cout << "\nGAME OVER! You have run out of turns." << std::endl;
            isGameOver = true;
            continue;
        }
        showMainMenu();
    }
}

void Game::showMainMenu() {
    std::cout << "\n------------------------------------------" << std::endl;
    std::cout << "Turns remaining: " << player.turnsRemaining << " | Tasks completed: " << player.tasksCompleted << "/5" << std::endl;

    if (player.status == PlayerStatus::SICK) {
        std::cout << "[!] ALERT: Biological system compromised. You must go to the Medical Lab (ID 1)." << std::endl;
    }

    std::cout << "Select the area you want to go to (by ID):" << std::endl;
    // ciclo para mostrar datos de la estructura
    for (const auto& area : gameAreas) {
        std::cout << area.id << ". " << area.name << (area.completed ? " (Completed)" : "") << std::endl;
    }

    int choice = getValidInput();
    navigateToArea(choice);
}

// Implementacion de Manejo de Entrada
int Game::getValidInput() {
    int choice;
    // Ciclo para asegurar una entrada valida
    do {
        std::cout << "Option > ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // flag de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // se descarta la linea erronea
            choice = -1; // Asignamos un valor invalido para que el bucle continue
        }
    } while (choice == -1);
    
    return choice;
}

void Game::navigateToArea(int areaId) {
    // restriccion por enfermedad del garden
    if (player.status == PlayerStatus::SICK && areaId != 1) {
        std::cout << "Action not allowed. You must go to the Medical Lab (1) first." << std::endl;
        return;
    }
    
    // Validar si el ID existe (aunque getValidInput ya asegura un numero)
    bool areaExists = false;
    for(const auto& area : gameAreas) {
        if(area.id == areaId) {
            areaExists = true;
            break;
        }
    }

    if (!areaExists) {
        std::cout << "Invalid ID. That area does not exist." << std::endl;
        return;
    }

    player.turnsRemaining--; // Ir a un area siempre consume un turno
    std::cout << "\n[Turn " << 8 - player.turnsRemaining << "/8] Entering " << gameAreas[areaId -1].name << "..." << std::endl;
    std::cout << gameAreas[areaId - 1].description << std::endl;

    // Uso de switch para llamar a la logica de la sala correcta
    switch (areaId) {
        case 1:
            executeMedicalLabLogic();
            break;
        case 2:
            executeHydroponicsGardenLogic();
            break;
        default:
            std::cout << "This area has no special interaction." << std::endl;
            break;
    }
}


// -- LOGICA DE LAS SALAS --

void Game::executeMedicalLabLogic() {
    if (player.status == PlayerStatus::SICK) {
        std::cout << "Administering anti-toxin serum... Treatment successful!" << std::endl;
        player.cure();
    } else {
        std::cout << "Vital system evaluation complete. All parameters are optimal." << std::endl;
        // Marcar tarea como completada si no lo estaba ya
        if (!gameAreas[0].completed) {
            std::cout << "Task completed!" << std::endl;
            player.tasksCompleted++;
            gameAreas[0].completed = true;
        } else {
             std::cout << "You have already completed the task in this area." << std::endl;
        }
    }
}

void Game::executeHydroponicsGardenLogic() {
    std::cout << "You have watered a Xenomorphic plant by mistake! Its spores have infected you." << std::endl;
    player.getInfected();
}

// implementacion del constructor de player aqui
Player::Player() {
    status = PlayerStatus::HEALTHY;
    turnsRemaining = 8;
    tasksCompleted = 0;
}

void Player::cure() {
    status = PlayerStatus::HEALTHY;
}

void Player::getInfected() {
    status = PlayerStatus::SICK;
}