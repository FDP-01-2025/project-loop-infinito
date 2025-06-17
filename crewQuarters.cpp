//Crew Quarters: Task to memorize password

#include <iostream>
#include <ctime>
using namespace std;

int generalCode; //general variable for the code

// random number function
int randomNumber(int min, int max)
{ // parameters to set a range for the random number
    return min + rand() % (max - min + 1);
}

// function to display the generated code
bool crewQuarters(){ 
    // initializing the "generalCode" variable with a number generated in the range [1000,9999]
    generalCode = randomNumber(1000,9999);
    int goBack;
    cout << "Remember this password: " << generalCode << "\nIt's a Mouseketool that will help us later\n";
    cout << "Enter 1 to complete task: ";
    cin >> goBack;
    return goBack == 1;
}

int main (){
    if (crewQuarters()){
        cout << "Task completed";
    }

    return 0;
}
