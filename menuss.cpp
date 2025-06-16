#include <iostream>

using namespace std;

void mainMenu(int &turnsLeft, int &tasksCompleted);

int main() {
    int turnsLeft = 8;         // 8 turns total
    int tasksCompleted = 0;    // tasks completed

    mainMenu(turnsLeft, tasksCompleted);

    cout << "Game Over. Thanks for playing!" << endl;

    return 0;
}

void mainMenu(int &turnsLeft, int &tasksCompleted) {
    int choice;

    do {
        cout << "\n=== Main Menu ===" << endl;
        cout << "Turns left: " << turnsLeft << endl;
        cout << "Tasks completed: " << tasksCompleted << endl;
        cout << "1. Go to Tasks Menu" << endl;
        cout << "2. Exit Game" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Opening Tasks Menu..." << endl;
                // Aquí se llamaría a la función del menú de tareas.
                // Por ahora, solo simula una tarea realizada y un turno utilizado.
                if (turnsLeft > 0) {
                    tasksCompleted++;
                    turnsLeft--;
                    cout << "You completed a task! Tasks completed: " << tasksCompleted << endl;
                } else {
                    cout << "No turns left!" << endl;
                }
                break;
            case 2:
                cout << "Exiting game..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }

    } while(choice != 2 && turnsLeft > 0);
}
