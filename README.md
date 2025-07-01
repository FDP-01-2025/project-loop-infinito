[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/mi1WNrHU)
# Proyecto de C++ - ZERO

## Descripción del Proyecto

La estacion espacial “ZERO” es un centro de investigacion que orbita la Tierra. El jugador asume el rol de un astronauta, quien ha quedado atrapado en la nave, que ha activado el protocolo de autodestrucción tras el un fallo del sistema principal. Como el único tecnico espacial, el jugador tiene que recorrer la nave para poder completar una serie de tareas (mini juegos) para evitar que la nave colapse.

![Banner](https://github.com/ymill016/Images/blob/main/3.png)

## Equipo

- **Nombre del equipo:** Loop Infinito

### Integrantes del equipo

1. **Nombre completo:** Krissia Yamileth Menjívar Morales
   **Carnet:** 00083924

2. **Nombre completo:** Josué Alexander Rodriguez Orellana
   **Carnet:** 00254125

3. **Nombre completo:** Brandon Daniel Sanchez Santamaria 
   **Carnet:** 00064025

4. **Nombre completo:** Melanie Yanina Villeda Marquez 
   **Carnet:** 00185125 

## Jugabilidad y mecánica principal
1. El juego se basa en un menú de opciones.
2. El jugador puede moverse según su elección.
3. El jugador inicia con 8 turnos para completar tareas.
4. Cada área de la estación tiene sus propias tareas.
5. **Victoria:** El jugado tiene que completar 5 tareas en 8 turnos o menos.
6. **Penalizacion:** Fallar una tarea reduce un turno.
7. **Derrota:** Agotar los turnos sín completar las tareas restantes.

## Áreas de "ZERO" interáctivo
1. **Command Center:** Tarea de resolver un acertijo logico simple.
2. **Research Lab:** Tarea de completar un problema matematico simple.
3. **Crew Quarters:** Tarea de memorizar contraseña.
4. **Engineering Bay:** Tarea usar la contraseña.
5. **Armory:** Tarea de juego de meteorito.
6. **AI Core:** Responder una secuencia lógica de comandos para reiniciar la IA.
7. **Medical Lab:** Tarea diagnóstico de sistema vital
8. **Hydroponics Garden:** Tarea de regar las plantas correctas segun su pigmentación.

## Temas a implementar
1. Uso de condicionales para validar las acciones del jugador y la estructura del juego,y saber en que condiciones puede ganar, perder y penalizar.
2. Uso de menus, para mostrarle al jugador las desiciones y acciones que puede realizar.
3. Uso de bucles para repetir tareas y volver al menu principal despues de cada tarea terminada.
4. Uso de variables para almacenar datos del juego, como el status del jugador.
5. Uso de funciones para estructurar el codigo de manera mas clara y ordenada.

## Instrucciones de Ejecución

1. Clona este repositorio en tu máquina local:
   ```bash
   git clone https://github.com/FDP-01-2025/project-loop-infinito.git
2. Busca el archivo en la carpeta previamente clonada bajo el nombre [project-loop-infinito].
3. Abrelo en GitHub.
4. Crea una nueva terminal:
   ```bash
   g++ -o zero zero.cpp
5. Y ejecutalo:
   ```bash
   ./zero
