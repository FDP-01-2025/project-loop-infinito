/*Area número 1: Command Center
tarea de resolver un acertijo simple*/

#include <iostream>
#include <ctime> 
using namespace std;

//función de numeros aleatorios
int numeroAleatorio(int min, int max) { //parametros para establecer un rango de numero aleatorio
    return min + rand() % (max - min + 1);
}


//función de tipo booleana que regresa 1 ó 0 (verdadero o falso)

//Área 1: Commmand Center
bool commandCenter (string pregunta, char respuestaCorrecta){
    char respuestaIngresada;
    cout << pregunta << "\n";
    cin >> respuestaIngresada;
    return respuestaIngresada == respuestaCorrecta;
}


int main (){
    return 0;
}
