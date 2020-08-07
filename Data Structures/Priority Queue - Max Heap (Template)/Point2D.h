#include <iostream>
#include <fstream>

using namespace std;

class Point2D {
    public:
        Point2D() {this->x = 0; this->y = 0;}
        Point2D(int x, int y) {this->x = x; this->y = y;}
        int x;
        int y;
};

ostream &operator<<(ostream &output, const Point2D &point) {
    output<<"("<<point.x<<","<<point.y<<")";
    return output;
}

bool operator>(const Point2D &left, const Point2D &right) {
    return (left.x*left.x)+(left.y*left.y) > (right.x*right.x)+(right.y*right.y);
}

bool operator==(const Point2D &left, const Point2D &right) {
    return (left.x*left.x)+(left.y*left.y) == (right.x*right.x)+(right.y*right.y);
}

bool operator<(const Point2D &left, const Point2D &right) {
    return !(left>right || left==right);
}
