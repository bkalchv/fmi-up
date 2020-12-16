// Напишете програма, която прочита от стандартния вход две цели числа, всяко от които представлява часово време в двоичен формат (Binary clock).
// За улеснение ще считаме, че последните 6 бита на всяко от числата ще показват стойността на минутите (битове от 0 до 5). 
// Битовете от 6 до 11 - представят часовете. За разлика от минутите, часът се пресмята, по следната схема: 
// стойността, записана в 6, 7, 8 и 9 бит кодира втората цифра от часа, а 10 и 11 бит - първата.
// При стойност "1" на 12-ти бит, ще считаме времето в 24 часов формат, а при "0" - в 12 часов.
// След като е валидирано, пресметнато и отпечатано времето, ще трябва да се намери също и абсолютната разлика
// между тези две времена в часове и минути.
// За часовете в 12 часов формат приемете, че са час преди обяд (AM). 
// При невалидно време и/или формат изведете подходящо съобщение.

#include <iostream>
#include <cmath>

using namespace std;

const unsigned int INPUT_DATA_BITS_LENGTH           = 13;
const unsigned int INPUT_DATA_BITS_LAST_IDX         = 12;
const unsigned int HOURS_FIRST_DIGIT_BIT_IDX        = 1;
const unsigned int HOURS_FIRST_DIGIT_BIT_LAST_IDX   = 2;
const unsigned int HOURS_SECOND_DIGIT_BIT_IDX       = 3;
const unsigned int HOURS_SECOND_DIGIT_BIT_LAST_IDX  = 6;
const unsigned int MINUTES_BITS_IDX                 = 7;
const unsigned int MINUTES_BITS_LAST_IDX            = 12;

int* toBinaryArray(int decimalTime) {

    int* binaryTimeArray = new (nothrow) int[INPUT_DATA_BITS_LENGTH];

    int* binaryTimeArrayReversed = new (nothrow) int[INPUT_DATA_BITS_LENGTH];

    for (unsigned int i{0}; decimalTime > 0; ++i)
    {
        binaryTimeArrayReversed[i] = decimalTime % 2;
        decimalTime = decimalTime / 2;
    }

    for (int z{INPUT_DATA_BITS_LAST_IDX}; z >= 0; --z) 
    {  
        binaryTimeArray[z] = binaryTimeArrayReversed[INPUT_DATA_BITS_LAST_IDX-z]; 
    }

    return binaryTimeArray;
}

void printBinaryTimeArray(int *(&binaryTimeArray)) {
    
    for (size_t i{0}; i < INPUT_DATA_BITS_LENGTH; ++i) 
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

    for (size_t i{HOURS_SECOND_DIGIT_BIT_IDX}; i <= HOURS_SECOND_DIGIT_BIT_LAST_IDX; ++i) 
    {   
        if (binaryTimeArray[i] != 0) {
            result += pow(2, HOURS_SECOND_DIGIT_BIT_LAST_IDX - i);
        }
    }

    for (size_t z{HOURS_FIRST_DIGIT_BIT_IDX}; z <= HOURS_FIRST_DIGIT_BIT_LAST_IDX; ++z) 
    {
        if (binaryTimeArray[z] != 0) 
        {
            result += 10*pow(2, HOURS_FIRST_DIGIT_BIT_LAST_IDX - z);
        }
    }

    return result;
}

unsigned int calculateMinutes(int *(&binaryTimeArray)) {

    unsigned int result = 0;

    for (size_t i{MINUTES_BITS_IDX}; i <= MINUTES_BITS_LAST_IDX ; ++i) 
    {   
        if (binaryTimeArray[i] != 0) {
            result += pow(2, MINUTES_BITS_LAST_IDX - i);
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

void printTimeDifference(const unsigned int& hours, const unsigned int& minutes) {
    cout << "diff: " << hours << ":";
    minutes < 10 ? cout << "0" <<  minutes : cout <<  minutes;
    cout << endl;
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
    return abs((int) timeInMinutes1 - (int) timeInMinutes2);
}

void printAbsoluteDifference(unsigned int& absoluteDifferenceInMinutes) {
    unsigned int absoluteDifferenceHours = absoluteDifferenceInMinutes / 60;
    unsigned int absoluteDifferenceMinutes = absoluteDifferenceInMinutes % 60;
    printTimeDifference(absoluteDifferenceHours, absoluteDifferenceMinutes);
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
        printAbsoluteDifference(absoluteDifferenceInMinutes);
    }
    else 
    {
        cout << "invalid format" << endl;
        // cout << "Do you want to see why? (y/n)" << endl;
        // char answer;
        // cin >> answer;
        // if (answer == 'y')
        // {
        //     if (!isInValidFormat(binaryTimeArray1)) 
        //     {
        //         printExplaination(wholeNumber1, binaryTimeArray1);
        //     }
            
        //     if (!isInValidFormat(binaryTimeArray2))
        //     {
        //         printExplaination(wholeNumber2, binaryTimeArray2);
        //     }
        // }
    }
 
    delete[] binaryTimeArray1;
    delete[] binaryTimeArray2;
}