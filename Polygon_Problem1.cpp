//Program 1 : Check if the given point lies inside or outside a polygon?

#include<iostream>
#define INF 10000

using namespace std;

struct Point{   //Coordinates
    int x;
    int y;
};

bool onSegment(Point p, Point q, Point r){  //Check whether a point is on segment of the other two
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

int orientation(Point p, Point q, Point r){     //Orientation of three given points
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0;  // co-linear

    return (val > 0)? 1: 2; // 1-->clockwise or 2-->anticlockwise
}

 bool doIntersect(Point p1, Point q1, Point p2, Point q2){      //4 Orientations for Different Cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    if (o1 == 0 && onSegment(p1, p2, q1))       // p1, q1 and p2-->co-linear and p2 lies on segment p1q1
        return true;

    if (o2 == 0 && onSegment(p1, q2, q1))       // p1, q1 and p2-->co-linear and q2 lies on segment p1q1
        return true;

    if (o3 == 0 && onSegment(p2, p1, q2))       // p2, q2 and p1-->co-linear and p1 lies on segment p2q2
        return true;

    if (o4 == 0 && onSegment(p2, q1, q2))       // p2, q2 and q1-->co-linear and q1 lies on segment p2q2
        return true;

    return false;   // None of the above cases
}

bool isInside(Point polygon[], int n, Point p){
    if (n < 3)  return false;   //Min 3 vertices in a polygon

    Point extreme = {INF, p.y};     //Point for line from p to infinity

    int count = 0, i = 0;   //Count refers to intersections of above line with sides of polygon
    do{
        int next = (i+1)%n;

        if (doIntersect(polygon[i], polygon[next], p, extreme)){ //Check whether line segment from 'p' to 'extreme' intersects or not with line segment from 'polygon[i]' to 'polygon[next]'.
                                                                 //Then Check if point 'p' is co-linear with line segment 'i-next'.
                                                                 //Then check if it lies on segment. If it lies, return true. If not, return false.
            if (orientation(polygon[i], p, polygon[next]) == 0)
               return onSegment(polygon[i], p, polygon[next]);

            count++;
        }
        i = next;
    } while (i != 0);

    return count&1; //Return true if count is odd, and false if even
}

//  Generate coordinates and polygon
//  Taken from the given problem
int main(){
    Point polygon1[] = {{1, 0}, {8, 3}, {8, 8}, {1, 5}};
    Point polygon2[] = {(-3,-2), (-2,-0.8), (0,1.2), (2.2, 0), (2,4.5)};
    int n = sizeof(polygon1)/sizeof(polygon2);

    Point p1 = {3,5};int n1 = sizeof(polygon1)/sizeof(polygon2);
    Point p2 = {0,0};
    isInside(polygon1, n, p1)? cout << "Output: False\n": cout << "Output: True \n"; //Tells whether the point p1 is inside or outside the polygon1
    isInside(polygon2, n, p2)? cout << "Output: True\n": cout << "Output: False \n"; //Tells whether the point p2 is inside or outside the polygon2

    return 0;
}
