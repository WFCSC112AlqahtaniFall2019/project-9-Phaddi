//Ryan Phadnis
//CSC 112 Project 9

#include <iostream>
#include "data.h"
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <ctime>
using namespace std;

//swap function
template <typename T>
void swap(T *a, T *b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

//bubble sort
template<typename T>
void bubbleSort(vector<T> &arr, int size)
{
    bool swapped;
    for(int i = 0; i < size-1; i++)
    {
        swapped = false;
        for(int j = 0; j < size-1-i; j++)
        {
            if(arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
    }
}

//Selection sort
template<typename T>
void selectionSort(vector<T> &arr, int n)
{
    int i;
    int j;
    int min;
    for(i = 0; i < n-1; i++)
    {
        min = i;
        for(j = i+1; j < n; j++)
        {
            if(arr.at(j) > arr.at(min))
            {
                min = j;
            }
        }
        swap(&arr.at(min), &arr.at(i));
    }
}

//Merge Sort (from Zybooks 15.9) - changed from array to vector
template<typename T>
void Merge(vector<T> &numbers, int i, int j, int k) {
    int mergedSize;                            // Size of merged partition
    int mergePos;                              // Position to insert merged number
    int leftPos;                               // Position of elements in left partition
    int rightPos;                              // Position of elements in right partition

    mergePos = 0;
    mergedSize = k - i + 1;
    leftPos = i;                               // Initialize left partition position
    rightPos = j + 1;                          // Initialize right partition position
    vector<T> mergedNumbers(mergedSize);       // Dynamically allocates temporary array
    // for merged numbers

    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= j && rightPos <= k) {
        if (numbers.at(leftPos) < numbers.at(rightPos)) {
            mergedNumbers.at(mergePos) = numbers.at(leftPos);
            ++leftPos;
        }
        else {
            mergedNumbers.at(mergePos) = numbers.at(rightPos);
            ++rightPos;

        }
        ++mergePos;
    }

    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= j) {
        mergedNumbers.at(mergePos) = numbers.at(leftPos);
        ++leftPos;
        ++mergePos;
    }

    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= k) {
        mergedNumbers.at(mergePos) = numbers.at(rightPos);
        ++rightPos;
        ++mergePos;
    }

    // Copy merge number back to numbers
    for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
        numbers.at(i + mergePos) = mergedNumbers.at(mergePos);
    }
}

template<typename T>
void MergeSort(vector<T> &numbers, int i, int k) {
    int j;

    if (i < k) {
        j = (i + k) / 2;  // Find the midpoint in the partition

        // Recursively sort left and right partitions
        MergeSort(numbers, i, j);
        MergeSort(numbers, j + 1, k);

        // Merge left and right partition in sorted order
        Merge(numbers, i, j, k);
    }
}

//Quick Sort (from Zybooks 15.8) - changed from array to vector
template<typename T>
int Partition(vector<T> &numbers, int i, int k) {
    int l;
    int h;
    int midpoint;
    T pivot;
    T temp;
    bool done;

    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    pivot = numbers.at(midpoint);

    done = false;
    l = i;
    h = k;

    while (!done) {

        /* Increment l while numbers[l] < pivot */
        while (numbers.at(l) < pivot) {
            ++l;
        }

        /* Decrement h while pivot < numbers[h] */
        while (pivot < numbers.at(h)) {
            --h;
        }

        /* If there are zero or one elements remaining,
         all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        }
        else {
            /* Swap numbers[l] and numbers[h],
             update l and h */
            temp = numbers.at(l);
            numbers.at(l) = numbers.at(h);
            numbers.at(h) = temp;

            ++l;
            --h;
        }
    }

    return h;
}

template<typename T>
void Quicksort(vector<T> &numbers, int i, int k) {
    int j;

    /* Base case: If there are 1 or zero elements to sort,
     partition is already sorted */
    if (i >= k) {
        return;
    }

    /* Partition the data within the array. Value j returned
     from partitioning is location of last element in low partition. */
    j = Partition(numbers, i, k);

    /* Recursively sort low partition (i to j) and
     high partition (j + 1 to k) */
    Quicksort(numbers, i, j);
    Quicksort(numbers, j + 1, k);
}

