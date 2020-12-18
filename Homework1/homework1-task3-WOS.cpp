// Да се напише програма, която прочита от стандартния вход две точки във времето във формат 
// dd.mm.yyyy HH:MM:SS (незадължително с водещи нули) и извежда на стандартния изход един ред, съдържащ тяхната разлика
// във формат [days-]HH:MM:SS - ако броят дни е 0, то той да не се извежда и HH, MM, SS са задължително с водещи нули.
// Ако някоя от въведените точки във времето не е валидна, програмата да изведе един ред със съобщение „Invalid date/time“.

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

const unsigned int MAX_INPUT_DATE_SIZE  = 11;
const unsigned int MAX_INPUT_TIME_SIZE  = 9;
const unsigned int TOKENS_AMOUNT        = 3;
const unsigned int MAX_TOKENS_LENGTH    = 4;
const unsigned int DATE_INDEX           = 0;
const unsigned int MONTH_INDEX          = 1;
const unsigned int YEAR_INDEX           = 2;
const unsigned int HOURS_INDEX          = 0;
const unsigned int MINUTES_INDEX        = 1;
const unsigned int SECONDS_INDEX        = 2;

const unsigned int SECONDS_IN_AN_HOUR   = 3600;
const unsigned int MINUTES_IN_AN_HOUR   = 60;
const unsigned int HOURS_IN_A_DAY       = 24;
const unsigned int SECONDS_IN_A_MINUTE  = 60;

const unsigned int MONTHS_IN_AN_YEAR    = 12;
const unsigned int DAYS_IN_AN_YEAR      = 365;

char* subString(const char* str, size_t fromIdx, size_t toIdx) {
    
    if (fromIdx < toIdx && fromIdx > 0 && toIdx > 0) 
    {
        char* result = new char[toIdx - fromIdx];

        for (size_t i{fromIdx}; i < toIdx; ++i)
        {
            result[i - fromIdx] = str[i];
        }

        return result;
    }

    return nullptr;
}

int find(const char* str, char ch) {

    int idx{0};
    for (char c = *str; c; c = *++str) 
    {
        if (ch == c) {
            return idx;
        }
        ++idx;
    }

    return -1;
}

char** stringToArrayOfTokens(char* str) {

    char delimiter[1];

    if (find(str,'.') != -1)
    {
        delimiter[0] = '.';
    }

    if (find(str,':') != -1)
    {
        delimiter[0] = ':';
    }

    char** result = new char*[TOKENS_AMOUNT];

    char* token = new char[MAX_TOKENS_LENGTH];
    token = strtok(str, delimiter);
    size_t idx{0};

    while (token != NULL)
    {   
        result[idx] = token;
        token = strtok(NULL, delimiter);
        ++idx;
    }

    return result;
}

