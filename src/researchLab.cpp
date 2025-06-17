//Area 2: Research Lab: Task to complete a simple math problem.

#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

// random number function
int randomNumber(int min, int max)
{ // parameters to set a range for the random number
    return min + rand() % (max - min + 1);
}

bool researchLab(){
    int x, y;

    int answerInput = 0;
    x = randomNumber(1, 10);
    y = randomNumber(1, 10);
    int correctAnswer = 3 * pow(x, 2) + 4 * y; // arithmetic operation 3x^2 + 4y

    cout << "Solve the following math problem: ";
    cout << "If x = " << x << " and y = " << y << ", then what is 3x^2 + 4y?\n";
    cout << "Answer: ";
    cin >> answerInput;
    return answerInput == correctAnswer; // return value 1 or 0
}

int main (){
    if (researchLab()){
        cout << "Task completed\n";
    } else {
        cout << "You failed\n";
    }
    return 0;
}
