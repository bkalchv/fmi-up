// Дадена е декартова координатна система. Всеки правоъгълник със страни успоредни на координатните оси в нея
// може да се определи с четири числа с плаваща точка: координатите на долния си ляв ъгъл (x, y), ширината и дължината си. 
// Напише програма, която прочита от стандартния вход данни за два правоъгълника и извежда на екрана лицето на общата им част. 
// Ако правоъгълниците нямат обща част, приемаме лицето за нула.

#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;

    Point() {
        x = 0;
        y = 0;
    }

    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

struct Rectangle
{   
    size_t  length;
    size_t  height;
    Point   mostDLP;

    Rectangle(size_t _length, size_t _height, Point _mostDLP = Point()) {
        length = _length;
        height = _height;
        mostDLP = _mostDLP;
    }

    unsigned int calculateArea() {
        return height*length;
    }

    Point calculateMostDRP() const {
        return Point(mostDLP.x + length, mostDLP.y);
    }

    Point calculateMostULP() const {
        return Point(mostDLP.x, mostDLP.y + height);
    }

    Point calculateMostURP() const {
        return Point(mostDLP.x + length, mostDLP.y + height);
    }
};

// vector<Point> getAllPoints(const Rectangle& rec) {
//     vector<Point> result;
//     result.reserve(4);
//     result = {rec.mostDLP, rec.calculateMostDRP() , rec.calculateMostULP(),  rec.calculateMostURP()};
//     return result;
// }

bool doOverlay(const Rectangle& rec1, const Rectangle& rec2) {
    
    if (rec1.mostDLP.x >= rec2.calculateMostURP().x || rec1.calculateMostURP().x <= rec2.mostDLP.x)
    {
        return false;
    }

    if (rec1.mostDLP.y >= rec2.calculateMostURP().y || rec1.calculateMostURP().y <= rec2.mostDLP.y)
    {
        return false;
    }

    return true;
}

unsigned int calculateOverlayArea(const Rectangle& rec1, const Rectangle& rec2) {

    if (doOverlay(rec1, rec2)) 
    {   
        int overlayLenght;
        
        int overlayMostUR_x;
        int overlayMostDL_x;

        if (rec1.calculateMostURP().x < rec2.calculateMostURP().x) 
        {
            overlayMostUR_x = rec1.calculateMostURP().x;
        }
        else 
        {
            overlayMostUR_x = rec2.calculateMostURP().x;
        }

        if (rec1.mostDLP.y > rec1.mostDLP.y)
        {
            overlayMostDL_x = rec1.mostDLP.x;
        }
        else
        {
            overlayMostDL_x = rec2.mostDLP.x;
        }
        
        overlayLenght = overlayMostUR_x - overlayMostDL_x;

        int overlayHeight;

        int overlayMostUR_y;
        int overlayMostDL_y;

        if (rec1.calculateMostURP().y < rec2.calculateMostURP().y) 
        {
            overlayMostUR_y = rec1.calculateMostURP().y;
        }
        else 
        {
            overlayMostUR_y = rec2.calculateMostURP().y;
        }

        if (rec1.mostDLP.x > rec2.mostDLP.x)
        {
            overlayMostDL_y = rec1.mostDLP.y;
        }
        else
        {
            overlayMostDL_y = rec2.mostDLP.y;
        }
        
        overlayHeight = overlayMostUR_y - overlayMostDL_y;

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
    Rectangle rec1 = Rectangle(height1, length1, Point(x1,y1));

    int x2, y2;
    size_t height2, length2;
    cout << "Input data for the second rectangle: ";
    cin >> x2 >> y2 >> height2 >> length2;
    Rectangle rec2 = Rectangle(height2, length2, Point(x2,y2));

    cout << "Rec1 and Rec2";
    doOverlay(rec1, rec2) ? cout << " do overlay.\n" : cout << "do not overlay\n";
    cout << "Area of overlay: ";
    doOverlay(rec1, rec2) ? cout << calculateOverlayArea(rec1, rec2) << endl : cout << 0 << endl; 

    return 0;
}