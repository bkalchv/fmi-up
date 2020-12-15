#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

vector<string> stringToVectorOfTokens(string str) {

    char delimiter;

    if (str.find('.') != std::string::npos)
    {
        delimiter = '.';
    }

    if (str.find(':') != string::npos)
    {
        delimiter = ':';
    }

    vector<string> result;

    size_t pos = str.find(delimiter);

    if (pos != string::npos)
    {
        for (; pos != string::npos; pos = str.find(delimiter)) 
        {
            string token;
            token = str.substr(0, pos);
            result.push_back(token);
            str.erase(0, pos + 1);
        }
    }
    result.push_back(str); // last token

    return result;
}

vector<unsigned int> TokensToUnsignedInts(const vector<string>& vectorOfTokens) {

    vector<unsigned int> result;

    for (const string& str : vectorOfTokens) 
    {
        result.push_back(stoi(str));
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

    if (isLeapYear(year) && month == 2 && date != 29)
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

vector<unsigned int>& getLaterDate(vector<unsigned int>& date1, vector<unsigned int>& date2) {
    for (size_t i{date1.size()}; i > 0; --i) {
        
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

void printAbsoluteDifference(unsigned int& absoluteDifferenceInSeconds) {
    unsigned int absoluteDifferenceHours    = (absoluteDifferenceInSeconds / 60) / 60;
    unsigned int absoluteDifferenceMinutes  = absoluteDifferenceHours / 60;
    unsigned int absoluteDifferenceSeconds  = absoluteDifferenceInSeconds % 60;
    
    printTime(absoluteDifferenceHours, absoluteDifferenceMinutes, absoluteDifferenceSeconds);
}

int main() {

    string inputDate1   = "22.10.2020";
    string inputTime1   = "00:00:00";
    string inputDate2   = "22.10.2019";
    string inputTime2   = "01:00:00";
    
    vector<string> tokenizedDate1   = stringToVectorOfTokens(inputDate1);
    vector<unsigned int> dataDate1  = TokensToUnsignedInts(tokenizedDate1);
    vector<string> tokenizedTime1   = stringToVectorOfTokens(inputTime1);
    vector<unsigned int> dataTime1  = TokensToUnsignedInts(tokenizedTime1);

    vector<string> tokenizedDate2   = stringToVectorOfTokens(inputDate2);
    vector<unsigned int> dataDate2  = TokensToUnsignedInts(tokenizedDate2);
    vector<string> tokenizedTime2   = stringToVectorOfTokens(inputTime2);
    vector<unsigned int> dataTime2  = TokensToUnsignedInts(tokenizedTime2);

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
        cout << calculateAbsoluteDateDifferenceInDays(date1Date, date1Month, date1Year, date2Date, date2Month, date2Year) << "-";
        unsigned int absoluteTimeDifferenceInSeconds = calculateAbsoluteTimeDifferenceInSeconds(time1Hours, time1Minutes, time1Seconds, time2Hours, time2Minutes, time2Seconds);
        printAbsoluteDifference(absoluteTimeDifferenceInSeconds);
        cout << endl;
    }
    else
    {
        cout << "Invalid date/time" << endl;
    }
    

    return 0;
}