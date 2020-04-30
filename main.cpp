///                                                                     This was built on Clion using the C++14 standard
///                                                                     for project 6, CS 321.
#include <iostream>
#include <algorithm>
#include <random>
#include <time.h>
#include <fstream>
#include <stack>
#include <vector> //for testing purposes
using namespace std;


//Original code, from the book.
template<class T>
void quicksortOriginal (T *data, int first, int last) {
    int lower = first+1, upper = last;
    swap(data[first],data[(first+last)/2]);
    T bound = data[first];
    ///this runs by the following process until the two pointers pass each other. Lower on the top, Upper on the bottom.
    while ( lower <= upper ) {
        while (bound > data[lower])///these keep on moving until they find a value on the wrong side of the pivot.
            lower++;
        while (bound < data[upper])///these keep on moving until they find a value on the wrong side of the pivot.
            upper--;
        if (lower < upper)///swaps the two values
            swap(data[lower++], data[upper--]);
        else lower++;
    }
    swap(data[upper], data[first]);
    if (first < (upper - 1))///recursive call on the first half of the array
        quicksortOriginal(data, first, upper - 1);
    if ((upper + 1) < last)///recursive call on the last half of the array
        quicksortOriginal(data, upper + 1, last);
};

//Quicksort (Original variant) overload.
template<class T>
void quicksortOriginal(T *data, int n){
    int i, max;
    if (n < 2)
        return;
    for (i = 1, max = 0; i < n; i++) {
        if (data[max] < data[i])
            max = i;
    }

    swap(data[n-1],data[max]);
    quicksortOriginal(data, 0, n - 2);
}

//Quicksort (median pivot variant) overload.
template<class T>
void quicksortRandomPivot(T *data, int n){
    int i, max;
    if (n < 2)
        return;
    for (i = 1, max = 0; i < n; i++) {
        if (data[max] < data[i])
            max = i;
    }

    swap(data[n-1],data[max]);
    quicksortRandomPivot(data, 0, n - 2);
}

//Quicksort, but with a Random Pivot
template<class T>
void quicksortRandomPivot (T *data, int first, int last) {
    ///random generation block
    random_device seed;
    int pivot = rand() % (last - first) + first; ///Needed geeks for geeks - Forgot I needed to readd first to the pivot
    int lower = first+1, upper = last;
    swap(data[first],data[pivot]);
    T bound = data[first];
    ///this runs by the following process until the two pointers pass each other. Lower on the top, Upper on the bottom.
    while ( lower <= upper ) {
        while (bound > data[lower])///these keep on moving until they find a value on the wrong side of the pivot.
            lower++;
        while (bound < data[upper])///these keep on moving until they find a value on the wrong side of the pivot.
            upper--;
        if (lower < upper)///swaps the two values
            swap(data[lower++], data[upper--]);
        else lower++;
    }
    swap(data[upper], data[first]);
    if (first < (upper - 1))///recursive call on the first half of the array
        quicksortRandomPivot(data, first, upper - 1);
    if ((upper + 1) < last)///recursive call on the last half of the array
        quicksortRandomPivot(data, upper + 1, last);
};

//Quicksort, but with a Median Pivot
template<class T>
void quicksortMedianPivot (T *data, int first, int last) {
    int lower = first+1, upper = last;
    ///Major difference. We use a function to determine the median, then pass that to the swap.
    int pivot = medianFinder(first, ((first+last)/2), last);
    swap(data[first],data[pivot]);
    T bound = data[first];
    ///this runs by the following process until the two pointers pass each other. Lower on the top, Upper on the bottom.
    while ( lower <= upper ) {
        while (bound > data[lower])///these keep on moving until they find a value on the wrong side of the pivot.
            lower++;
        while (bound < data[upper])///these keep on moving until they find a value on the wrong side of the pivot.
            upper--;
        if (lower < upper)///swaps the two values
            swap(data[lower++], data[upper--]);
        else lower++;
    }
    swap(data[upper], data[first]);
    if (first < (upper - 1))///recursive call on the first half of the array
        quicksortMedianPivot(data, first, upper - 1);
    if ((upper + 1) < last)///recursive call on the last half of the array
        quicksortMedianPivot(data, upper + 1, last);
};

//Quicksort (median pivot variant) overload.
template<class T>
void quicksortMedianPivot(T *data, int n){
    int i, max;
    if (n < 2)
        return;
    for (i = 1, max = 0; i < n; i++) {
        if (data[max] < data[i])
            max = i;
    }

    swap(data[n-1],data[max]);
    quicksortMedianPivot(data, 0, n - 2);
}

