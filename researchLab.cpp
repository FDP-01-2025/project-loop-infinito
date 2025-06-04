//Área 2: Research Lab: Tarea de completar un problema matematico simple.

#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

// función de numeros aleatorios
int numeroAleatorio(int min, int max)
{ // parametros para establecer un rango de numero aleatorio
    return min + rand() % (max - min + 1);
}

bool researchLab(){
    int x,y;

    int respuestaPregunta = 0;
    x = numeroAleatorio(1,10);
    y = numeroAleatorio (1,10);
    int respuesta = 3 * pow (x,2) +4 * y;//operacion aritmetica 3x^2+4y

    cout << "Resuelve el siguiente problema matemático: ";
    cout << "Sí x = " << x << " y si y = " << y << " entonces 3x^2 + 4y es ?\n";
    cout << "Respuesta: ";
    cin >> respuestaPregunta;
    return respuestaPregunta == respuesta; //devolver valor 1 o 0
}