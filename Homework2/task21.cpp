#include <iostream>
#include <thread>
#include <time.h>
#include <cstring>

using namespace std;

std::chrono::duration<double, ratio<1>> milisecondsToDuration(double seconds) 
{
    return std::chrono::duration<double, ratio<1>>(seconds);
}

bool isValidInput(double input)
{
    if (input < 0 || input > 1) 
    {
        return false;
    }

    return true;
}

int inputToPercentage(double input)
{
    return input * 100;
}

char* fillLoadingBar(size_t length, char leftOpeningSymbol, char emptySymbol, char rightClosingSymbol) 
{   
    char* loadingBar = new char[length + 2]; 

    for (size_t i{0}; i < length + 2; ++i) 
    {
        if (i == 0)
        {
            loadingBar[i] = leftOpeningSymbol;
            continue;
        }

        if (i == length + 1) 
        {
            loadingBar[i] = rightClosingSymbol;
            continue;
        }

        loadingBar[i] = emptySymbol;
    }

    return loadingBar; 
}

void printLoadingBar(char* loadingBar, int percentage, bool showPercentages)
{   
    size_t middleIndex = strlen(loadingBar)/2;
    for (size_t i{0}; i < strlen(loadingBar); ++i)
    {
        if (i == middleIndex && showPercentages)
        {
            cout << " " << percentage << "% ";
            continue;
        }
        cout << loadingBar[i];
    }
    cout << endl;
}

size_t indexOfPercentage(char* (&loadingBar), double fromPercentageInput) 
{   
    size_t result = 0;
    static const size_t barLength           = strlen(loadingBar) - 2;
    const double progressLevel = 100.0 / barLength;
    int fromPercentage = inputToPercentage(fromPercentageInput);
    int progress = 0;

    for (size_t i = 0; i < barLength; ++i) 
    {   
        if (progress >= fromPercentage)
        {
            result = i;
            return result;
        }
        progress += progressLevel;
    }

    return result;
}

void loadingByTime(char* (&loadingBar), double time1, char loadingSymbol, double fromPercentageOn, bool showPercentages)
{
    static const size_t barLength           = strlen(loadingBar) - 2;
    static const size_t actualBarLength     = barLength - (fromPercentageOn * barLength);
    static const double waitingMiliseconds  = time1 / (double) actualBarLength;
    int progress = inputToPercentage(fromPercentageOn);
    const double progressLevel = 100.0 / barLength;

    for (size_t i = indexOfPercentage(loadingBar, fromPercentageOn); i <= barLength; ++i) 
    {   
        if (progress <= 100) 
        {
            if (i == 0)
            {   
                printLoadingBar(loadingBar, progress, showPercentages);
                std::this_thread::sleep_for(milisecondsToDuration(waitingMiliseconds));
                progress += progressLevel;
                continue;
            }
            system("clear");
            loadingBar[i] = loadingSymbol;
            printLoadingBar(loadingBar, progress, showPercentages);
            std::this_thread::sleep_for(milisecondsToDuration(waitingMiliseconds));
            progress += progressLevel;    
        }
        else
        {
            break;
        }
    }

    while (progress < 100)
    {
        system("clear");
        printLoadingBar(loadingBar, progress, showPercentages);
        std::this_thread::sleep_for(milisecondsToDuration(waitingMiliseconds));
        progress += progressLevel;
    }

    if (progress >= 100)
    {
        system("clear");
        printLoadingBar(loadingBar, 100, showPercentages);
    }
}

void printUpTo(char* (&loadingBar), char loadingSymbol, double upToPercentageInput, bool showPercentages)
{
    static const size_t barLength           = strlen(loadingBar) - 2;
    int progress = 0;
    const double progressLevel = 100.0 / barLength;
    int upToPercentage = inputToPercentage(upToPercentageInput);

    for (size_t i = 1; i < barLength; ++i) 
    {   
        if (progress < upToPercentage)
        {
            loadingBar[i] = loadingSymbol;
            progress += progressLevel;
        }
        else
        {
            break;
        }
    }
}

void oneFunctionToRuleThemAll(double currentProgress, char leftOpeningSymbol, char rightClosingSymbol, bool showPercentage, char loadingSymbol, char emptySymbol, size_t loadingSections, size_t loadingTime)
{
    char* loadingBar = fillLoadingBar(loadingSections, leftOpeningSymbol, emptySymbol, rightClosingSymbol);
    printUpTo(loadingBar, loadingSymbol, currentProgress, showPercentage);
    loadingByTime(loadingBar, loadingTime, loadingSymbol, currentProgress, showPercentage);
}

int main() {
    double  currentProgress;
    char    leftOpeningSymbol;
    char    rightOpeningSymbol;
    bool    showPercentage;
    char    showPercentageAnswer;
    char    loadingSymbol;
    char    emptySymbol;
    size_t  loadingSections;
    size_t  loadingTimeInSeconds;

    cout    << "Current progress: ";
    while (!(cin >> currentProgress) || !isValidInput(currentProgress))
    {
        system("clear");
        cout << "Invalid input. Try again! [0,1]" << endl;
        cout << "Current progress: ";
    }

    cout << "Opening symbol: ";
    cin >> leftOpeningSymbol;

    cout << "Closing symbol: ";
    cin >> rightOpeningSymbol;

    cout << "Percentage representation? (1- yes; 0 - no): ";
    cin >> showPercentageAnswer;
    while (showPercentageAnswer != '1' && showPercentageAnswer != '0')
    {
        system("clear");
        cout << "Invalid input. Try again!" << endl;
        cout << "Percentage representation? (1- yes; 0 - no)";
        cin  >> showPercentageAnswer;
    }
    showPercentage = showPercentageAnswer == '1'; 
    

    cout << "Loading symbol: ";
    cin  >> loadingSymbol;

    cout << "Empty symbol: ";
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get(emptySymbol);
    
    cout << "Amount of loading sections: ";
    while (!(cin  >> loadingSections))
    {   
        system("clear");
        cout << "Invalid input. Try again! (whole number > 0)" << endl;
        cout << "Amount of loading sections: ";
    }

    cout << "Loading time: ";
    while (!(cin >> loadingTimeInSeconds)) 
    {
        system("clear");
        cout << "Invalid input. Try again! (whole number in seconds)" << endl;
        cout << "Loading time: ";
    }

    oneFunctionToRuleThemAll(currentProgress, leftOpeningSymbol, rightOpeningSymbol, showPercentage, loadingSymbol, emptySymbol, loadingSections, loadingTimeInSeconds);

    return 0;
} 