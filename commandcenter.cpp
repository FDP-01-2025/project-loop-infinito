/*Area número 1: Command Center
tarea de resolver un acertijo simple*/

#include <iostream>
#include <ctime>
using namespace std;


int numeroAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

bool commandCenter (char respuestaUno, char respuestaDos,char res){

    switch (numeroAleatorio(1,3))
    {
    case 1:
        cout << "Un tren eléctrico va de norte a sur. El viento sopla de este a oeste.\n¿Hacia dónde va el humo?"<< "\n";
        cout <<"a. Hacia el sur\nb. Hacia el este\nc. Hacia ningún lado\n";
        cin <<
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
