[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/mi1WNrHU)
# Proyecto de C++ - ZERO
![Banner](https://github.com/ymill016/Images/blob/main/3.png)

## Equipo

- **Nombre del equipo:** Loop Infinito

### Nombre del Juego
ZERO

### Temática y Ambientación
"ZERO" es un juego de estrategia y supervivencia por turnos ambientado en una estación espacial de investigación que orbita la Tierra. El jugador asume el rol del único astronauta sobreviviente a bordo después de que un fallo crítico en el sistema activara el protocolo de autodestrucción de la nave. Con el tiempo en su contra y la estación colapsando a su alrededor, la misión es una carrera desesperada por la supervivencia.

### Objetivo del Jugador
El objetivo principal es cancelar el protocolo de autodestrucción completando **5 tareas** distribuidas en las diferentes áreas de la estación antes de agotar los **8 turnos** disponibles. El jugador debe ser estratégico en el orden en que visita las salas, minimizar los errores y gestionar sus turnos de la manera más eficiente posible para lograr la victoria.

### Mecánicas Principales y Jugabilidad
El juego se desarrolla a través de una **interfaz de consola basada en menús**, donde el jugador toma decisiones estratégicas en cada turno.

* **Sistema de Turnos**: El jugador comienza con 8 turnos. Viajar a cualquier área de la estación consume un turno.
* **Tareas y Minijuegos**: Cada área de la estación presenta un desafío o minijuego único que pone a prueba diferentes habilidades (lógica, memoria, atención al detalle, etc.).
* **Penalizaciones y Estados**: Fallar en una tarea o tomar una decisión incorrecta puede tener consecuencias, como la pérdida de un turno o la inducción de un estado negativo (como "Infectado"), lo que obliga al jugador a cambiar su estrategia.
* **Condición de Victoria**: Completar 5 tareas antes de que se acaben los turnos.
* **Condición de Derrota**: Agotar los 8 turnos sin haber completado las 5 tareas requeridas.

## Áreas de "ZERO" interáctivo
1. **Command Center:** Tarea de resolver un acertijo logico simple.
2. **Research Lab:** Tarea de completar un problema matematico simple.
3. **Crew Quarters:** Tarea de memorizar contraseña.
4. **Engineering Bay:** Tarea usar la contraseña.
5. **Armory:** Tarea de juego de meteorito.
6. **AI Core:** Responder una secuencia lógica de comandos para reiniciar la IA.
7. **Medical Lab:** Tarea diagnóstico de sistema vital
8. **Hydroponics Garden:** Tarea de regar las plantas correctas segun su pigmentación.

## Aplicación de los Temas Vistos

A continuación, se detalla cómo se implementó en el proyecto cada uno de los temas requeridos por el curso.

***

### Variables y tipos de datos

Se utilizaron diversos tipos de datos para gestionar el estado del juego. Por ejemplo, `int` para los turnos restantes, `bool` para controlar el bucle principal (`isGameOver`), `std::string` para nombres y contraseñas, y `enum` para definir estados específicos del jugador como `HEALTHY` o `SICK`. Estos se agruparon en estructuras para representar las entidades del juego.

***

### Estructuras condicionales (if, else, switch)

Las estructuras condicionales son fundamentales para la lógica del juego. Se usan bloques `if/else` para verificar si una tarea ya fue completada, si el jugador está infectado, o para validar la respuesta en los acertijos. Se utilizó una estructura `switch` para dirigir al jugador a la sala correcta según su elección numérica, ejecutando la función correspondiente a cada área.

***

### Ciclos (for, while, do-while)

Los ciclos son esenciales para el funcionamiento del juego:
* **`while`**: Se utiliza para el bucle principal del juego, que se mantiene activo hasta que se cumple una condición de victoria o derrota.
* **`for`**: Se usa para iterar sobre el vector de áreas y mostrar el menú dinámicamente, y para la cuenta regresiva en el desafío de los camarotes.
* **`do-while`**: Garantiza que se reciba una entrada numérica válida por parte del usuario, repitiendo la solicitud hasta que la entrada sea correcta.

***

### Funciones

El proyecto está altamente modularizado mediante el uso de funciones. Cada función tiene una única responsabilidad, como `loadAreasFromFile()` para cargar los datos del juego, `showMainMenu()` para mostrar la interfaz, o `executeAiCoreLogic()` para manejar la lógica de un acertijo específico. Esto mejora la legibilidad y el mantenimiento del código.

***

### Estructuras de datos

Se utilizaron `structs` como `Player` y `Area` para crear tipos de datos personalizados que modelan las entidades del juego. La estructura de datos principal es un `std::vector<Area>`, que almacena todas las salas del juego de forma dinámica, permitiendo que el juego se adapte fácilmente si se añaden o quitan áreas del archivo de datos.

***

### Manejo de archivos

El juego implementa un diseño dirigido por datos, cargando la información de las áreas (ID, nombre y descripción) desde un archivo de texto externo (`data/areas.txt`). Esto se realiza mediante el uso de `std::ifstream` de la librería `<fstream>`, lo que permite modificar o añadir contenido al juego sin recompilar el código fuente.

***

### Manejo de errores

Se implementaron varios mecanismos de manejo de errores. El más crítico es la validación al abrir archivos, donde el programa notifica al usuario y termina de forma controlada si `data/areas.txt` no se encuentra. Adicionalmente, se valida la entrada del usuario con `std::cin.fail()` para evitar que el programa falle si se introduce texto en lugar de números.

***

### Interfaz por consola

Toda la interacción con el jugador se realiza a través de la interfaz de consola. Se utilizan `std::cout` para mostrar menús, descripciones y resultados, y `std::cin` junto con `std::getline` para capturar las decisiones del jugador. Se creó una función `clearScreen()` para limpiar la pantalla y mejorar la experiencia en los puzles de memoria.

## Consideraciones técnicas del desarrollo
Para la construcción del proyecto "ZERO", se tomaron en cuenta los siguientes aspectos técnicos, adhiriéndose a los requisitos del curso y aplicando buenas prácticas de programación.

**Lenguaje y Paradigma de Programación**

El proyecto fue desarrollado íntegramente en C++. 

Se optó por un paradigma de programación procedural, donde la lógica del juego se estructura a través de funciones y el estado se gestiona mediante estructuras de datos (structs). Esta decisión se tomó para cumplir estrictamente con los temas cubiertos en el curso, enfocándose en la modularización a través de funciones

**Estructura del Proyecto**
El código fuente fue organizado para maximizar la claridad y la modularización, siguiendo las indicaciones del proyecto:

main.cpp: Ubicado en la raíz del proyecto, su única responsabilidad es iniciar el juego a través de una sola llamada a la función runGame(), manteniendo el punto de entrada lo más limpio posible.

Carpeta src/: Contiene todos los archivos de código fuente (.h y .cpp). La lógica del juego, las estructuras de datos y las funciones auxiliares se separaron en 

game_logic y game_structs para facilitar el mantenimiento y la lectura del código.

Carpeta data/: Almacena archivos externos, como areas.txt. Esta separación sigue el principio de diseño dirigido por datos, donde la información del juego (como las descripciones de las salas) se desacopla del código fuente.

**Gestión de Datos**

Estructuras de Datos (structs): Se utilizaron structs (Player, Area) para modelar las entidades principales del juego, agrupando variables relacionadas como el estado del jugador, los turnos restantes, y la información de cada sala.

Manejo de Archivos: La información de todas las áreas del juego se carga desde areas.txt al iniciar el programa. Esto se logra utilizando la librería fstream, cumpliendo con el requisito de manejo de archivos y haciendo el juego fácilmente expandible sin necesidad de recompilar el código.

Contenedores Dinámicos: Se utilizó un std::vector<Area> para almacenar las salas del juego, lo que permite una gestión de memoria dinámica y un acceso eficiente a los datos de cada área.

**Manejo de la Lógica y Flujo del Juego**
Bucle de Juego Principal: El corazón del programa es la función runGame(), que contiene un bucle while que se ejecuta mientras el juego no haya terminado. Este bucle se encarga de mostrar el menú, procesar la entrada del jugador y verificar las condiciones de victoria o derrota en cada ciclo.

Entrada de Usuario Robusta: Se implementaron técnicas para prevenir errores comunes de entrada en la consola. Se utilizó std::cin.ignore() para limpiar el buffer de entrada antes de leer texto con std::getline, evitando que el programa se salte entradas del jugador. Esto es parte del manejo de errores y buenas prácticas.

**Funcionalidades Específicas**

Limpieza de Pantalla Multiplataforma: Se creó una función clearScreen() que utiliza directivas de preprocesador (#ifdef _WIN32) para ejecutar system("cls") en Windows y system("clear") en sistemas operativos tipo UNIX (Linux, macOS). Esto permite que la misma base de código funcione en diferentes plataformas.

## Imagenes del juego
## Menu
![Banner](https://github.com/ymill016/Images/blob/main/menu.png)
## Armeria
![Banner](https://github.com/ymill016/Images/blob/main/armeria.png)
## IA
![Banner](https://github.com/ymill016/Images/blob/main/IA.png)
## Camarotes
![Banner](https://github.com/ymill016/Images/blob/main/camarotes.png)

### Integrantes del equipo

1. **Nombre completo:** Krissia Yamileth Menjívar Morales
   **Carnet:** 00083924

2. **Nombre completo:** Josué Alexander Rodriguez Orellana
   **Carnet:** 00254125

3. **Nombre completo:** Brandon Daniel Sanchez Santamaria 
   **Carnet:** 00064025

4. **Nombre completo:** Melanie Yanina Villeda Marquez 
   **Carnet:** 00185125 

## Instrucciones de Ejecución

1. Clona este repositorio en tu máquina local:
   ```bash
   git clone https://github.com/FDP-01-2025/project-loop-infinito.git
2. Busca el archivo en la carpeta previamente clonada bajo el nombre [project-loop-infinito].
3. Abrelo en GitHub.
4. Crea una nueva terminal:
   ```bash
   g++ main.cpp src/game_logic.cpp -o ZERO_GAME -std=c++17
5. Y ejecutalo:
   ```bash
   ./zero
