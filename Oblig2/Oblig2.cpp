#include <iostream>
#include <cstdlib>
#include <time.h>
#include <list>
#include <chrono>

using namespace std;

void bubblesort(list<int>& unsorted, list<int>& sorted) {
    int size = unsorted.size();
    for (int i = 0; i < size - 1; i++) {

        //temporary variable storing current biggest element
        int t = unsorted.front();
        unsorted.pop_front();

        //Finding the biggest element and pushing it to the end
        for (int j = 0; j < size - 1 - i; j++) {
            if (t >= unsorted.front()) {
                unsorted.push_back(unsorted.front());
                unsorted.pop_front();
            }
            else {
                unsorted.push_back(t);
                t = unsorted.front();
                unsorted.pop_front();
            }
        }

        //Adding biggest element to the sorted list
        sorted.push_front(t);
    }

    //This surprised me a bit, I was unsure of why I needed to add this, but it works
    sorted.push_front(unsorted.front());
}


//The two next functions belongs to merge sort
list <int> merge(list<int>& listA, list<int>& listB) {
    list <int> listC = {};

    //Sorting elements and putting them in the correct list
    while (!listA.empty() && !listB.empty()) {
        if (listA.front() > listB.front()) {
            listC.push_back(listB.front());
            listB.pop_front();
        }
        else {
            listC.push_back(listA.front());
            listA.pop_front();
        }
    }

    //Adding the remaining elements when one list is empty
    while (!listA.empty()) {
        listC.push_back(listA.front());
        listA.pop_front();
    }
    while (!listB.empty()) {
        listC.push_back(listB.front());
        listB.pop_front();
    }
    return listC;
}

list <int> mergesort(list<int>& unsorted) {
    if (unsorted.size() == 1) {
        return unsorted;
    }

    //Temporary lists that will be merged
    list <int> tempA = {};
    list <int> tempB = {};

    int size = unsorted.size();
    for (int i = 0; i < size / 2; i++) {
        tempA.push_back(unsorted.front());
        unsorted.pop_front();
    }
    while (!unsorted.empty()) {
        tempB.push_back(unsorted.front());
        unsorted.pop_front();
    }

    //Recursive calls
    tempA = mergesort(tempA);
    tempB = mergesort(tempB);

    return merge(tempA, tempB);
}

//The two next functions belongs to quick sort
int partition(list<int>& listA, int low, int high) {
    int size = listA.size();

    //Two lists to store elements outside of the partition being worked on
    list <int> tempLeft = {};
    list <int> tempRight = {};

    //Storing elements lower than the pivot, the higher ones are pushed to the end of the current partition
    list <int> tempPartLeft = {};

    //Temporary removing elements in list outside of partition
    if (low != 0) {
        for (int i = 0; i < low; i++) {
            tempLeft.push_back(listA.front());
            listA.pop_front();
        }
    }
    if (high != size-1) {
        for (int i = size - 1; i > high; i--) {
            tempRight.push_front(listA.back());
            listA.pop_back();
        }
    }

    //Using the last element as the pivot
    int pivot = listA.back();
    listA.pop_back();

    //Sorting elements
    int tempSize = listA.size();
    for (int i = 0; i < tempSize;i++) {
        if (listA.front() < pivot) {
            tempPartLeft.push_back(listA.front());
        }
        else {
            listA.push_back(listA.front());
        }
        listA.pop_front();
    }

    //Finding the spot of the pivot
    int location = tempLeft.size()  + tempPartLeft.size();

    int leftsize = tempLeft.size();
    int rightsize = tempRight.size();
    int partsize = tempPartLeft.size();

    //Adding all the elements in their (current) correct spot (or partition)
    listA.push_front(pivot);

    for (int i = 0; i < partsize; i++) {
        listA.push_front(tempPartLeft.back());
        tempPartLeft.pop_back();
    }

    for (int i = 0; i < leftsize; i++) {
        listA.push_front(tempLeft.back());
        tempLeft.pop_back();
    }

    for (int i = 0; i < rightsize; i++) {
        listA.push_back(tempRight.front());
        tempRight.pop_front();
    }
    return location;
}

void quicksort(list<int>& listA, int low, int high) {
    if (low < high) {

        //Partitioning and finding pivot location
        int pivot_location = partition(listA, low, high);

        //Recursive calls
        quicksort(listA, low, pivot_location-1);
        quicksort(listA, pivot_location + 1,high);
    }
}

list<int> unsorted {};
list<int> sorted {};

int main()
{
    srand(time(0));

    cout << "Bubble Sort: " << endl <<endl;

    //This section is just running the algorithms

    for (int n = 10; n <= 10000; n *= 10) {

        unsorted = {};
        sorted = {};

        //Filling a list with random numbers
        for (int i = 0; i <n ; i++) {
            unsorted.push_back(rand() % (n));
        }
        cout << "Unsorted list: " << endl;
        for (int n : unsorted) {
            cout << n << ", ";
        }
        cout << endl;

        //Timing and running the algorithm
        auto start = std::chrono::high_resolution_clock::now();
        bubblesort(unsorted,sorted);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();


        cout << "Sorted list: " << endl;
        for (int n : sorted) {
            cout << n << ", ";
        }
        cout << endl;
        cout << "Size: " << sorted.size() << " Time: " << duration << "ms" << endl;
        cin.ignore();
    }

    cout << "Merge Sort: " << endl << endl;

    for (int n = 10; n <= 10000; n *= 10) {
        unsorted = {};
        sorted = {};

        for (int i = 0; i < n; i++) {
            unsorted.push_back(rand() % (n));
        }
        cout << "Unsorted list: " << endl;
        for (int n : unsorted) {
            cout << n << ", ";
        }
        cout << endl;

        auto start = std::chrono::high_resolution_clock::now();
        sorted = mergesort(unsorted);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        cout << "Sorted list: " << endl;
        for (int n : sorted) {
            cout << n << ", ";
        }
        cout << endl;
        cout << "Size: " << sorted.size() << " Time: " << duration << "ms" << endl;
        cin.ignore();
    }

    cout << "Quick Sort: " << endl << endl;

    for (int n = 10; n <= 10000; n *= 10) {
        unsorted = {};

        for (int i = 0; i < n; i++) {
            unsorted.push_back(rand() % (n));
        }
        cout << "Unsorted list: " << endl;
        for (int n : unsorted) {
            cout << n << ", ";
        }
        cout << endl;

        auto start = std::chrono::high_resolution_clock::now();
        quicksort(unsorted, 0, n - 1);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        cout << "Sorted list: " << endl;
        for (int n : unsorted) {
            cout << n << ", ";
        }
        cout << endl;
        cout << "Size: " << unsorted.size() << " Time: " << duration << "ms" << endl;
        cin.ignore();
    }

    return 0;
}
