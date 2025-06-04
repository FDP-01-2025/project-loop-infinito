/*Area número 1: Command Center
tarea de resolver un acertijo simple*/

#include <iostream>
#include <ctime>
using namespace std;

// función de numeros aleatorios
int numeroAleatorio(int min, int max)
{ // parametros para establecer un rango de numero aleatorio
    return min + rand() % (max - min + 1);
}

// función de tipo booleana que regresa 1 ó 0 (verdadero o falso)

// Área 1: Commmand Center
//funcion para cambiar de acertijos y su respuestas
bool flujoCommandCenter(string pregunta, char respuestaCorrecta)
{
    char respuestaIngresada;
    cout << "Resuelve el sigiente acertijo lógico:\n";
    cout << pregunta << "\n";
    cin >> respuestaIngresada;
    return respuestaIngresada == respuestaCorrecta;
}
//funcion principal de command center: 3 acertijos distintos
bool commandCenter()
{
    int aleatorio = numeroAleatorio(1, 3);

    switch (aleatorio)
    {
    case 1:
        return flujoCommandCenter("Un tren eléctrico va de norte a sur. El viento sopla de este a oeste.\n¿Hacia dónde va el humo?\na. Hacia el Norte  b. Hacia el oeste  c. Hacia ningún lado\n", 'c');
        break;
    case 2:
        return flujoCommandCenter("¿Qué palabra de cuatro letras contiene seis?\na. ocho  b. seis  c. luna\n", 'b');
        break;
    case 3:
        return flujoCommandCenter("¿Qué sube, pero nunca baja?\na. Tu edad  b. El sol  c. La marea\n", 'a');
        break;

    default:
        return;
    }
}

int main()
{
    srand(time(0));
    return 0;
}
