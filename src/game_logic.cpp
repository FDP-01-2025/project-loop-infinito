#include "game_logic.h"
#include "game_structs.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm> // Necesario para transformar texto a minusculas
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;


const int filas = 10;
const int columnas = 10;
char tablero[filas][columnas];
int jugadorPos = columnas / 2;
int meteoritoX, meteoritoY;

void inicializarTablero() {
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < columnas; ++j)
            tablero[i][j] = ' ';
    tablero[filas - 1][jugadorPos] = 'A';
}

void generarMeteorito() {
    meteoritoX = 0;
    meteoritoY = rand() % columnas;
    tablero[meteoritoX][meteoritoY] = '*';
}

bool moverMeteorito() {
    if (meteoritoX < filas - 1) {
        tablero[meteoritoX][meteoritoY] = ' ';
        meteoritoX++;
        if (tablero[meteoritoX][meteoritoY] == 'A') {
            cout << "¡Has sido golpeado por un meteorito! 💥" << endl;
            system("pause");
            return false;  // Fin del minijuego
        }
        tablero[meteoritoX][meteoritoY] = '*';
    } else {
        tablero[meteoritoX][meteoritoY] = ' ';
        generarMeteorito();
    }
    return true; // Sigue jugando
}

void moverJugador(char direccion) {
    tablero[filas - 1][jugadorPos] = ' ';
    if (direccion == 'a' && jugadorPos > 0)
        jugadorPos--;
    else if (direccion == 'd' && jugadorPos < columnas - 1)
        jugadorPos++;
    tablero[filas - 1][jugadorPos] = 'A';
}

void mostrarTablero() {
    system("cls");
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j)
            cout << "[" << tablero[i][j] << "]";
        cout << endl;
    }
    cout << "\nUsa 'a' para moverte a la izquierda, 'd' para moverte a la derecha.\n";
}

void juegoMeteoritos() {
    srand(static_cast<unsigned int>(time(0)));
    inicializarTablero();
    generarMeteorito();

    bool jugando = true;
    while (jugando) {
        if (_kbhit()) {
            char tecla = _getch();
            moverJugador(tecla);
        }
        jugando = moverMeteorito();
        mostrarTablero();
        Sleep(300);
    }
}

bool loadAreasFromFile(const std::string &filePath, std::vector<Area> &gameAreas)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "ERROR FATAL: No se pudo abrir el archivo de datos de areas: " << filePath << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string segment;
        Area newArea;
        newArea.completed = false;
        if (std::getline(ss, segment, ','))
        {
            newArea.id = std::stoi(segment);
        }
        if (std::getline(ss, segment, ','))
        {
            newArea.name = segment;
        }
        if (std::getline(ss, segment, ','))
        {
            newArea.description = segment;
        }
        gameAreas.push_back(newArea);
    }
    file.close();
    return true;
}

// Muestra el menu principal
void showMainMenu(Player &player, const std::vector<Area> &gameAreas)
{
    std::cout << "\n------------------------------------------" << std::endl;
    std::cout << "Turnos restantes: " << player.turnsRemaining << " | Tareas completadas: " << player.tasksCompleted << "/5" << std::endl;
    if (player.status == SICK)
    {
        std::cout << "[!] ALERTA: Sistema biologico comprometido. Debes ir al Laboratorio Medico (ID 1)." << std::endl;
    }
    std::cout << "Selecciona el area a la que quieres ir (por ID):" << std::endl;
    for (const auto &area : gameAreas)
    {
        std::cout << area.id << ". " << area.name << (area.completed ? " (Completada)" : "") << std::endl;
    }
}

// Pide la opcion al usuario
int getValidInput()
{
    int choice;
    do
    {
        std::cout << "Opcion > ";
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cout << "Entrada invalida. Por favor, introduce un numero." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1;
        }
    } while (choice == -1);
    return choice;
}

