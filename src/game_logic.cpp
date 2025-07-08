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
      std::cout << "0. Salir del Juego" << std::endl;
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
    case 6:
        executeArmoryLogic(player, gameAreas);
        break;
    case 7: // <--- AÑADE ESTE NUEVO CASO PARA EL AI CORE
        executeAiCoreLogic(player, gameAreas);
        break;
    case 8:
        executeResearchLab(player, gameAreas);
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
    // no puede entrar si no ha completado 4 salas.
    if (!player.tasksCompleted == 4)
    {
        std::cout << "\n[ ¡ACCESO DENEGADO! ] Debes completar al menos 4 tareas para ingresar al Puente de Mando\n";
        return;
    }
    else if (gameAreas[areaIndex].completed)
    {
        std::cout << "\nYa has completado el Centro de Mando. No hay interecciones especiales disponibles.\n";
        return;
    }

    std::cout << "\n[ERROR] El sistema del Centro de Mando está fallando\n";
    std::cout << "Los nodos de energía están inestables, y solo hay un nodo defectuoso que esta causando el fallo\n";
    std::cout << "Debes encontrar y desactivar ese nodo desde la matriz energetica.(A-D FILAS, 1-4 COLUMNAS)\n";
    std::cout << "cargando...\n\n";

    srand(time(0));

    int energyMatrix[4][4] = { // matriz de los nodos 1-4
        {1, 2, 3, 4},
        {4, 3, 2, 1},
        {2, 1, 4, 3},
        {3, 4, 1, 2}};

    std::string coordinates[4][4] = { //coordenadas, ayuda visual
        {"A1", "A2", "A3", "A4"},
        {"B1", "B2", "B3", "B4"},
        {"C1", "C2", "C3", "C4"},
        {"D1", "D2", "D3", "D4"}};

    // eligiendo la celda del nodo defectuoso
    int targetRow = rand() % 4;
    int targetCol = rand() % 4;

    int targetNode = energyMatrix[targetRow][targetCol];
    int newValue;

    // cambiando el valor de la celda elegida a uno que ya esté en la fila
    do
    {
        newValue = energyMatrix[targetRow][rand() % 4];
    } while (newValue == targetNode);

    energyMatrix[targetRow][targetCol] = newValue;

    // mostrar la matriz
    std::cout << "[MATRIZ NODOS]\n";
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            std::cout << " [" << energyMatrix[row][col] << "] ";
        }
        std::cout << "\n";
    }
    std::cout << "[PISTA] Solo hay una celda con valor incorrecto\n";

    // Entrada del jugador y validación
    std::string input;
    std::cout << "\nIngrese coordenada del nodo defectuoso (ej. B2) > ";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //limpiando el bufer
    std::getline(std::cin, input); 

    if (input.length() != 2)
    {
        std::cout << "Entrada invalida.\n";
    }

    int playerRow = toupper(input[0]) - 'A'; // letra a fila
    int playerCol = input[1] - '1';          // numero a columna

    if (playerRow < 0 || playerRow >= 4 || playerCol < 0 || playerCol >= 4)
    {
        std::cout << "Coordenada fuera del rango.\n";
    }

    // Verificar si el jugador acertó o no
    if (playerRow == targetRow && playerCol == targetCol)
    {
        std::cout << "\n¡TAREA COMPLETADA! Has detectado y aislado la celda corrupta (" << coordinates[playerRow][playerCol] << ").\n";
        gameAreas[areaIndex].completed = true;
        player.tasksCompleted++;
    }
    else
    {
        std::cout << "\nEsa no es la celda incorrecta. El sistema sigue inestable.\n";
        std::cout << "La celda corrupta estaba en: " << coordinates[playerRow][playerCol] << ".\n";
    }

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

    if (player.memorizedPassword.empty()) // si llega a la sala y no tiene la contraseña
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
        std::cout << "No hay vuelta atrás... la estación sigue tambaleándose hacia el colapso.\n";
    }
}

