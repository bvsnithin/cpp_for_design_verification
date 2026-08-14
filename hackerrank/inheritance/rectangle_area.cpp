// https://www.hackerrank.com/challenges/rectangle-area/problem?isFullScreen=true

#include <iostream>

using namespace std;
/*
 * Create classes Rectangle and RectangleArea
 */
class Rectangle{
    
    protected: int width, height;
    
    public:
        void display(){
            cout << width << " " <<height << endl;
        }
};

class RectangleArea : public Rectangle{
    public:
        void read_input(){
            cin >> width;
            cin >> height;
        }
        
        void display(){
            int area;
            area = width * height;
            cout << area << endl;
        }
};

int main()
{
    /*
     * Declare a RectangleArea object
     */
    RectangleArea r_area;
    
    /*
     * Read the width and height
     */
    r_area.read_input();
    
    /*
     * Print the width and height
     */
    r_area.Rectangle::display();
    
    /*
     * Print the area
     */
    r_area.display();
    
    return 0;
}