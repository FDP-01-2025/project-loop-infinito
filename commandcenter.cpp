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
bool commandCenter (char respuestaUno, char respuestaDos,char res){

    switch (numeroAleatorio(1,3))
    {
    case 1:
        cout << "Un tren eléctrico va de norte a sur. El viento sopla de este a oeste.\n¿Hacia dónde va el humo?"<< "\n";
        cout <<"a. Hacia el sur\nb. Hacia el este\nc. Hacia ningún lado\n";
        cout << "Respuesta(letra en minuscula): ";
        cin >> respuestaUno;

        if (respuestaUno == 'c'){
            cout << "¡Tarea completada!\nIngresa 1 para regresar.\n";

        }
        break;
    case 2:
    break;

    case 3:
    break;
    
    default:
        break;
    }

    return 0;
}

int main (){
    srand(time(0));
    return 0;
}
