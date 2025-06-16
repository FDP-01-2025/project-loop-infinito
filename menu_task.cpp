#include <iostream>

using namespace std;

void tasksMenu(int &turnsLeft, int &tasksCompleted);

int main() {
    int turnsLeft = 8;
    int tasksCompleted = 0;

    tasksMenu(turnsLeft, tasksCompleted);

    cout << "Exiting Tasks Menu." << endl;

    return 0;
}

void tasksMenu(int &turnsLeft, int &tasksCompleted) {
    int choice;

    do {
        cout << "\n=== Tasks Menu ===" << endl;
        cout << "Turns left: " << turnsLeft << endl;
        cout << "Tasks completed: " << tasksCompleted << endl;
        cout << "Select an area to perform a task:" << endl;
        cout << "1. Command Center" << endl;
        cout << "2. Research Lab" << endl;
        cout << "3. Crew Quarters" << endl;
        cout << "4. Engineering Bay" << endl;
        cout << "5. Armory" << endl;
        cout << "6. AI Core" << endl;
        cout << "7. Medical Lab" << endl;
        cout << "8. Hydroponics Garden" << endl;
        cout << "9. Return to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >=1 && choice <=8) {
            if (turnsLeft > 0) {
                tasksCompleted++;
                turnsLeft--;
                cout << "Task in area " << choice << " completed!" << endl;
            } else {
                cout << "No turns left!" << endl;
            }
        } else if (choice == 9) {
            cout << "Returning to Main Menu..." << endl;
        } else {
            cout << "Invalid choice, please try again." << endl;
        }

    } while(choice != 9 && turnsLeft > 0);
}
