//Engineering Bay: Ingresar la contraseña

#include <iostream>
#include <ctime>
using namespace std;

// función de numeros aleatorios
int numeroAleatorio(int min, int max)
{ // parametros para establecer un rango de numero aleatorio
    return min + rand() % (max - min + 1);
}

bool crewQuarters(){
    int contra = numeroAleatorio(1000,9999);
    int regresar;
    cout << "Memoriza esta constraseña/codigo: "<< contra << "\nEs una Mouseketool que nos ayudará mas tarde\n";
    cout << "Ingresa 1 para completar la tarea: ";
    cin >> regresar;
    return true;
}

bool engineeringBay (){
    int contraIngresada = 0;
    cout << "Ingresa la contraseña: " << contraIngresada << "\n";
    
}

int main (){
    return 0;
}