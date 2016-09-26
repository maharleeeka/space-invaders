#include <graphics.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#define DEG_TO_RAD 0.0174532925
#define pi 3.14159

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

/**LINE CLASS**/
class Line{
    public:
        Point a, b;
        void drawLine();
        void setter();
};

void Line::drawLine(){
    line(a.x, a.y, b.x, b.y);
}

/**LINE CLASS**/

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

/**SPACESHIP CLASS**/
class Spaceship: public Polygon{
    public:
        Spaceship();
        void drawShip();
};

Spaceship::Spaceship(){

}
void Spaceship::drawShip(){
    vector<Point> pts;
    Point a, b, c;
    a.setter(250, 470);
    b.setter(240, 500);
    c.setter(260, 500);

    pts.push_back(a);
    pts.push_back(b);
    pts.push_back(c);

    Triangle spaceship(pts.size(), pts);
    spaceship.drawTriangle();

    cout<<"drawing ship"<<endl;
}
/**SPACESHIP CLASS**/

/**GUN CLASS**/
class Gun{
    public:
        Line gun;
        int x1, y1, x2, y2;
        void drawGun(int x1, int y1, int x2, int y2);
        bool isFired;
};

void Gun::drawGun(int x1, int y1, int x2, int y2){
    line(x1, y1, x2, y2);
}
/**GUN CLASS**/

int main(){
    initwindow(500,500);


    vector <Point> triPoints;
    int x = 20, y = 20, flag = 0;
    int i, radius = 50;
    int x1 = 250, y1 = 470, x2= 250, y2 = 430;
    Point a, b, c;
    Point p1, p2, p3;
    double rad = pi;
    Line bullet;
    bool isFired;
    char input;

    while(y < 500){
        cleardevice();
        Spaceship sp;
        sp.drawShip();
        Gun gun;
        gun.drawGun(x1, y1, x2, y2);

        if(flag == 0){
            a.setter(x,y);
            b.setter(x-10,y+20);
            c.setter(x+10, y+20);
            x++;
        }else{
            a.setter(x,y);
            b.setter(x-10,y+20);
            c.setter(x+10, y+20);
            x--;
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

        triPoints.pop_back();
        triPoints.pop_back();
        triPoints.pop_back();


        if(kbhit()){
            input = getch();
            if(input == KEY_LEFT){
                if (rad <= pi+(pi/2)){
                    rad += 0.5;
                    x2 = radius*sin(rad) + x1;
                    y2 = radius*cos(rad) + y1;
                } else{
                    rad = pi/2;
                }
            }

            if(input == KEY_RIGHT){
                if (rad <= pi+pi/2){
                    rad -= 0.5;
                    x2 = radius*sin(rad) + x1;
                    y2 = radius*cos(rad) + y1;
                } else{
                    rad = pi/2;
                }
            }
            if(input == 32){
                if(!isFired){
                    bullet.a.setter(x2,y2);
                    bullet.b.setter(x2,y2-20);
                    bullet.drawLine();
                }
                isFired = true;
            }
        }

        if(isFired){
            if(bullet.a.y > 0){
                bullet.a.setter(bullet.a.x, bullet.a.y-10);
                bullet.b.setter(bullet.b.x, bullet.b.y-10);
                bullet.drawLine();
            }else{
                isFired = false;
                bullet.a.setter(0,0);
                bullet.b.setter(0,0);
            }
        }

        delay(2);
    }
    getch();
return 0;
}
