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

using namespace std;

const unsigned int INPUT_DATA_BITS_LENGTH           = 13;
const unsigned int HOURS_FIRST_DIGIT_BIT_POSITION   = 10;
const unsigned int HOURS_FIRST_DIGIT_BITS_LENGTH    = 2;
const unsigned int HOURS_SECOND_DIGIT_BIT_POSITION  = 6;
const unsigned int HOURS_SECOND_DIGIT_BITS_LENGTH   = 4;
const unsigned int MINUTES_BITS_LENGTH              = 6;
const unsigned int MINUTES_BITS_POSITION            = 0;

bool isIn24hFormat(unsigned int wholeNumber) {
    return (wholeNumber >> (INPUT_DATA_BITS_LENGTH - 1));
}

unsigned int wholeNumberToHours(unsigned int wholeNumber) {
    
    unsigned int decimalHours, hoursFirstDigit,hoursSecondDigit;

    hoursFirstDigit    = ((1 << HOURS_FIRST_DIGIT_BITS_LENGTH ) - 1) & (wholeNumber >> (HOURS_FIRST_DIGIT_BIT_POSITION));

    hoursSecondDigit   = ((1 << HOURS_SECOND_DIGIT_BITS_LENGTH ) - 1) & (wholeNumber >> (HOURS_SECOND_DIGIT_BIT_POSITION));

    decimalHours = hoursFirstDigit * 10 + hoursSecondDigit;

    return decimalHours;
}

bool isInValidFormat(unsigned int wholeNumber) {

    if (!isIn24hFormat(wholeNumber) && wholeNumberToHours(wholeNumber) <= 12) 
    {
        return true;
    }

    if (isIn24hFormat(wholeNumber) && wholeNumberToHours(wholeNumber) > 12)
    {
        return true;
    }

    return false;
}

unsigned int wholeNumberToMinutes(unsigned int wholeNumber) {

    unsigned int decimalMinutes;

    decimalMinutes = ((1 << MINUTES_BITS_LENGTH) - 1) & (wholeNumber >> (MINUTES_BITS_POSITION));

    return decimalMinutes;
}

unsigned int calculateAbsoluteDifferenceInMinutes(unsigned int wholeNumber1, unsigned int wholeNumber2) {
    unsigned int time1InMinutes = (wholeNumberToHours(wholeNumber1) * 60 + wholeNumberToMinutes(wholeNumber1));
    unsigned int time2InMinutes = (wholeNumberToHours(wholeNumber2) * 60 + wholeNumberToMinutes(wholeNumber2)); 
    return abs((int) time1InMinutes - (int) time2InMinutes);
}

void printTime(unsigned int wholeNumber) {

    unsigned int timeHours      = wholeNumberToHours(wholeNumber);
    unsigned int timeMinutes    = wholeNumberToMinutes(wholeNumber);

    if (timeHours < 10) 
    {
        cout << "0";
    }
    cout << timeHours << ":";

    if (timeMinutes < 10) 
    {
        cout << "0";
    }
    cout << timeMinutes << endl;
}

void printDifference(unsigned int wholeNumber1, unsigned int wholeNumber2) {
    unsigned int absoluteDifferenceInMinutes    = calculateAbsoluteDifferenceInMinutes(wholeNumber1, wholeNumber2);
    unsigned int absoluteDifferenceHours        = absoluteDifferenceInMinutes / 60;
    unsigned int absoluteDifferenceMinutes      = absoluteDifferenceInMinutes % 60;

    cout << "diff: " << absoluteDifferenceHours << ":";
    if (absoluteDifferenceMinutes < 10) 
    {
        cout << "0";
    }
    cout << absoluteDifferenceMinutes << endl;
}

int main() {

    unsigned int wholeNumber1;
    unsigned int wholeNumber2;

    cin >> wholeNumber1 >> wholeNumber2;

    if (isInValidFormat(wholeNumber1) && isInValidFormat(wholeNumber2)) 
    {
        printTime(wholeNumber1);
        printTime(wholeNumber2);
        printDifference(wholeNumber1, wholeNumber2);
    }
    else 
    {
        cout << "invalid format";
    }

    return 0;
}