//First variant of shellsort. Stopping condition h(t) for which h(t+2) >= n.
template<class T>
void shellSortFirstVariant(T data[], int n){

    register int i, j, hCnt, h;
    int increments[20], k;

    //create an appropriate number of increments h
    for (h = 1, i = 0; h < n; i++){
    increments[i] = h;
    if ((h * 9 + 4) >= n)
        break;
    h = 3*h + 1;
    }

    //cout << "This algorithm has " << i << " increments\n";

    //Loop on the number of different increments h
    for (i--; i >= 0; i--){
        h = increments[i];

        //loop on the number of subarrays h-sorted in ith pass
        for (hCnt = h; hCnt < 2*h; hCnt++) {
        //insertion sort for subarray containing every hth element of array data
        for (j = hCnt; j < n; ) {//array data
            T tmp = data[j];
            k = j;
            while (k-h >= 0 && tmp < data[k-h]) {
                data[k] = data[k-h];
                k -= h;
                }
                data[k] = tmp;
                j += h;
            }
        }
    }
}

//Second variant of shellsort. Stopping condition (2^k - 1) > n
template<class T>
void shellSortSecondVariant(T data[], int n){
    register int i, j, hCnt, h;
    int increments[20], k;

    //create an appropriate number of increments h
    for (h = 1, i = 0; h < n; i++){
        increments[i] = h;
        h = pow(2, (i + 1)) - 1;
        if ( h > n )
            break;
    }
   // cout << "This algorithm has " << i << " increments\n";

    //Loop on the number of different increments h
    for (i--; i >= 0; i--){
        h = increments[i];
        //loop on the number of subarrays h-sorted in ith pass
        for (hCnt = h; hCnt < 2*h; hCnt++) {
            //insertion sort for subarray containing every hth element of array data
            for (j = hCnt; j < n; ) {//array data
                T tmp = data[j];
                k = j;
                while (k-h >= 0 && tmp < data[k-h]) {
                    data[k] = data[k-h];
                    k -= h;
                }
                data[k] = tmp;
                j += h;
            }
        }
    }
}

///                                                                        Third variant of shellsort. Stopping
///                                                                        condition (2^k + 1) > n
template<class T>
void shellSortThirdVariant(T data[], int n){
    register int i, j, hCnt, h;
    int increments[20], k;

    //create an appropriate number of increments h
    for (h = 1, i = 0; h < n; i++){
        increments[i] = h;
        h = pow(2, (i + 1)) + 1;
        if ( h > n )
            break;
    }
    //cout << "This algorithm has " << i << " increments\n";

    //Loop on the number of different increments h
    for (i--; i >= 0; i--){
        h = increments[i];
        //loop on the number of subarrays h-sorted in ith pass
        for (hCnt = h; hCnt < 2*h; hCnt++) {
            //insertion sort for subarray containing every hth element of array data
            for (j = hCnt; j < n; ) {//array data
                T tmp = data[j];
                k = j;
                while (k-h >= 0 && tmp < data[k-h]) {
                    data[k] = data[k-h];
                    k -= h;
                }
                data[k] = tmp;
                j += h;
            }
        }
    }
}

///                                                                        Fourth variant of shellsort. Stopping
///                                                                        condition F(n) < n, where F = fibbonaci num.
template<class T>
void shellSortFourthVariant(T data[], int n){
    register int i, j, hCnt, h;
    int increments[28], k;
    increments[0] = 0;
    increments[1] = 1;
    //create an appropriate number of increments h
    for (h = 1, i = 2; h < n; i++){
        increments[i] = h;
        h = increments[i] + increments[i-1];
        if ( h > n )
            break;
    }
    //cout << "This algorithm has " << i << " increments\n";

    //Loop on the number of different increments h
    for (i--; i >= 0; i--){
        h = increments[i];
        //loop on the number of subarrays h-sorted in ith pass
        for (hCnt = h; hCnt < 2*h; hCnt++) {
            //insertion sort for subarray containing every hth element of array data
            for (j = hCnt; j < n; ) {//array data
                T tmp = data[j];
                k = j;
                while (k-h >= 0 && tmp < data[k-h]) {
                    data[k] = data[k-h];
                    k -= h;
                }
                data[k] = tmp;
                j += h;
            }
        }
    }
}

