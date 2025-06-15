//Engineering Bay: Ingresar la contraseña

#include <iostream>
#include <ctime>
using namespace std;

int codigoGlobal; //variable genearal del codigo

// función de numeros aleatorios
int numeroAleatorio(int min, int max)
{ // parametros para establecer un rango de numero aleatorio
    return min + rand() % (max - min + 1);
}

//funcion para mostrar el codigo generado
bool crewQuarters(){ 
    codigoGlobal = numeroAleatorio(1000,9999);
    int regresar;
    cout << "Memoriza esta constraseña/codigo: "<< codigoGlobal << "\nEs una Mouseketool que nos ayudará mas tarde\n";
    cout << "Ingresa 1 para completar la tarea: ";
    cin >> regresar;
    return regresar == 1;
}

//funcion para ingresar el codigo generado mostrado anteriormente
bool engineeringBay (){
    int contraIngresada = 0;
    cout << "Ingresa la contraseña: ";
    cin >> contraIngresada;
    return codigoGlobal == contraIngresada;
}

int main (){
    srand(time(0));
 
        if (crewQuarters()){
        cout << "Tarea completada\n";
    }else{
        cout << "Fallastes\n";
    }

    if (engineeringBay()){
        cout << "Tarea completada\n";
    }else {
        cout << "Fallastes\n";
    }
    return 0;
}