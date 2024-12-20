struct circle{
    point c;
    double r;
    circle() {}
    circle(point _c, double _r) { c = _c, r = _r; }
    bool operator==(circle other) const{
        return other.c == c && abs(r - other.r) < EPS;
    }
    bool operator<(circle other) const{
        if (!(other.c == c))
            return c < other.c;
        return r < other.r;
    }
};
struct point{
    double x, y;
    point() { x = y = 0.0; }
    point(double _x, double _y) : x(_x), y(_y) {}
    bool operator<(point other) const{
        if (fabs(x - other.x) > EPS)
            return x < other.x;
        else
            return y < other.y;
    }
    bool operator==(point other) const{
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
    }
    point operator+(point other) const{
        return point(x + other.x, y + other.y);
    }
    point operator-(point other) const{
        return point(x - other.x, y - other.y);
    }
    point operator*(double k) const{
        return point(x * k, y * k);
    }
    double norm(){
        return hypot(x, y);
    }
};