int main()
{
    ifstream inFile;
    ofstream outFile;

    vector <Data> dataV;
    vector <Data> dataV_B; //bubble sort
    vector <Data> dataV_S; //selection sort
    vector <Data> dataV_Q; //quick sort
    vector <Data> dataV_M; //merge sort
    vector<Data> datatemp; //temp for merge

    vector <int> intV;
    vector <int> intV_B; //bubble sort
    vector <int> intV_S; //selection sort
    vector <int> intV_Q; //quick sort
    vector <int> intV_M; //merge sort
    vector <int> temp;

    int length;
    cout << "Length of vector: " << endl;
    cin >> length;

    inFile.open("ks-projects-201612.csv");
    if(!inFile.is_open())
    {
        cout << "The input file didn't open" << endl;
        return -1;
    }
    cout << "The input file opened" << endl;

    int count = 0;
    while(count < length || count < 100000)
    {
        string n;
        string cat;
        string g;
        string p;
        string cn;
        getline(inFile, n, ',');
        getline(inFile, cat, ',');
        getline(inFile, g, ',');
        getline(inFile, p, ',');
        getline(inFile, cn, ',');

        double goal = stod(g);
        //double pledged = stod(p);
        Data info = Data(n, cat, goal, p, cn);
        dataV.push_back(info);
        count++;
    }

    //make all vectors identical to the norm

    dataV_B = dataV;
    dataV_M = dataV;
    dataV_Q = dataV;
    dataV_S = dataV;
    datatemp = dataV;

    for(int i = 0; i < length; i++)
    {
        int random = rand() %100;
        intV.push_back(random);
    }
    intV_B = intV;
    intV_M = intV;
    intV_Q = intV;
    intV_S = intV;
    temp = intV;

    int num = 100000; //need to change this manually for data tests

    srand(time(0));

    cout << "Random Integer Testing: " << endl << endl;

    clock_t begIntSelectionSort = clock();
    selectionSort(intV_S, intV_S.size());
    clock_t endIntSelectionSort = clock();
    double totalIntSelectionSort = double(endIntSelectionSort - begIntSelectionSort) / CLOCKS_PER_SEC;
    cout << "Time for int selection sort: " << totalIntSelectionSort << endl;

    clock_t begIntSelectionSort2 = clock();
    selectionSort(intV_S, intV_S.size());
    clock_t endIntSelectionSort2 = clock();
    double totalIntSelectionSort2 = double(endIntSelectionSort2 - begIntSelectionSort2) / CLOCKS_PER_SEC;
    cout << "Time for int selection sort 2: " << totalIntSelectionSort2 << endl;

    cout << endl;

    clock_t begIntBubbleSort = clock();
    bubbleSort(intV_B, intV_B.size());
    clock_t endIntBubbleSort = clock();
    double totalIntBubbleSort = double(endIntBubbleSort - begIntBubbleSort) / CLOCKS_PER_SEC;
    cout << "Time for int bubble sort: " << totalIntBubbleSort << endl;

    clock_t begIntBubbleSort2 = clock();
    bubbleSort(intV_B, intV_B.size());
    clock_t endIntBubbleSort2 = clock();
    double totalIntBubbleSort2 = double(endIntBubbleSort2 - begIntBubbleSort2) / CLOCKS_PER_SEC;
    cout << "Time for int bubble sort 2: " << totalIntBubbleSort2 << endl;

    cout << endl;

    clock_t begIntQuickSort = clock();
    Quicksort(intV_Q, 0, intV_Q.size() - 1);
    clock_t endIntQuickSort = clock();
    double totalIntQuickSort = double(endIntQuickSort - begIntQuickSort) / CLOCKS_PER_SEC;
    cout << "Time for int quick sort: " << totalIntQuickSort << endl;

    clock_t begIntQuickSort2 = clock();
    Quicksort(intV_Q, 0, intV_Q.size() - 1);
    clock_t endIntQuickSort2 = clock();
    double totalIntQuickSort2 = double(endIntQuickSort2 - begIntQuickSort2) / CLOCKS_PER_SEC;
    cout << "Time for int quick sort 2: " << totalIntQuickSort2 << endl;

    cout << endl;

    clock_t begIntMergeSort = clock();
    MergeSort(intV_M, 0, intV_M.size() - 1);
    clock_t endIntMergeSort = clock();
    double totalIntMergeSort = double(endIntMergeSort - begIntMergeSort) / CLOCKS_PER_SEC;
    cout << "Time for int merge sort: " << totalIntMergeSort << endl;

    clock_t begIntMergeSort2 = clock();
    MergeSort(intV_M, 0, intV_M.size() - 1);
    clock_t endIntMergeSort2 = clock();
    double totalIntMergeSort2 = double(endIntMergeSort2 - begIntMergeSort2) / CLOCKS_PER_SEC;
    cout << "Time for int merge sort 2: " << totalIntMergeSort2 << endl;

    cout << endl << "Data Testing: " << endl << endl;

    clock_t begDataSelectionSort = clock();
    selectionSort(dataV_S, /*dataV_S.size() - 1*/ num);
    clock_t endDataSelectionSort = clock();
    double totalDataSelectionSort = double(endDataSelectionSort - begDataSelectionSort) / CLOCKS_PER_SEC;
    cout << "Time for data selection sort: " << totalDataSelectionSort << endl;
    //see if selection sort even works
    //for (int i = 1; i < dataV.size() - 1; i++) {
        //assert(dataV_S.at(i - 1) <= dataV_S.at(i));
    //}

    clock_t begDataSelectionSort2 = clock();
    selectionSort(dataV_S, /*dataV_S.size() - 1*/ num);
    clock_t endDataSelectionSort2 = clock();
    double totalDataSelectionSort2 = double(endDataSelectionSort2 - begDataSelectionSort2) / CLOCKS_PER_SEC;
    cout << "Time for data selection sort 2: " << totalDataSelectionSort2 << endl;

    cout << endl;

    clock_t begDataBubbleSort = clock();
    bubbleSort(dataV_B, /*dataV_B.size() - 1*/ num);
    clock_t endDataBubbleSort = clock();
    double totalDataBubbleSort = double(endDataBubbleSort - begDataBubbleSort) / CLOCKS_PER_SEC;
    cout << "Time for data bubble sort: " << totalDataBubbleSort << endl;
    //see if bubble sort works
    //for (int i = 1; i < dataV.size() - 1; i++) {
    //    assert(dataV_B.at(i - 1) <= dataV_B.at(i));
    //}

    clock_t begDataBubbleSort2 = clock();
    bubbleSort(dataV_B, /*dataV_B.size() - 1*/ num);
    clock_t endDataBubbleSort2 = clock();
    double totalDataBubbleSort2 = double(endDataBubbleSort2 - begDataBubbleSort2) / CLOCKS_PER_SEC;
    cout << "Time for data bubble sort 2: " << totalDataBubbleSort2 << endl;

    cout << endl;

    clock_t begDataQuickSort = clock();
    Quicksort(dataV_Q, 0, /*dataV_Q.size() - 1*/ num);
    clock_t endDataQuickSort = clock();
    double totalDataQuickSort = double(endDataQuickSort - begDataQuickSort) / CLOCKS_PER_SEC;
    cout << "Time for data quick sort: " << totalDataQuickSort << endl;
    //see if quick sort works
    //for (int i = 1; i < dataV.size() - 1; i++) {
    //    assert(dataV_Q.at(i - 1) <= dataV_Q.at(i));
    //}

    clock_t begDataQuickSort2 = clock();
    Quicksort(dataV_Q, 0, /*dataV_Q.size() - 1*/ num);
    clock_t endDataQuickSort2 = clock();
    double totalDataQuickSort2 = double(endDataQuickSort2 - begDataQuickSort2) / CLOCKS_PER_SEC;
    cout << "Time for data quick sort 2: " << totalDataQuickSort2 << endl;

    cout << endl;

    clock_t begDataMergeSort = clock();
    MergeSort(dataV_M, 0, /*dataV_M.size() - 1*/ num);
    clock_t endDataMergeSort = clock();
    double totalDataMergeSort = double(endDataMergeSort - begDataMergeSort) / CLOCKS_PER_SEC;
    cout << "Time for data merge sort: " << totalDataMergeSort << endl;
    //see if merge sort works
    //for (int i = 1; i < dataV.size() - 1; i++) {
    //    assert(dataV_M.at(i - 1) <= dataV_M.at(i));
    //}

    clock_t start_mergeSort2 = clock();
    MergeSort(dataV_M, 0, /*dataV_M.size() - 1*/ num);
    clock_t end_mergeSort2 = clock();
    double elapsed_mergeSort2 = double(end_mergeSort2 - start_mergeSort2) / CLOCKS_PER_SEC;
    cout << "Time for data merge sort 2: " << elapsed_mergeSort2 << endl;

    cout << endl;

    inFile.close();
    cout << "Files closed" << endl;

    return 0;
}