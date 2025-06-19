#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h> // Para Sleep()

using namespace std;

vector<string> comandos = {"RUN", "CHK", "RST", "DBG", "LOAD"};
vector<string> secuenciaIA;

void mostrarSecuencia() {
    cout << "\n📡 Secuencia de reinicio de IA:\n";
    for (string cmd : secuenciaIA) {
        cout << cmd << " ";
        Sleep(1000); // Mostrar cada comando por 1 segundo
    }
    cout << "\n\nTu turno:\n";
}

bool verificarRespuesta() {
    for (size_t i = 0; i < secuenciaIA.size(); ++i) {
        string entrada;
        cout << "Comando #" << i + 1 << ": ";
        cin >> entrada;

        // Convertir entrada a mayúsculas por si acaso
        for (char &c : entrada) c = toupper(c);

        if (entrada != secuenciaIA[i]) {
            cout << "❌ Comando incorrecto. Reinicio de IA fallido.\n";
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(0));
    int nivel = 1;

    cout << "🤖 SIMULADOR DE REINICIO DE IA 🤖\n";
    cout << "Repite correctamente la secuencia de comandos para reiniciar la IA.\n";

    while (true) {
        cout << "\n🔄 Nivel " << nivel << ":\n";
        secuenciaIA.push_back(comandos[rand() % comandos.size()]);
        mostrarSecuencia();

        if (!verificarRespuesta()) {
            cout << "🔁 Volviendo al nivel 1...\n";
            secuenciaIA.clear();
            nivel = 1;
            continue;
        }

        cout << "✅ Secuencia correcta. Avanzando al siguiente nivel.\n";
        nivel++;
        Sleep(1000);
        system("cls");
    }

    return 0;
}