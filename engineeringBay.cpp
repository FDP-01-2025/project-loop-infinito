//Engineering Bay: Ingresar la contraseña

#include <iostream>
#include <ctime>
using namespace std;

// función de numeros aleatorios
int numeroAleatorio(int min, int max)
{ // parametros para establecer un rango de numero aleatorio
    return min + rand() % (max - min + 1);
}

bool crewQuarters(int& codigoGenerado){ //int& para que sea un valor fijo
    codigoGenerado = numeroAleatorio(1000,9999);
    int regresar;
    cout << "Memoriza esta constraseña/codigo: "<< codigoGenerado << "\nEs una Mouseketool que nos ayudará mas tarde\n";
    cout << "Ingresa 1 para completar la tarea: ";
    cin >> regresar;
    return regresar == 1;
}

bool engineeringBay (int codigoCorrecto){
    int contraIngresada = 0;
    cout << "Ingresa la contraseña: ";
    cin >> contraIngresada;
    return codigoCorrecto == contraIngresada;
}

int main (){
    srand(time(0));
    int code;
 
        if (crewQuarters(code)){
        cout << "Tarea completada\n";
    }

    if (engineeringBay(code)){
        cout << "Tarea completada";
    }else {
        cout << "fallastes";
    }
    return 0;
}