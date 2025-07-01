#include "game_logic.h"
#include "game_structs.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm> // Necesario para transformar texto a minusculas


bool loadAreasFromFile(const std::string& filePath, std::vector<Area>& gameAreas) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "ERROR FATAL: No se pudo abrir el archivo de datos de areas: " << filePath << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string segment;
        Area newArea;
        newArea.completed = false;
        if (std::getline(ss, segment, ',')) { newArea.id = std::stoi(segment); }
        if (std::getline(ss, segment, ',')) { newArea.name = segment; }
        if (std::getline(ss, segment, ',')) { newArea.description = segment; }
        gameAreas.push_back(newArea);
    }
    file.close();
    return true;
}

// Muestra el menu principa
void showMainMenu(Player& player, const std::vector<Area>& gameAreas) {
    std::cout << "\n------------------------------------------" << std::endl;
    std::cout << "Turnos restantes: " << player.turnsRemaining << " | Tareas completadas: " << player.tasksCompleted << "/5" << std::endl;
    if (player.status == SICK) {
        std::cout << "[!] ALERTA: Sistema biologico comprometido. Debes ir al Laboratorio Medico (ID 1)." << std::endl;
    }
    std::cout << "Selecciona el area a la que quieres ir (por ID):" << std::endl;
    for (const auto& area : gameAreas) {
        std::cout << area.id << ". " << area.name << (area.completed ? " (Completada)" : "") << std::endl;
    }
}

// Pide la opcion al usuario
int getValidInput() {
    int choice;
    do {
        std::cout << "Opcion > ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Entrada invalida. Por favor, introduce un numero." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1;
        }
    } while (choice == -1);
    return choice;
}

// Navega a las areas con 
void navigateToArea(Player& player, std::vector<Area>& gameAreas, int areaId) {
    if (player.status == SICK && areaId != 1) {
        std::cout << "Accion no permitida. Debes ir primero al Laboratorio Medico (1)." << std::endl;
        return;
    }
    bool areaExists = false;
    for (const auto& area : gameAreas) {
        if (area.id == areaId) {
            areaExists = true;
            break;
        }
    }
    if (!areaExists) {
        std::cout << "ID invalido. Esa area no existe." << std::endl;
        return;
    }
    player.turnsRemaining--;
    std::cout << "\n[Turno " << 8 - player.turnsRemaining << "/8] Entrando a " << gameAreas[areaId - 1].name << "..." << std::endl;
    std::cout << "> " << gameAreas[areaId - 1].description << std::endl;
    switch (areaId) {
        case 1:
            executeMedicalLabLogic(player, gameAreas);
            break;
        case 2:
            executeHydroponicsGardenLogic(player, gameAreas);
            break;
        default:
            std::cout << "Esta area parece tranquila por ahora. No hay interacciones especiales." << std::endl;
            break;
    }
}

// Logica del Laboratorio Medico 
void executeMedicalLabLogic(Player& player, std::vector<Area>& gameAreas) {
    if (player.status == SICK) {
        std::cout << "Administrando suero anti-toxinas... ¡Tratamiento exitoso! Te sientes saludable de nuevo." << std::endl;
        player.status = HEALTHY;
    } else {
        std::cout << "Evaluacion de sistema vital completa. Todos los parametros son optimos." << std::endl;
        if (!gameAreas[0].completed) {
            std::cout << "¡Tarea completada!" << std::endl;
            player.tasksCompleted++;
            gameAreas[0].completed = true;
        } else {
             std::cout << "Ya has completado la tarea en esta area." << std::endl;
        }
    }
}

// Logica del Jardin con acertijo 
void executeHydroponicsGardenLogic(Player& player, std::vector<Area>& gameAreas) {
    int areaIndex = 1;
    if (gameAreas[areaIndex].completed) {
        std::cout << "El sistema de riego automatizado funciona correctamente. No hay nada mas que hacer aqui." << std::endl;
        return;
    }
    std::cout << "El sistema principal de riego esta desconectado. Debes regar las plantas manualmente." << std::endl;
    std::cout << "Ves tres plantas extranas: una con venas [Rojas], una con flores [Azules] y una con un tallo [Verde] brillante." << std::endl;
    std::cout << "Una nota botanica en una terminal dice: 'Advertencia: Cierta Flora puede ser hostil. Suministre agua solo a especimenes con pigmentacion de colores primarios.'" << std::endl;
    std::cout << "\n¿Que planta(s) riegas? (ej: 'roja', 'roja azul', 'verde')" << std::endl;
    std::cout << "Entrada > ";
    std::string userInput;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::getline(std::cin, userInput);
    
    // se convierte la entrada a minusculas para facilitar la comparacion
    std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);

    bool wateredRed = userInput.find("roja") != std::string::npos;
    bool wateredBlue = userInput.find("azul") != std::string::npos;
    bool wateredGreen = userInput.find("verde") != std::string::npos;

    if (wateredGreen) {
        std::cout << "\n¡La planta de tallo verde brillante libera una nube de esporas mientras la riegas!" << std::endl;
        std::cout << "Te sientes mareado y una extrana erupcion aparece en tu brazo." << std::endl;
        std::cout << "\n[!] INFECCION DETECTADA. ¡Debes ir al Laboratorio Medico inmediatamente!" << std::endl;
        player.status = SICK;
    } else if (wateredRed && wateredBlue) {
        std::cout << "\nLas plantas roja y azul absorben el agua y su coloracion se vuelve mas vibrante." << std::endl;
        std::cout << "Has restaurado con exito el soporte vital de la seccion botanica." << std::endl;
        std::cout << "¡Tarea completada!" << std::endl;
        player.tasksCompleted++;
        gameAreas[areaIndex].completed = true;
    } else {
        std::cout << "\nRiegas algunas plantas, pero algo no se siente bien. El sistema sigue reportando un error." << std::endl;
        std::cout << "No lograste estabilizar el jardin. Un extrano olor emana de las plantas no regadas." << std::endl;
    }
}

// Bucle principal del juego 
void runGame() {
    Player player;
    std::vector<Area> gameAreas;
    bool isGameOver = false;

    if (!loadAreasFromFile("data/areas.txt", gameAreas)) {
        return;
    }

    std::cout << "--- BIENVENIDO A LA ESTACION ESPACIAL ZERO ---" << std::endl;
    std::cout << "El protocolo de autodestruccion ha sido activado. Tienes 8 turnos para completar 5 tareas." << std::endl;

    while (!isGameOver) {
        showMainMenu(player, gameAreas);
        int choice = getValidInput();
        navigateToArea(player, gameAreas, choice);

        if (player.tasksCompleted >= 5) {
            std::cout << "\n¡FELICIDADES! Completaste todas las tareas y estabilizaste la estacion. ¡Has sobrevivido!" << std::endl;
            isGameOver = true;
        } else if (player.turnsRemaining <= 0) {
            std::cout << "\n¡FIN DEL JUEGO! Te has quedado sin turnos. La estacion ha colapsado contigo dentro." << std::endl;
            isGameOver = true;
        }
    }
}