// Navega a las areas con
void navigateToArea(Player &player, std::vector<Area> &gameAreas, int areaId)
{
    if (player.status == SICK && areaId != 1)
    {
        std::cout << "Accion no permitida. Debes ir primero al Laboratorio Medico (1)." << std::endl;
        return;
    }
    bool areaExists = false;
    for (const auto &area : gameAreas)
    {
        if (area.id == areaId)
        {
            areaExists = true;
            break;
        }
    }
    if (!areaExists)
    {
        std::cout << "ID invalido. Esa area no existe." << std::endl;
        return;
    }
    player.turnsRemaining--;
    std::cout << "\n[Turno " << 8 - player.turnsRemaining << "/8] Entrando a " << gameAreas[areaId - 1].name << "..." << std::endl;
    std::cout << "> " << gameAreas[areaId - 1].description << std::endl;
    switch (areaId)
    {
    case 1:
        executeMedicalLabLogic(player, gameAreas);
        break;
    case 2:
        executeHydroponicsGardenLogic(player, gameAreas);
        break;
    case 3:
        executeCommandCenter(player, gameAreas);
        break;
    case 4:
        executeCrewQuarters(player, gameAreas);
        break;
    case 5:
        executeEngineeringBay(player, gameAreas);
        break;
    default:
        std::cout << "Esta area parece tranquila por ahora. No hay interacciones especiales." << std::endl;
        break;
    }
}

// Logica del Laboratorio Medico
void executeMedicalLabLogic(Player &player, std::vector<Area> &gameAreas)
{
    if (player.status == SICK)
    {
        std::cout << "Administrando suero anti-toxinas... ¡Tratamiento exitoso! Te sientes saludable de nuevo." << std::endl;
        player.status = HEALTHY;
    }
    else
    {
        std::cout << "Evaluacion de sistema vital completa. Todos los parametros son optimos." << std::endl;
        if (!gameAreas[0].completed)
        {
            std::cout << "¡Tarea completada!" << std::endl;
            player.tasksCompleted++;
            gameAreas[0].completed = true;
        }
        else
        {
            std::cout << "Ya has completado la tarea en esta area." << std::endl;
        }
    }
}

