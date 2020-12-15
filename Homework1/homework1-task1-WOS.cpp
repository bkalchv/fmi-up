// Дадена е декартова координатна система. Всеки правоъгълник със страни успоредни на координатните оси в нея
// може да се определи с четири числа с плаваща точка: координатите на долния си ляв ъгъл (x, y), ширината и дължината си. 
// Напише програма, която прочита от стандартния вход данни за два правоъгълника и извежда на екрана лицето на общата им част. 
// Ако правоъгълниците нямат обща част, приемаме лицето за нула.

#include <iostream>
#include <vector>


using namespace std;


unsigned int calculateArea(unsigned int height, unsigned int length) {
        return height*length;
}

int calculateMostDRP_x(const int& mostDLP_x, const unsigned int& length) {
        return mostDLP_x + length;
}

int calculateMostDRP_y(const int& mostDLP_y) {
        return mostDLP_y;
}

int calculateMostULP_x(const int& mostDLP_x)  {
        return mostDLP_x;
}

int calculateMostULP_y(const int& mostDLP_y, const unsigned int& height)  {
        return mostDLP_y + height;
}

int calculateMostURP_x(const int& mostDLP_x, const unsigned int& length)  {
        return mostDLP_x + length;
}

int calculateMostURP_y(const int& mostDLP_y, const unsigned int& height)  {
        return mostDLP_y + height;
}

bool doOverlay(const int& rec1_x1, const int& rec1_y1, const unsigned int& rec1_length, const unsigned int& rec1_height, const int& rec2_x2, const int& rec2_y2, const unsigned int& rec2_length, const unsigned int& rec2_height) {
    
    if (rec1_x1 >= calculateMostURP_x(rec2_x2, rec2_length) || calculateMostURP_x(rec1_x1, rec1_length) <= rec2_x2)
    {
        return false;
    }

    if (rec1_y1 >= calculateMostURP_y(rec2_y2, rec2_height) || calculateMostURP_y(rec1_y1, rec1_height) <= rec2_y2)
    {
        return false;
    }

    return true;
}

unsigned int calculateOverlayArea(const int& rec1_x1, const int& rec1_y1, const unsigned int& rec1_length, const unsigned int& rec1_height, const int& rec2_x2, const int& rec2_y2, const unsigned int& rec2_length, const unsigned int& rec2_height) {

    if (doOverlay(rec1_x1, rec1_y1, rec1_length, rec1_height, rec2_x2, rec2_y2, rec2_length, rec2_height))
    {   
        int overlayLenght;
        
        int overlayMostURP_x;
        int overlayMostDLP_x;

        if (calculateMostURP_x(rec1_x1, rec1_length) < calculateMostURP_x(rec2_x2, rec2_length)) 
        {
            overlayMostURP_x = calculateMostURP_x(rec1_x1, rec1_length);
        }
        else 
        {
            overlayMostURP_x = calculateMostURP_x(rec2_x2, rec2_length);
        }

        if (rec1_y1 > rec2_y2)
        {
            overlayMostDLP_x = rec1_x1;
        }
        else
        {
            overlayMostDLP_x = rec2_x2;
        }
        
        overlayLenght = overlayMostURP_x - overlayMostDLP_x;

        int overlayHeight;

        int overlayMostURP_y;
        int overlayMostDLP_y;

        if (calculateMostURP_y(rec1_y1, rec1_height) < calculateMostURP_y(rec2_y2, rec2_height)) 
        {
            overlayMostURP_y = calculateMostURP_y(rec1_y1, rec1_height);
        }
        else 
        {
            overlayMostURP_y = calculateMostURP_y(rec2_y2, rec2_height);
        }

        if (rec1_x1 > rec2_x2)
        {
            overlayMostDLP_y = rec1_y1;
        }
        else
        {
            overlayMostDLP_y = rec2_y2;
        }
        
        overlayHeight = overlayMostURP_y - overlayMostDLP_y;

        return overlayLenght * overlayHeight;
    }

    return 0;
}

int main() 
{
    int x1, y1;
    size_t height1, length1;
    cout << "Input data for the first rectangle: ";
    cin >> x1 >> y1 >> height1 >> length1;

    int x2, y2;
    size_t height2, length2;
    cout << "Input data for the second rectangle: ";
    cin >> x2 >> y2 >> height2 >> length2;

    cout << "Rec1 and Rec2";

    bool rectanglesDoOverlay = doOverlay(x1, y1, length1, height1, x2, y2, length2, height2);

    if (rectanglesDoOverlay)
    {
        cout << " do overlay.\n";
    }
    else
    {
        cout << "do NOT overlay\n";
    }
    
    cout << "Area of overlay: ";
    cout << calculateOverlayArea(x1, y1, length1, height1, x2, y2, length2, height2) << endl; 

    return 0;
}