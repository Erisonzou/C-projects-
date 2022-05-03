#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

bool in_Array(int arr[], int number)
{
    for (int i = 0; i < 5; i++)
    {
        if (arr[i] == number)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    const int WhiteBalls = 69;
    const int WhitePicks = 5;
    const int RedBalls = 26;
    int randomArray[WhitePicks];
    int number_of_games;

   cout << "How many games would you like to play? ";
   cin >> number_of_games;

    srand((unsigned)time(0));

    for (int i = 0; i < number_of_games; i++)
    {

        for (int j = 0; j < WhitePicks; j++)
        {
            int random_number = (rand() % WhiteBalls) + 1;
            while (in_Array(randomArray, random_number))
            {
                random_number = (rand() % WhiteBalls) + 1;
            }

            randomArray[j] = random_number;
        }

        sort(randomArray, randomArray + WhitePicks);
        cout << "White Balls are: ";

        for (int number_in_array : randomArray)
        {
            cout << number_in_array << " ";
        }

        int PowerBall = (rand() % RedBalls) + 1;
        cout << "Powerball is: " << PowerBall;
        cout << endl;
    }

    return 0;
}
