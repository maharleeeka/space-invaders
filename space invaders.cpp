#include <graphics.h>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

/**POINT CLASS**/
class Point{
    public:
        int x;
        int y;
        Point();
        Point(int x, int y);
        void setter(int x, int y);
};
/**POINT CLASS**/

/**POLYGON CLASS**/
class Polygon{
    public:
        int totalPoints;
        vector<Point> points;
};
Point::Point(){
        x = 0;
        y = 0;
};
Point::Point(int x, int y){
        this->x = x;
        this->y = y;
};
void Point::setter(int x, int y){
        this->x = x;
        this->y = y;
};
/**POLYGON CLASS**/

/**TRIANGLE CLASS**/
class Triangle: public Polygon{
   public:
        Triangle(int totPoint, vector<Point> &pts);
        void drawTriangle();
        void destroy();
};
Triangle::Triangle(int totPoint, vector<Point> &pts){
    totalPoints = totPoint;
    points = pts;
};
void Triangle::drawTriangle(){
    for(int i = 0; i < points.size(); i++){
        if(i==2){
            line(points.at(i).x, points.at(i).y, points.at(0).x, points.at(0).y);
        }
        else{
            line(points.at(i).x, points.at(i).y, points.at(i+1).x, points.at(i+1).y);
        }
    }
}
/**TRIANGLE CLASS**/

/**GUN CLASS**/
class Gun: public Polygon{
    public:
        Gun(int totPoint, vector<Point> &pts);
        void drawGun();
};

/**GUN CLASS**/

int main(){
    initwindow(500,500);

    vector <Point> triPoints;
    int x = 20, y = 20, flag = 0;
    Point a, b, c;

    while(y < 300){
        //cleardevice();
        cout<<x<<endl;
        cout<<y<<endl;
        if(flag == 0){
            a.setter(x,y);
            b.setter(x-20,y+40);
            c.setter(x+20, y+40);
            x+=45;
        }else{
            a.setter(x,y);
            b.setter(x-20,y+40);
            c.setter(x+20, y+40);
            x-=45;
        }

        triPoints.push_back(a);
        triPoints.push_back(b);
        triPoints.push_back(c);
        Triangle trig(triPoints.size(),triPoints);
        trig.drawTriangle();

        if(x + 45 > 490){
            flag = 1;
            y+=50;
        }else if(x <= 10){
            flag = 0;
            y+=50;
        }
        delay(800);
        triPoints.pop_back();
        triPoints.pop_back();
        triPoints.pop_back();

    };


    getch();
return 0;
}
