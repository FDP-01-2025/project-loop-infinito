/*Area number 1: Command Center
task to solve a simple riddle*/

#include <iostream>
#include <ctime>
using namespace std;

// random number function
int randomNumber(int min, int max)
{ // parameters to set a random number range
    return min + rand() % (max - min + 1);
}

// boolean function that returns 1 or 0 (true or false)

// Area 1: Command Center
// function to switch between riddles and their answers
bool commandCenterFlow(string question, char correctAnswer)
{
    char userAnswer;
    cout << "Solve the following logic riddle:\n";
    cout << question << "\n";
    cin >> userAnswer;
    return userAnswer == correctAnswer;
}

// main function of command center: 3 different riddles
bool commandCenter()
{
    int random = randomNumber(1, 3);

    switch (random)
    {
    case 1:
        return commandCenterFlow("An electric train is going from north to south. The wind blows from east to west.\nWhere does the smoke go?\na. North  b. West  c. Nowhere\n", 'c');
        break;
    case 2:
        return commandCenterFlow("What four-letter word contains six?\na. eight  b. six  c. moon\n", 'b');
        break;
    case 3:
        return commandCenterFlow("What goes up but never comes down?\na. Your age  b. The sun  c. The tide\n", 'a');
        break;

    default:
        return false;
    }
}

int main()
{
    srand(time(0));
    return 0;
}

