#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h> 
#include <windows.h> 

using namespace std;

const int filas = 10;
const int columnas = 10;
char tablero[filas][columnas];
int jugadorPos = columnas / 2;
int meteoritoX, meteoritoY;

void inicializarTablero() {
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < columnas; ++j)
            tablero[i][j] = ' ';
    tablero[filas - 1][jugadorPos] = 'A'; // Jugador
}

void generarMeteorito() {
    meteoritoX = 0;
    meteoritoY = rand() % columnas;
    tablero[meteoritoX][meteoritoY] = '*';
}

void moverMeteorito() {
    if (meteoritoX < filas - 1) {
        tablero[meteoritoX][meteoritoY] = ' ';
        meteoritoX++;
        if (tablero[meteoritoX][meteoritoY] == 'A') {
            cout << "¡Has sido golpeado por un meteorito! 💥" << endl;
            exit(0);
        }
        tablero[meteoritoX][meteoritoY] = '*';
    } else {
        tablero[meteoritoX][meteoritoY] = ' ';
        generarMeteorito();
    }
}

void moverJugador(char direccion) {
    tablero[filas - 1][jugadorPos] = ' ';
    if (direccion == 'a' && jugadorPos > 0)
        jugadorPos--;
    else if (direccion == 'd' && jugadorPos < columnas - 1)
        jugadorPos++;
    tablero[filas - 1][jugadorPos] = 'A';
}

void mostrarTablero() {
    system("cls"); // Limpiar pantalla (Windows)
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j)
            cout << "[" << tablero[i][j] << "]";
        cout << endl;
    }
}

int main() {
    srand(time(0));
    inicializarTablero();
    generarMeteorito();

    while (true) {
        if (_kbhit()) {
            char tecla = _getch();
            moverJugador(tecla);
        }
        moverMeteorito();
        mostrarTablero();
        Sleep(300); // Retardo para ver movimiento
    }

    return 0;
}