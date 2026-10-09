#pragma once

struct Point {
    double x, y;
};
inline bool comparePoints(const Point& p1, const Point& p2){
    if (p1.x * p1.x + p1.y*p1.y < p2.x * p2.x +  p2.y*p2.y){
        return true;
    }
    else{
        return false;
    }
}