unsigned int* TokensToUnsignedInts(char** vectorOfTokens) {

    unsigned int* result = new unsigned int[TOKENS_AMOUNT];

    for (size_t i{0}; i < TOKENS_AMOUNT; ++i) 
    {   
        char* temp = vectorOfTokens[i];
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

unsigned int getMonthsDays(unsigned int month, unsigned int year) {

    if (isEven(month) && month <= 7)
    {    
        if (month == 2) // February
        {   
            if (isLeapYear(year)) {
                return 29;
            }

            return 28;
        }
        else
        {
            return 30; // April, June
        }
    } 
    else if (!isEven(month) && month <= 7) // January, March, May, July
    {
        return 31;
    }
    else if (isEven(month) && month > 7) // August, October, December
    {
        return 31;
    }
    else if (!isEven(month) && month > 7) // September, November
    {
        return 30;
    }

    return -1;
}

bool isLaterTimeStamp(unsigned int* time1, unsigned int* time2) {

    for (size_t i{TOKENS_AMOUNT}; i > 0; --i) {
        
        if (time1[i-1] == time2[i-1]) {

            continue;
        }

        if (time1[i-1] > time2[i-1]) 
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }

    return false;
}

unsigned int*& getLaterDate(unsigned int* (&date1), unsigned int* time1, unsigned int* (&date2), unsigned int* time2) {

    for (size_t i{TOKENS_AMOUNT}; i > 0; --i) {
        
        if (date1[i-1] == date2[i-1]) {
            
            if (i == 1)
            {
                if (isLaterTimeStamp(time1, time2))
                {
                    return date1;
                }
                
                return date2;
            }

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
    
    if (date1 != date2 || month1 != month2 || year1 != year2) 
    {
        unsigned int laterYear  = year1;
        unsigned int laterMonth = month1;
        unsigned int laterDate  = date1;

        unsigned int absoluteDateDifferenceInDays = 0;
        
        if (month1 != month2) 
        {
            absoluteDateDifferenceInDays += date1;
            --laterMonth; 
        }

        if (year1 != year2) 
        {

            while (laterMonth > 0) 
            {   
               absoluteDateDifferenceInDays += getMonthsDays(laterMonth, laterYear);
                --laterMonth;

                if (laterMonth == 0)
                {
                    laterMonth = MONTHS_IN_AN_YEAR;
                    break;
                }

            }

            --laterYear;

            while (laterYear > year2)
            {   
                if (isLeapYear(laterYear)) 
                {   
                    absoluteDateDifferenceInDays += 1;
                }

                absoluteDateDifferenceInDays += DAYS_IN_AN_YEAR;
                --laterYear;
            }
        }

        while (laterMonth > month2 + 1 || laterYear != year2)
        {   

            if (laterMonth == 0)
            {   
                --laterYear;
                laterMonth = MONTHS_IN_AN_YEAR;
            }

            absoluteDateDifferenceInDays += getMonthsDays(laterMonth, laterYear);

            --laterMonth;
        }

        if (month1 != month2 || laterMonth > month2)
        {
            laterDate = getMonthsDays(laterMonth, laterYear);
        }
        
        while  ( (laterDate > date2 || laterMonth != month2) )
        {    
            
            if (laterDate == 0) 
            {   
                
                --laterMonth;
                laterDate = getMonthsDays(laterMonth, laterYear);
            }

            --laterDate;
            
            if (laterDate == date2 - 1 && laterMonth == month2)
            {
                 break;
            }

            ++absoluteDateDifferenceInDays;

        }

        return absoluteDateDifferenceInDays;

    }

    return 0;
}

unsigned int calculateAbsoluteTimeDifferenceInSeconds(unsigned int hours1, unsigned int minutes1, unsigned int seconds1, unsigned int hours2, unsigned int minutes2, unsigned int seconds2, unsigned int& daysDifference) {
    int timeInSeconds1 = SECONDS_IN_A_MINUTE * (hours1 * MINUTES_IN_AN_HOUR + minutes1) + seconds1;
    int timeInSeconds2 = SECONDS_IN_A_MINUTE * (hours2 * MINUTES_IN_AN_HOUR + minutes2) + seconds2;
    int difference = timeInSeconds1 - timeInSeconds2;

    if (difference < 0)
    {   
        if (seconds2 > seconds1) 
        {
            --minutes1;
            seconds1 +=  SECONDS_IN_A_MINUTE;
        }

        int differenceSeconds = seconds1 - seconds2;

        if (minutes2 > minutes1)
        {
            --hours1;
            minutes1 += MINUTES_IN_AN_HOUR;
        }
        int differenceMinutes  = minutes1 - minutes2;

        if (hours2 > hours1) {
            
            if (daysDifference > 0)
            {
            --daysDifference;        
            }
            
            hours1 += HOURS_IN_A_DAY ;
        }

        int differenceHours    = hours1 - hours2;

        return differenceHours * SECONDS_IN_AN_HOUR + differenceMinutes * SECONDS_IN_A_MINUTE + differenceSeconds;
    }

    return difference;
}

void printTime(const unsigned int& hours, const unsigned int& minutes, const unsigned& seconds) {
    hours < 10 ? cout << "0" << hours : cout << hours; 
    cout << ":";
    minutes < 10 ? cout << "0" <<  minutes : cout <<  minutes;
    cout << ":";
    seconds < 10 ? cout << "0" <<  seconds : cout <<  seconds;
}

void printAbsoluteDifference(unsigned int absoluteDifferenceInSeconds) {
    unsigned int absoluteDifferenceHours    = absoluteDifferenceInSeconds / SECONDS_IN_AN_HOUR;
    absoluteDifferenceInSeconds             = absoluteDifferenceInSeconds % SECONDS_IN_AN_HOUR;
    unsigned int absoluteDifferenceMinutes  = absoluteDifferenceInSeconds / MINUTES_IN_AN_HOUR;
    absoluteDifferenceInSeconds             = absoluteDifferenceInSeconds % MINUTES_IN_AN_HOUR;
    unsigned int absoluteDifferenceSeconds  = absoluteDifferenceInSeconds;

    printTime(absoluteDifferenceHours, absoluteDifferenceMinutes, absoluteDifferenceSeconds);
}

int main() {

    char    inputDate1[MAX_INPUT_DATE_SIZE];
    char    inputTime1[MAX_INPUT_TIME_SIZE];
    cin >> inputDate1 >> inputTime1;

    char    inputDate2[MAX_INPUT_DATE_SIZE];
    char    inputTime2[MAX_INPUT_TIME_SIZE];
    cin >> inputDate2 >> inputTime2;
    
    char** tokenizedDate1           = stringToArrayOfTokens(inputDate1);
    unsigned int* dataDate1         = TokensToUnsignedInts(tokenizedDate1);
    char** tokenizedTime1           = stringToArrayOfTokens(inputTime1);
    unsigned int* dataTime1         = TokensToUnsignedInts(tokenizedTime1);

    char** tokenizedDate2           = stringToArrayOfTokens(inputDate2);
    unsigned int* dataDate2         = TokensToUnsignedInts(tokenizedDate2);
    char** tokenizedTime2           = stringToArrayOfTokens(inputTime2);
    unsigned int* dataTime2         = TokensToUnsignedInts(tokenizedTime2);

    if (getLaterDate(dataDate1, dataTime1, dataDate2, dataTime2) == dataDate2) 
    {
        std::swap(dataDate1, dataDate2);
        std::swap(dataTime1, dataTime2);
    }

    unsigned int date1Date      = dataDate1[DATE_INDEX];
    unsigned int date1Month     = dataDate1[MONTH_INDEX];
    unsigned int date1Year      = dataDate1[YEAR_INDEX];
    unsigned int time1Hours     = dataTime1[HOURS_INDEX];
    unsigned int time1Minutes   = dataTime1[MINUTES_INDEX];
    unsigned int time1Seconds   = dataTime1[SECONDS_INDEX];

    unsigned int date2Date      = dataDate2[DATE_INDEX];
    unsigned int date2Month     = dataDate2[MONTH_INDEX];
    unsigned int date2Year      = dataDate2[YEAR_INDEX];
    unsigned int time2Hours     = dataTime2[HOURS_INDEX];
    unsigned int time2Minutes   = dataTime2[MINUTES_INDEX];
    unsigned int time2Seconds   = dataTime2[SECONDS_INDEX];


    bool isValidInput1 = isValidDate(date1Date, date1Month, date1Year) && isValidTime(time1Hours, time1Minutes, time1Seconds);
    bool isValidInput2 = isValidDate(date2Date, date2Month, date2Year) && isValidTime(time2Hours, time2Minutes, time2Seconds);

    if (isValidInput1 && isValidInput2) 
    {   
        unsigned int absoluteDateDifferenceInDays = calculateAbsoluteDateDifferenceInDays(date1Date, date1Month, date1Year, date2Date, date2Month, date2Year);

        unsigned int absoluteTimeDifferenceInSeconds = calculateAbsoluteTimeDifferenceInSeconds(time1Hours, time1Minutes, time1Seconds, time2Hours, time2Minutes, time2Seconds, absoluteDateDifferenceInDays);

        while (absoluteTimeDifferenceInSeconds % (HOURS_IN_A_DAY * SECONDS_IN_AN_HOUR) != absoluteTimeDifferenceInSeconds && absoluteDateDifferenceInDays != 0) 
        {
            absoluteTimeDifferenceInSeconds -= (HOURS_IN_A_DAY * SECONDS_IN_AN_HOUR);
            ++absoluteDateDifferenceInDays;
        }

        if (absoluteDateDifferenceInDays > 0) 
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

    return 0;
}