///                                                                        Fifth variant of shellsort. Stopping
///                                                                        condition (h = 1)
template<class T>
void shellSortFifthVariant(T data[], int n){
    std::stack<int> reversiStack;
    register int i, j, hCnt, h;
    int increments[40] = {0};
    int k;


    //create an appropriate number of increments h
    for (h =  n / 2, i = 0; h > 0; i++){
        increments[i] = h;
        reversiStack.push(h);
        h = floor(0.75 * increments[i]);
    }

    int counter = 0;
    for (int z = 0; z < 40; z++) {
        if (increments[z] != 0)
            counter++;
    }
    for (int timer = 0; timer < counter; timer++) {
        increments[timer] = reversiStack.top();
        reversiStack.pop();
        if (reversiStack.empty())
            break;
    }

    //Loop on the number of different increments h
    for (i--; i >= 0; i--){
        h = increments[i];
        //loop on the number of subarrays h-sorted in ith pass
        for (hCnt = h; hCnt < 2*h; hCnt++) {
            //insertion sort for subarray containing every hth element of array data
            for (j = hCnt; j < n; ) {//array data
                T tmp = data[j];
                k = j;
                while (k-h >= 0 && tmp < data[k-h]) {
                    data[k] = data[k-h];
                    k -= h;
                }
                data[k] = tmp;
                j += h;
            }
        }
    }

}

///                                                                        Function to return the median of the three.
///                                                                        Contested medians default to the closest to
///                                                                        the front. Outright medians are handled last.
int medianFinder(int first, int middle, int last){
        ///Contested median, 1st case. Returns the closest variable.
        if (middle == first)
            return first;

        ///Contested median, 2nd case. Returns the closest variable.
        if (middle == last)
            return middle;

        ///Contested median, 3rd case. Returns the closest variable.
        if (first == last)
            return first;

    /// Case = first is uncontested median.
    if ((middle < first) && (first < last))
        return first;

    if ((middle > first) && (first > last))
        return first;

    /// Case = middle is uncontested median.
        if ((first < middle) && (middle < last))
            return middle;

        if ((first > middle) && (middle > last))
            return middle;

    /// Case = last is uncontested median.
        if ((middle < last) && (last < first))
            return last;

        if ((middle > last) && (last > first))
            return last;

        return 0;
    }



