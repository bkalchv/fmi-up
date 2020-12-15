#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int* toBinaryArray(int decimalTime) {

    int* binaryTimeArray = new (nothrow) int[13];

    int* binaryTimeArrayReversed = new (nothrow) int[13];

    for (unsigned int i{0}; decimalTime > 0; ++i)
    {
        binaryTimeArrayReversed[i] = decimalTime % 2;
        decimalTime = decimalTime / 2;
    }

    for (int z{12}; z >= 0; --z) 
    {  
        binaryTimeArray[z] = binaryTimeArrayReversed[12-z]; 
    }

    return binaryTimeArray;
}

void printBinaryTimeArray(int *(&binaryTimeArray)) {
    
    for (size_t i{0}; i < 13; ++i) 
    {
        cout << binaryTimeArray[i];
        if ( i == 0 || i == 6) 
        {
            cout << "|";
        }
    }

}

unsigned int calculateHours(int *(&binaryTimeArray)) {

    unsigned int result = 0;

    for (size_t i{3}; i <= 6 ; ++i) 
    {   
        if (binaryTimeArray[i] != 0) {
            result += pow(2, 6 - i);
        }
    }

    for (size_t z{1}; z <= 2; ++z) 
    {
        if (binaryTimeArray[z] != 0) 
        {
            result += 10*pow(2, 2 - z);
        }
    }

    return result;
}

unsigned int calculateMinutes(int *(&binaryTimeArray)) {

    unsigned int result = 0;

    for (size_t i{7}; i <= 12 ; ++i) 
    {   
        if (binaryTimeArray[i] != 0) {
            result += pow(2, 12 - i);
        }
    }    

    return result;
}

bool isIn24hFormat(int *(&binaryTimeArray)) {
    return binaryTimeArray[0];
}

bool isInValidFormat(int *(&binaryTimeArray)) {
    if (!isIn24hFormat(binaryTimeArray) && calculateHours(binaryTimeArray) <= 12) 
    {
        return true;
    }

    if (isIn24hFormat(binaryTimeArray) && calculateHours(binaryTimeArray) > 12)
    {
        return true;
    }

    return false;
}

void printTime(const unsigned int& hours, const unsigned int& minutes) {
    hours < 10 ? cout << "0" << hours : cout << hours; 
    cout << ":";
    minutes < 10 ? cout << "0" <<  minutes : cout <<  minutes;
}

void printExplaination(int wholeNumber, int *(&binaryTimeArray)) {
    cout << wholeNumber << " -> ";
    printBinaryTimeArray(binaryTimeArray);
    cout << " -> ";
    printTime(calculateHours(binaryTimeArray), calculateMinutes(binaryTimeArray));
    isIn24hFormat(binaryTimeArray) ? cout << endl : cout << " (12-hrs format)" << endl;
}

unsigned int calculateAbsoluteDifferenceInMinutes(const unsigned int& hours1, const unsigned int& minutes1, const unsigned int& hours2, const unsigned int& minutes2) {
    unsigned int timeInMinutes1 = hours1 * 60 + minutes1;
    unsigned int timeInMinutes2 = hours2 * 60 + minutes2;
    return abs((double) timeInMinutes1 - (double) timeInMinutes2);
}

void printAbsoluteDifference(unsigned int& absoluteDifferenceInMinutes) {
    unsigned int absoluteDifferenceHours = absoluteDifferenceInMinutes / 60;
    unsigned int absoluteDifferenceMinutes = absoluteDifferenceInMinutes % 60;
    printTime(absoluteDifferenceHours, absoluteDifferenceMinutes);
}

int main() {
    int wholeNumber1;
    int wholeNumber2;

    cin >> wholeNumber1 >> wholeNumber2;

    int* binaryTimeArray1 = toBinaryArray(wholeNumber1);
    int* binaryTimeArray2 = toBinaryArray(wholeNumber2); 

    if (isInValidFormat(binaryTimeArray1) && isInValidFormat(binaryTimeArray2))
    {   
        unsigned int hours1     = calculateHours(binaryTimeArray1);
        unsigned int minutes1   = calculateMinutes(binaryTimeArray1);
        unsigned int hours2     = calculateHours(binaryTimeArray2);
        unsigned int minutes2   = calculateMinutes(binaryTimeArray2);
        printTime(hours1, minutes1);
        cout << endl;
        printTime(hours2, minutes2);
        cout << endl;
        unsigned int absoluteDifferenceInMinutes = calculateAbsoluteDifferenceInMinutes(hours1, minutes1, hours2, minutes2);
        cout << "diff: ";
        printAbsoluteDifference(absoluteDifferenceInMinutes);
        cout << endl;
    }
    else 
    {
        cout << "invalid format" << endl;
        cout << "Do you want to see why? (y/n)" << endl;
        char answer;
        cin >> answer;
        if (answer == 'y')
        {
            if (!isInValidFormat(binaryTimeArray1)) 
            {
                printExplaination(wholeNumber1, binaryTimeArray1);
            }
            
            if (!isInValidFormat(binaryTimeArray2))
            {
                printExplaination(wholeNumber2, binaryTimeArray2);
            }
        }
    }
 

    delete[] binaryTimeArray1;
    delete[] binaryTimeArray2;
}