// Logica del Jardin con acertijo
void executeHydroponicsGardenLogic(Player &player, std::vector<Area> &gameAreas)
{
    int areaIndex = 1;
    if (gameAreas[areaIndex].completed)
    {
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

    if (wateredGreen)
    {
        std::cout << "\n¡La planta de tallo verde brillante libera una nube de esporas mientras la riegas!" << std::endl;
        std::cout << "Te sientes mareado y una extrana erupcion aparece en tu brazo." << std::endl;
        std::cout << "\n[!] INFECCION DETECTADA. ¡Debes ir al Laboratorio Medico inmediatamente!" << std::endl;
        player.status = SICK;
    }
    else if (wateredRed && wateredBlue)
    {
        std::cout << "\nLas plantas roja y azul absorben el agua y su coloracion se vuelve mas vibrante." << std::endl;
        std::cout << "Has restaurado con exito el soporte vital de la seccion botanica." << std::endl;
        std::cout << "¡Tarea completada!" << std::endl;
        player.tasksCompleted++;
        gameAreas[areaIndex].completed = true;
    }
    else
    {
        std::cout << "\nRiegas algunas plantas, pero algo no se siente bien. El sistema sigue reportando un error." << std::endl;
        std::cout << "No lograste estabilizar el jardin. Un extrano olor emana de las plantas no regadas." << std::endl;
    }
}

// Loógica del Centro de Comandos
void executeCommandCenter(Player &player, std::vector<Area> &gameAreas)
{
    int areaIndex = 2;
    // puzzle
}

// Lógica del los camarotes de la tripulación
void executeCrewQuarters(Player &player, std::vector<Area> &gameAreas)
{
    int areaIndex = 3;

    if (!gameAreas[areaIndex].completed)
    {
        std::cout << "\nExploras los camarotes... Encuentras una consola con una contraseña temporal:\n";
        // se genera y muestra al jugador la contraseña
        std::string generatedPassword = "ZERO-2025"; // contraseña quemada
        player.memorizedPassword = generatedPassword;
        std::cout << "CONTRASEÑA: " << generatedPassword << std::endl;
        std::cout << "La contraseña brilla por última vez... y luego la consola se apaga para siempre. No hay segundas oportunidades.\n";
        gameAreas[areaIndex].completed = true;
        player.tasksCompleted++;
    }
    else
    {
        std::cout << "\nLa consola está apagada. Ya no puedes recuperar la contraseña.\n";
    }
}

// logica del LA SALA DE INGENIERIA
void executeEngineeringBay(Player &player, std::vector<Area> &gameAreas)
{
    int index = 4;

    if (gameAreas[index].completed)
    {
        std::cout << "\nEl Núcleo ZETA ya ha sido estabilizado. No queda nada más por hacer aquí.\n";
        return;
    }

    if (player.memorizedPassword.empty()) //si llega a la sala y no tiene la contraseña
    {
        std::cout << "\n!Acceso inválido¡\n";
        std::cout << "Intentas activar la consola del Núcleo ZETA, pero el sistema requiere una contraseña que nunca obtuviste.\n";
        std::cout << "Un eco grave recorre la sala... la interfaz se bloquea con un chispazo eléctrico.\n";
        std::cout << "Has perdido una oportunidad vital. La presión interna de la estación sigue aumentando...\n";
        return;
    }

    std::cout << "\nEl acceso al Núcleo ZETA está sellado.\n";
    std::cout << "Para desactivar el protocolo de autodestrucción, deberás ingresar la contraseña de seguridad.\n";
    std::cout << "Solo tienes **una oportunidad**. Si fallas, el sistema se cerrará permanentemente.\n";
    std::cout << "\nContraseña > ";

    std::string input;
    std::cin.ignore(); 
    std::getline(std::cin, input);

    if (input == player.memorizedPassword)
    {
        std::cout << "\n!ACCESO CONCEDIDO¡\n";
        std::cout << "El sistema reconoce la clave. El Núcleo ZETA comienza a estabilizarse lentamente...\n";
        std::cout << "Sistemas críticos en recuperación.\n";
        std::cout << "!Tarea completada¡\n";
        gameAreas[index].completed = true;
        player.tasksCompleted++;
    }
    else
    {
        std::cout << "\n!CONTRASEÑA INCORRECTA¡";
        std::cout << "Alarmas silenciosas se disparan. Las pantallas parpadean y se apagan una por una.\n";
        std::cout << "El acceso al Núcleo ZETA se ha perdido en el vacío del sistema.\n";
        std::cout << "No hay vuelta atrás... la estación sigue tambaleándose hacia el colapso.\n";    }
}

//research lab

// Bucle principal del juego
void runGame()
{
    Player player;
    std::vector<Area> gameAreas;
    bool isGameOver = false;

    if (!loadAreasFromFile("data/areas.txt", gameAreas))
    {
        return;
    }

    std::cout << "--- BIENVENIDO A LA ESTACION ESPACIAL ZERO ---" << std::endl;
    std::cout << "El protocolo de autodestruccion ha sido activado. Tienes 8 turnos para completar 5 tareas." << std::endl;

    while (!isGameOver)
    {
        showMainMenu(player, gameAreas);
        int choice = getValidInput();
        navigateToArea(player, gameAreas, choice);

        if (player.tasksCompleted >= 5)
        {
            std::cout << "\n¡FELICIDADES! Completaste todas las tareas y estabilizaste la estacion. ¡Has sobrevivido!" << std::endl;
            isGameOver = true;
        }
        else if (player.turnsRemaining <= 0)
        {
            std::cout << "\n¡FIN DEL JUEGO! Te has quedado sin turnos. La estacion ha colapsado contigo dentro." << std::endl;
            isGameOver = true;
        }
    }
}