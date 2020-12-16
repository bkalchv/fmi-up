// Да се напише програма, която прочита от стандартния вход две точки във времето във формат 
// dd.mm.yyyy HH:MM:SS (незадължително с водещи нули) и извежда на стандартния изход един ред, съдържащ тяхната разлика
// във формат [days-]HH:MM:SS - ако броят дни е 0, то той да не се извежда и HH, MM, SS са задължително с водещи нули.
// Ако някоя от въведените точки във времето не е валидна, програмата да изведе един ред със съобщение „Invalid date/time“.

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

string* stringToArrayOfTokens(string str) {

    char delimiter;

    if (str.find('.') != std::string::npos)
    {
        delimiter = '.';
    }

    if (str.find(':') != string::npos)
    {
        delimiter = ':';
    }

    string* result = new string[3];

    size_t pos = str.find(delimiter);

    if (pos != string::npos)
    {
        for (size_t idx{0}; pos != string::npos && idx < 2; pos = str.find(delimiter), ++idx) 
        {
            string token;
            token = str.substr(0, pos);
            result[idx] = token;
            str.erase(0, pos + 1);
        }
    }
    result[2] = str; // last token

    return result;
}

unsigned int* TokensToUnsignedInts(string* (&vectorOfTokens)) {

    unsigned int* result = new unsigned int[3];

    for (size_t i{0}; i < 3; ++i) 
    {   
        string temp = vectorOfTokens[i];
        result[i] = stoul(temp);
    }

    return result;
}

bool isLeapYear(const unsigned int& year) {

    if ( year % 400 == 0 || (year % 4 == 0 && year % 100 != 0) ) 
    {
        return true;
    }

    return false;
}

bool isEven(const unsigned int& month) {
    return month % 2 == 0;
}

bool isValidDate(const unsigned int& date, const unsigned int& month, const unsigned int& year) {

    if (date > 31 || date <= 0) 
    {
        //throw std::invalid_argument("Date can't be bigger than 31. Invalid date input!");
        return false;
    }

    if (month > 12 || month <= 0)
    {
        //throw std::invalid_argument("Months can't be bigger than 12 or lesser than/ equal to 0. Invalid month input!");
        return false;
    }

    if (year > 9999 || year < 0)
    {
        //throw std::invalid_argument("Year should be between 0 and 9999. Invalid year input!");
        return false;
    }

    if (isLeapYear(year) && month == 2 && date > 29)
    {
        //throw std::invalid_argument("In an leap year, february has 29 days. Invalid date input!");
        return false;
    }

    if (!isLeapYear(year) && month == 2 && date > 28)
    {
        //throw std::invalid_argument("February has 28 days. Invalid date input!");
        return false;
    }

    if (month <= 6 && isEven(month) && date > 30)
    {   
        return false;
    }


    if (month > 6 && !isEven(month) && date > 30) 
    {
        return false;
    }

    return true;
}

bool isValidTime(const unsigned int& hours, const unsigned int& minutes, const unsigned int& seconds) {

    if (hours < 0 || hours > 23) 
    {
        return false;
    }

    if (minutes < 0 || minutes > 60)
    {
        return false;
    }

    if (seconds < 0 || seconds > 60) 
    {
        return false;
    }

    return true;
}

unsigned int*& getLaterDate(unsigned int* (&date1), unsigned int* (&date2)) {

    for (size_t i{3}; i > 0; --i) {
        
        if (date1[i-1] == date2[i-1]) {
            continue;
        }

        if (date1[i-1] > date2[i-1]) 
        {
            return date1;
        }
        else
        {
            return date2;
        }
        
    }

    return date1;
}

unsigned int calculateAbsoluteDateDifferenceInDays(const unsigned int& date1, const unsigned int& month1, const unsigned int& year1, const unsigned int& date2, const unsigned int& month2, const unsigned int& year2) {
    
    unsigned int laterYear = year1;

    unsigned int absoluteDateDifferenceInDays = 0;

    if (year1 != year2) 
    {
        while (laterYear > year2 + 1)
        {   
            if (isLeapYear(laterYear)) 
            {
                absoluteDateDifferenceInDays += 1;
            }
            absoluteDateDifferenceInDays += 365;
            --laterYear;
        }
    }

    int laterMonth = month1;

    while (laterMonth > month2 + 1 || laterYear != year2)
    {   

        if (laterMonth == 0)
        {   
            --laterYear;
            laterMonth = 12;
        }

        if (isEven(laterMonth) && laterMonth <= 7)
        {    
            if (laterMonth == 2) 
            {
                absoluteDateDifferenceInDays += 28;
                if (isLeapYear(laterYear)) {
                    absoluteDateDifferenceInDays += 1;
                }
            }
            else
            {
                absoluteDateDifferenceInDays += 30;
            }
        }

        if (!isEven(laterMonth) && laterMonth <= 7) 
        {
            absoluteDateDifferenceInDays +=  31;
        }

        if (isEven(laterMonth) && laterMonth > 7) 
        {
            absoluteDateDifferenceInDays += 31;
        }

        if (!isEven(laterMonth) && laterMonth > 7) 
        {
            absoluteDateDifferenceInDays += 30;
        }

        --laterMonth;
    }

      
    int laterDate = date1;

    while (laterDate > date2 || laterMonth != month2)
    {   
        if (laterDate == 0) 
        {
            if (isEven(laterMonth) && laterMonth <= 7)
            {    
                if (laterMonth == 2) 
                {
                    laterDate = 28;
                    if (isLeapYear(laterYear)) {
                        laterDate += 1;
                    }
                }
                else
                {
                    laterDate = 30;
                }
            }

            if (!isEven(laterMonth) && laterMonth <= 7) 
            {
                laterDate =  31;
            }

            if (isEven(laterMonth) && laterMonth > 7) 
            {
                laterDate = 31;
            }

            if (!isEven(laterMonth) && laterMonth > 7) 
            {
                laterDate = 30;
            }

            --laterMonth;
        }

        ++absoluteDateDifferenceInDays;

        --laterDate;
    }

    return absoluteDateDifferenceInDays;
}

