//Engineering Bay: Ingresar la contraseña

#include <iostream>
#include <ctime>
using namespace std;

int generalCode; //variable genearal del codigo

// función de numeros aleatorios
int randomNumber(int min, int max)
{ // parametros para establecer un rango de numero aleatorio
    return min + rand() % (max - min + 1);
}

//funcion para mostrar el codigo generado
bool crewQuarters(){ 
    //inicializando la variable "generalCode" con el numero generado en el rango [1000,9999]
    generalCode = randomNumber(1000,9999);
    int goBack;
    cout << "Remember this password: "<< generalCode << "\nIt's a Mouseketool that will help us later\n";
    cout << "Enter 1 to complete task: ";
    cin >> goBack;
    return goBack == 1;
}

//funcion para ingresar el codigo generado mostrado anteriormente
bool engineeringBay (){
    int enteredCode = 0;
    cout << "Enter the generated password: ";
    cin >> enteredCode;
    return generalCode == enteredCode;
}

int main (){
    srand(time(0));
 
        if (crewQuarters()){
        cout << "Task completed\n";
    }else{
        cout << "Fallastes\n";
    }

    if (engineeringBay()){
        cout << "Tarea completada\n";
    }else {
        cout << "You have failed the task\n";
    }
    return 0;
}