// logica de research lab
void executeResearchLab(Player &player, std::vector<Area> &gameAreas)
{
    int index = 7;

    if (gameAreas[index].completed)
    {
        std::cout << "\nYa has obtenido la cura de las muestras. No hay nada que hacer aquí.\n";
    }

    std::cout << "\nEl ambiente es sofocante. Notas que hay vidrios y pantallas rotas.\n";
    std::cout << "[ADVERTENCIA] Estas infestado por el COVID-19 que se estaba investigando en el laboratorio.\n";
    std::cout << "Estas agitado y toses violentamiente.\n";

    std::cout << "¡ALERTA! Para sintetizar la cura, debes ordenar correctamente las muestras biológicas contaminadas.\n";
    std::cout << "Si fallas,, quedarás infectado y deberás volver más tarde...\n";

    std::cout << "\n¿Cuál es el orden correcto de las muestras para sintetizar la cura?\n";
    std::cout << "1) ALPHA - BETA - GAMA - DELTA\n"; // es el orden correcto
    std::cout << "2) GAMA - ALPHA - DELTA - BETA\n";
    std::cout << "3) BETA - GAMA - ALPHA - DELTA\n";
    std::cout << "4) DELTA - GAMA - BETA - ALPHA\n";
    std::cout << "[PISTA] La letras inciales de la secuencia correcta es A-B-G-D\n";
    std::cout << "Ingresa tu opción > ";

    int option;
    std::cin >> option;

    if (option == 1)
    {
        std::cout << "\n\n\n¡Tarea completada! Has sintetizado la cura con éxito.\n";
        gameAreas[index].completed = true;
        player.tasksCompleted++;
    }
    else
    {
        std::cout << "\n¡Fallastes! Te has quedado infestado. Vuelve cuando te sientas listo...\n";
        player.status = SICK;
    }
}

void executeArmoryLogic(Player& player, std::vector<Area>& gameAreas) {
    // El ID de la Armeria es 6, su indice en el vector es 5
    int areaIndex = 5;

    // se revisa si la tarea ya fue completada
    if (gameAreas[areaIndex].completed) {
        std::cout << "El sistema de defensa anti-meteoritos ya esta calibrado y en linea." << std::endl;
        return;
    }

    std::string correctSequence = "delta sierra alpha romeo";
    std::cout << "Accedes a la consola de defensa de la estacion." << std::endl;
    std::cout << "Se acercan meteoritos y necesitas las torretas para destruirlos. Para calibrar las torretas, debes introducir una secuencia de activacion." << std::endl;
    std::cout << "Un mensaje parpadea en la pantalla: 'Memoriza y repite la secuencia de alineacion.'" << std::endl;
    std::cout << "\nSECUENCIA DE CALIBRACION: " << correctSequence << std::endl;
    std::cout << "\nEscribe 'continuar' y presiona Enter para ocultar la secuencia." << std::endl;
        
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Espera a que el usuario escriba "continuar" para ocultar la secuencia
    // Esto permite que el usuario tenga tiempo de memorizar la secuencia antes de que desapare
    std::string confirmation_input = "";
    while (confirmation_input != "continuar") {
        std::cout << "Entrada > ";
        std::getline(std::cin, confirmation_input);
    }
    

       system("cls"); // Limpia la pantalla para que la secuencia no se vea mas.

    

    std::cout << "La secuencia ha desaparecido de la pantalla." << std::endl;
    std::cout << "Introduce la secuencia de calibracion ahora:" << std::endl;
    std::cout << "Entrada > ";

    std::string userInput;
    // Este getline esperara correctamente la entrada del usuario.
    std::getline(std::cin, userInput); 

    // --- Evaluacion ---
    if (userInput == correctSequence) {
        std::cout << "\nSECUENCIA CORRECTA. Calibracion exitosa." << std::endl;
        std::cout << "Los sistemas de defensa de la estacion estan ahora activos y listos para el impacto." << std::endl;
        std::cout << "¡Tarea completada!" << std::endl;
        player.tasksCompleted++;
        gameAreas[areaIndex].completed = true;
    } else {
        std::cout << "\nSECUENCIA INCORRECTA. Calibracion fallida." << std::endl;
        std::cout << "Las torretas se mueven erraticamente y vuelven a su posicion inicial." << std::endl;
        std::cout << "Has perdido un tiempo valioso, los meteoritos están cada vez mas cerca y las defensas siguen inactivas." << std::endl;
    }
}


