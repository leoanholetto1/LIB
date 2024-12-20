struct Point{
	ll x, y;
	Point(ll x=0, ll y=0): x(x), y(y){}

	Point operator+(const Point &o) const{ return {x + o.x, y + o.y}; } // a + b
	Point operator-(const Point &o) const{ return {x - o.x, y - o.y}; } // a - b
	Point operator*(ll t) const{ return {x * t, y * t}; } // a * t
	Point operator/(ll t) const{ return {x / t, y / t}; } // a / t
	ll operator*(const Point &o) const{ return x * o.x + y * o.y; } // Escalar  (a * b)
	ll operator^(const Point &o) const{ return x * o.y - y * o.x; } // Vetorial (a ^ b)
	//bool operator <(const Point& b) const { return x == b.x ? y < b.y : x < b.x; }
	bool operator<(const Point &p) const {
		return y < p.y;
	}
	bool operator==(const Point &p){
		return (x == p.x && y == p.y);
	}
	ll cross(const Point& b, const Point& c) const {
		return (b - *this) ^ (c - *this);
	}
};

