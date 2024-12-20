//Complexidade: O(n x log n)
struct Point {
    int x, y;
    Point operator +(const Point& b) const { return Point{x+b.x, y+b.y}; }
    Point operator -(const Point& b) const { return Point{x-b.x, y-b.y}; }
    ll operator *(const Point& b) const { return (ll) x * b.y - (ll) y * b.x; }
    bool operator <(const Point& b) const { return x == b.x ? y < b.y : x < b.x; }
    void operator +=(const Point& b) { x += b.x; y += b.y; }
    void operator -=(const Point &b) { x -= b.x; y -= b.y; }
    void operator *=(const int k) { x *= k; y *= k; }
 
    ll cross(const Point& b, const Point& c) const {
        return (b - *this) * (c - *this);
    }
};

ll cross(const Point& o, const Point& a,const Point& b){
    return (a.x - o.x)*(b.y - o.y)-(a.y - o.y)*(b.x - o.x);
}

//Cuidado com pontos colineares.
void convex(vector<Point> P,vector<Point> &hull){
    int n = P.size(), k = 0;
    hull.resize(2 * n);
    sort(P.begin(), P.end());
    // Build lower hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && (int)cross(hull[k - 2], hull[k - 1], P[i]) < 0)
            k--;
        hull[k++] = P[i];
    }
    // Build upper hull
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && (int)cross(hull[k - 2], hull[k - 1], P[i]) < 0)
            k--;
        hull[k++] = P[i];
    }
    hull.resize(k);
    hull.pop_back();
}