void executeAiCoreLogic(Player& player, std::vector<Area>& gameAreas) {
    int areaIndex = 6;

    if (gameAreas[areaIndex].completed) {
        std::cout << "La IA funciona con parametros estables. No requiere mas ajustes." << std::endl;
        return;
    }

    // --- El Puzle de Logica ---
    std::string correctAnswer = "flush init ethics";
    std::cout << "La IA principal de la estacion esta en un bucle de errores. Debes reiniciarla manualmente." << std::endl;
    std::cout << "La consola muestra una serie de reglas de diagnostico para un reinicio seguro:" << std::endl;
    
    // Las reglas del puzle
    std::cout << "\n--- REGLAS DE DIAGNOSTICO ---" << std::endl;
    std::cout << "1. El cache de memoria debe ser purgado ANTES de inicializar el kernel." << std::endl;
    std::cout << "2. El modulo de etica debe cargarse DESPUES de que el kernel sea inicializado." << std::endl;
    std::cout << "3. Un reinicio forzado es inestable y NUNCA debe usarse en esta secuencia." << std::endl;
    std::cout << "4. El diagnostico de red es irrelevante para la secuencia de reinicio." << std::endl;

    // Los comandos disponibles
    std::cout << "\n--- COMANDOS DISPONIBLES ---" << std::endl;
    std::cout << "- init    (Inicializa el kernel)" << std::endl;
    std::cout << "- ethics  (Carga el modulo de etica)" << std::endl;
    std::cout << "- flush   (Purga el cache de memoria)" << std::endl;
    std::cout << "- reboot  (Fuerza un reinicio)" << std::endl;
    std::cout << "- network (Diagnostico de red)" << std::endl;

    std::cout << "\nIntroduce los 3 comandos correctos en orden, separados por espacios (ej: flush ... ...)" << std::endl;
    std::cout << "Entrada > ";

    std::string userInput;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, userInput);
    
    // --- Evaluacion ---
    if (userInput == correctAnswer) {
        std::cout << "\nSECUENCIA ACEPTADA. La IA reinicia sus protocolos de forma estable." << std::endl;
        std::cout << "Una voz robotica dice: 'Sistemas en linea. Hola, astronauta.'" << std::endl;
        std::cout << "¡Tarea completada!" << std::endl;
        player.tasksCompleted++;
        gameAreas[areaIndex].completed = true;
    } else {
        std::cout << "\nSECUENCIA RECHAZADA. El nucleo de la IA emite un pulso de energia." << std::endl;
        std::cout << "Las luces parpadean y el sistema vuelve a su estado de error anterior." << std::endl;
        std::cout << "Has fallado en el reinicio. Debes intentarlo de nuevo mas tarde." << std::endl;
    }
}
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
        if (choice == 0) {
            // se pide confirmacion antes de salir
            std::cout << "\n¿Estas seguro de que quieres salir? (s/n)" << std::endl;
            std::cout << "Opcion > ";
            
            char confirmation;
            std::cin >> confirmation;

            // se verifica la respuesta del jugador (aceptamos 's' o 'S')
            if (confirmation == 's' || confirmation == 'S') {
                std::cout << "\nGracias por jugar. ¡Hasta la proxima!" << std::endl;
                break; // Se rompe el bucle y el juego termina
            } else {
                std::cout << "Regresando al juego..." << std::endl;
                // Si no es 's' o 'S', no hacemos nada y el bucle continuara,
                // mostrando el menu de nuevo.
            }

        } else {
            // Si la opcion no es 0, la logica del juego continua como siempre
            navigateToArea(player, gameAreas, choice);
        }

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