unsigned int calculateAbsoluteTimeDifferenceInSeconds(const unsigned int& hours1, const unsigned int& minutes1, const unsigned int seconds1, const unsigned int& hours2, const unsigned int& minutes2, const unsigned int& seconds2) {
    int timeInSeconds1 = 60 * (hours1 * 60 + minutes1) + seconds1;
    int timeInSeconds2 = 60 * (hours2 * 60 + minutes2) + seconds2;

    if (timeInSeconds1 - timeInSeconds2 < 0) 
    {
        return (24*60*60) - abs((double) timeInSeconds1 - (double) timeInSeconds2);
    }

    return timeInSeconds1 - timeInSeconds2;
}

void printTime(const unsigned int& hours, const unsigned int& minutes, const unsigned& seconds) {
    hours < 10 ? cout << "0" << hours : cout << hours; 
    cout << ":";
    minutes < 10 ? cout << "0" <<  minutes : cout <<  minutes;
    cout << ":";
    seconds < 10 ? cout << "0" <<  seconds : cout <<  seconds;
}

void printAbsoluteDifference(const unsigned int& absoluteDifferenceInSeconds) {
    unsigned int absoluteDifferenceHours    = (absoluteDifferenceInSeconds / 60) / 60;
    unsigned int absoluteDifferenceMinutes  = absoluteDifferenceInSeconds / 60;
    unsigned int absoluteDifferenceSeconds  = absoluteDifferenceInSeconds % 60;

    printTime(absoluteDifferenceHours, absoluteDifferenceMinutes, absoluteDifferenceSeconds);
}

int main() {

    string inputDate1;
    string inputTime1;
    cin >> inputDate1 >> inputTime1;

    string inputDate2;
    string inputTime2;
    cin >> inputDate2 >> inputTime2;
    
    string* tokenizedDate1          = stringToArrayOfTokens(inputDate1);
    unsigned int* dataDate1         = TokensToUnsignedInts(tokenizedDate1);
    string* tokenizedTime1          = stringToArrayOfTokens(inputTime1);
    unsigned int* dataTime1         = TokensToUnsignedInts(tokenizedTime1);

    string* tokenizedDate2          = stringToArrayOfTokens(inputDate2);
    unsigned int* dataDate2         = TokensToUnsignedInts(tokenizedDate2);
    string* tokenizedTime2          = stringToArrayOfTokens(inputTime2);
    unsigned int* dataTime2         = TokensToUnsignedInts(tokenizedTime2);

    if (getLaterDate(dataDate1, dataDate2) == dataDate2) 
    {
        swap(dataDate1, dataDate2);
        swap(dataTime1, dataTime2);
    }

    unsigned int date1Date      = dataDate1[0];
    unsigned int date1Month     = dataDate1[1];
    unsigned int date1Year      = dataDate1[2];
    unsigned int time1Hours     = dataTime1[0];
    unsigned int time1Minutes   = dataTime1[1];
    unsigned int time1Seconds   = dataTime1[2];

    unsigned int date2Date      = dataDate2[0];
    unsigned int date2Month     = dataDate2[1];
    unsigned int date2Year      = dataDate2[2];
    unsigned int time2Hours     = dataTime2[0];
    unsigned int time2Minutes   = dataTime2[1];
    unsigned int time2Seconds   = dataTime2[2];


    bool isValidInput1 = isValidDate(date1Date, date1Month, date1Year) && isValidTime(time1Hours, time1Minutes, time1Seconds);
    bool isValidInput2 = isValidDate(date2Date, date2Month, date2Year) && isValidTime(time2Hours, time2Minutes, time2Seconds);

    if (isValidInput1 && isValidInput2) 
    {   
        unsigned int absoluteDateDifferenceInDays = calculateAbsoluteDateDifferenceInDays(date1Date, date1Month, date1Year, date2Date, date2Month, date2Year);

        unsigned int absoluteTimeDifferenceInSeconds = calculateAbsoluteTimeDifferenceInSeconds(time1Hours, time1Minutes, time1Seconds, time2Hours, time2Minutes, time2Seconds);

        if (absoluteDateDifferenceInDays != 0) 
        {
        cout << absoluteDateDifferenceInDays << "-";
        }

        printAbsoluteDifference(absoluteTimeDifferenceInSeconds);
        cout << endl;
    }
    else
    {
        cout << "Invalid date/time" << endl;
    }
    
    delete[] tokenizedDate1;
    delete[] dataDate1;
    delete[] tokenizedDate2;
    delete[] dataDate2;

    return 0;
}