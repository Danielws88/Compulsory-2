#include <iostream>
#include <cstdlib>
#include <time.h>
#include <list>
using namespace std;


int main()
{
    srand(time(0));

    list<int> numbers {};

    for (int i = 0; i < 10; i++) {
        numbers.push_back(rand() % 100);
    }
    
    cout << "Unsorted list: " << endl;

    for (int number : numbers) {
        cout << number << ", ";
    }

    cout << endl;



    return 0;
}