int main() {



    ///For demonstration that yes, the algorithms do work.
    ofstream file;

    ofstream outputFile;
    ///For actual file output - a .csv that can be imported into excel.

///                                                                                      Random number generation block.
    random_device seed;
    mt19937 number(seed());
    uniform_int_distribution<int> variance(1, 500000);


///                                                                             <start> block for quicksorts.
    /*
    ///Testing arrays
    int testingIntArrayOriginalSort[20];
    int testingIntArrayRandomPivot[20];
    int testingIntArrayMedianPivot[20];
    int testingArrayUnsortedCopy[20];

    ///Production arrays - we use these for sorting.
    ///You only need to change these - change all three, since variably sized arrays weren't working in Clion?
    int productionArraySize = 5000;
    static int intArrayOriginal[5000];
    int intArraySortingCopy[5000];


    ///Loop variable to indicate how much tests we're doing.
    int testCount = 1000;

    ///Output Arrays - size should match variable (testCount);
    int originalSortExport[1000];
    int medianPivotExport[1000];
    int randomPivotExport[1000];




///                                                                                            Building the test arrays.
    for (int i = 0; i < 20; i++) {
        testingArrayUnsortedCopy[i] = testingIntArrayRandomPivot[i] = testingIntArrayOriginalSort[i] =
        testingIntArrayMedianPivot[i] = variance(seed);
    }


    quicksortOriginal(testingIntArrayOriginalSort, 20);

    quicksortRandomPivot(testingIntArrayRandomPivot, 20);

    quicksortMedianPivot(testingIntArrayMedianPivot, 20);


///                                                                                 Creating an output file for manually
///                                                                                 checking the results.
    file.open("quicksortTestingArray.csv");
    file << "Index,UnsortedArray, Original Sort, Random Pivot, Median Pivot\n";
    for (int i = 0; i < 20; i++) {
        file << i << "," << testingArrayUnsortedCopy[i] << "," << testingIntArrayOriginalSort[i] << "," <<
             testingIntArrayRandomPivot[i] << "," << testingIntArrayMedianPivot[i] << endl;
    }
    file.close();
    cout << endl << endl;
    cout << "The three variants of Algorithms have been ran on a test array of 20 integers.\n";
    cout << "A file named quicksortTestingArray.csv has been created with the arrays printed horizontally.\n";
    cout << "Please check the data at your convenience.\n";

    cout << endl << endl << endl;


    //clocks - the time needed to sort will be the difference between the end and the start.
    clock_t randomPivotStart, randomPivotEnd, originalStart, originalEnd, medianStart, medianEnd;





    ///Loop for repeating the experiments. Change the second argument to control the amount of tests to run.
    ///See line (264) for output options.
    for (int timer = 0; timer < testCount; timer++) {

        //filling the arrays.
        for (int i = 0; i < productionArraySize; i++) {
            intArrayOriginal[i] = intArraySortingCopy[i] = variance(seed);
        }



        //Sorts the copy with the random pivot variant.
        randomPivotStart = clock();
        quicksortRandomPivot(intArraySortingCopy, productionArraySize);
        randomPivotEnd = clock();

        for (int i = 0; i < productionArraySize; i++)
            intArraySortingCopy[i] = intArrayOriginal[i];

        originalStart = clock();
        quicksortOriginal(intArraySortingCopy, productionArraySize);
        originalEnd = clock();

        for (int i = 0; i < productionArraySize; i++)
            intArraySortingCopy[i] = intArrayOriginal[i];

        medianStart = clock();
        quicksortMedianPivot(intArraySortingCopy, productionArraySize);
        medianEnd = clock();



        ///Uncomment this block to have results printed to the screen. O

        // << "The original sort took " << originalEnd - originalStart << " milliseconds to sort.\n";

        //cout << "The random pivot sort took " << randomPivotEnd - randomPivotStart << " milliseconds to sort.\n";

       // cout << "The median pivot sort took " << medianEnd - medianStart << " milliseconds to sort.\n";

        //cout << endl;


        originalSortExport[timer] = originalEnd - originalStart;
        randomPivotExport[timer]= randomPivotEnd - randomPivotStart;
        medianPivotExport[timer] = medianEnd - medianStart;



    }

    outputFile.open("outfile.csv");
    outputFile << "This data is for arrays of size " << productionArraySize << endl;
    outputFile << "Test Number,OriginalSortTime,RandomPivotSortTime,MedianPivotSortTime" << endl;
    for (int i = 0; i < testCount; i++){
        outputFile << i << "," << originalSortExport[i] << "," << randomPivotExport[i] << "," << medianPivotExport[i] <<
        endl;
    }
    outputFile.close();

    cout << "Results for the sort times have been placed in your folder in a file named outfile.csv.\n";
*/
///                                                                             <end> block for quicksorts.


    //Control block - array size for production tests.
    //To modify data size, simply change the numbers on lines 522, 523, and 524.
    int arraySize = 5000;
    static int testArrayMasterCopy[5000];
    int testArraySortableCopy[5000];

    clock_t start, end;


for (int chicken = 0; chicken < 5; chicken++) {
    for (int i = 0; i < arraySize; i++)
        testArraySortableCopy[i] = testArrayMasterCopy[i] = variance(seed);

    start = clock();
    shellSortFirstVariant(testArraySortableCopy, arraySize);
    end = clock();
    cout << "The first sort took " << end - start << " milliseconds.\n";

    for (int x = 0; x < arraySize; x++)
        testArraySortableCopy[x] = testArrayMasterCopy[x];

    start = clock();
    shellSortSecondVariant(testArraySortableCopy, arraySize);
    end = clock();
    cout << "The second sort took " << end - start << " milliseconds.\n";


    for (int x = 0; x < arraySize; x++)
        testArraySortableCopy[x] = testArrayMasterCopy[x];

    start = clock();
    shellSortThirdVariant(testArraySortableCopy, arraySize);
    end = clock();
    cout << "The third sort took " << end - start << " milliseconds.\n";


    for (int x = 0; x < arraySize; x++)
        testArraySortableCopy[x] = testArrayMasterCopy[x];

    start = clock();
    shellSortFourthVariant(testArraySortableCopy, arraySize);
    end = clock();
    cout << "The fourth sort took " << end - start << " milliseconds.\n";

    for (int x = 0; x < arraySize; x++)
        testArraySortableCopy[x] = testArrayMasterCopy[x];

    start = clock();
    shellSortFifthVariant(testArraySortableCopy, arraySize);
    end = clock();
    cout << "The fifth sort took " << end - start << " milliseconds.\n";
    cout << endl;

}
    return 0;
}