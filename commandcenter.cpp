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
bool flujoCommandCenter (string pregunta, char respuestaCorrecta){
    char respuestaIngresada;
    cout << pregunta << "\n";
    cin >> respuestaIngresada;
    return respuestaIngresada == respuestaCorrecta;
}

int commandCenter (){
    int aleatorio = numeroAleatorio (1,3);

    switch (aleatorio)
    {
    case 1:
        cout << flujoCommandCenter("Un tren eléctrico va de norte a sur. El viento sopla de este a oeste.\n¿Hacia dónde va el humo?\na. Hacia el Norte\nb. Hacia el oeste\nc. Hacia ningún lado\n",'c');
        break;
    case 2:
    cout << flujoCommandCenter()
    default:
        break;
    }
    }


int main (){
    return 0;
}
