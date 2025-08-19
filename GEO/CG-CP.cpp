#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <array>

constexpr double PI = 3.14159265358979323846, INF = 2e9;
constexpr double DEG2RAD = PI/180.0;
using ll = long long;

struct Vec3 {
    double x, y, z;

    Vec3(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {};

    double SqrLength() const {
        return x*x + y*y + z*z;
    }

    double Length() const {
        return sqrt(x*x + y*y + z*z);
    }

    static double SqrDistance(const Vec3& v1, const Vec3& v2) {
        double dx = (v1.x-v2.x);
        double dy = (v1.y-v2.y);
        double dz = (v1.z-v2.z);
        return dx*dx + dy*dy + dz*dz;
    }

    static double Distance(const Vec3& v1, const Vec3& v2) {
        return sqrt(Vec3::SqrDistance(v1, v2));
    }

    static double Angle(const Vec3& v1, const Vec3& v2) {
        return atan2((v1 ^ v2).Length(), v1*v2);
    }

    static int Orientation(const Vec3& p1, const Vec3& p2, const Vec3& p3) {
        double zCross = ((p2-p1)^(p3-p1)).z;
        if(zCross > 1e-7) return 1; // Counter-Clockwise
        else if (zCross < -1e-7) return -1; // Clockwise
        else return 0; // Collinear
    }

    static Vec3 Reflect(const Vec3& I, const Vec3& N) {
        return I - N*(I*N)*2;
    }

    Vec3 operator+(const Vec3& other) const {
        return {this->x + other.x, this->y + other.y, this->z + other.z};
    }

    Vec3 operator-(const Vec3& other) const {
        return {this->x - other.x, this->y - other.y, this->z - other.z};
    }

    Vec3 operator-() const {
        return {-this->x, -this->y, -this->z};
    }

    Vec3 operator*(double s) const {
        return {this->x*s, this->y*s, this->z*s}; 
    }

    Vec3 operator/(double s) const {
        return {this->x/s, this->y/s, this->z/s}; 
    }

    Vec3 Norm() const {
        double len = this->Length();
        return { this->x / len, this->y / len, this->z / len };
    }

private:
    double lerp(double a, double b, double t) const {
        return (1.0 - t) * a + b * t;
    }

public:

    Vec3 Lerp(const Vec3& target, double t) const {
        return {lerp(this->x, target.x, t), lerp(this->y, target.y, t), lerp(this->z, target.z, t)};
    }

    static Vec3 RotateAround(const Vec3& v, const Vec3& axis, double angle) {
        Vec3 k = axis.Norm();
        return v * cos(angle) + (k^v) * sin(angle) + k * (k * v) * (1 - cos(angle));
    }

    double operator*(const Vec3& other) const {
        return this->x * other.x + this->y * other.y + this->z * other.z; 
    }

    Vec3 operator^(const Vec3& other) const {
        return {
                this->y * other.z - this->z * other.y,
                this->z * other.x - this->x * other.z,
                this->x * other.y - this->y * other.x
            }; 
    }

    bool operator==(const Vec3 other) const {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    void Print() const {
        printf("[ %.2lf, %.2lf, %.2lf ]\n", (double)this->x, (double)this->y, (double)this->z);
    }
};

struct Line {
    double a, b;

    Line(double a = 1, double b = 0): a(a), b(b) {}
    Line(double a, double b, double c) {}
    Line(const Vec3& p1, const Vec3& p2) {
        a = (p1.y-p2.y)/(p1.x-p2.x);
        b = p1.y - a*p1.x;
    }

    inline Line Perpendicular() const {
        return {-1/a, b};
    }

    inline double Angle() const {
        return atan(a);
    }

    static double Distance(const Line& line, const Vec3& q) {
        double x = (line.a * (q.y - line.b) + q.x)/(1 + (line.a*line.a - 1e-9)); // |ax-y+b|/sqrt(a^2 + 1)
        double y = line.GetY(x);
        return Vec3::Distance(q, {x, y, 0});
    }

    inline double GetY(double x) const {
        return this->a * x + this->b;
    }
};


struct LineG {
    double a, b, c;
    
    LineG(double a = 0, double b = 1, double c = 0) : a(a), b(b), c(c) {}
    LineG(const Vec3& p1, const Vec3& p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = -(a * p1.x + b * p1.y);
    }

    LineG Perpendicular() const {
        return LineG(-b, a, c);
    }

    inline double Angle() const {
        return atan2(-a, b);
    }

    double GetY(double x) const {
        if (abs(b) < 1e-9) return INF;
        return (-a * x - c) / b;
    }

    static double Distance(const LineG& line, const Vec3& q) {
        return abs(line.a * q.x + line.b * q.y + line.c) / sqrt(line.a * line.a + line.b * line.b);
    }
};

struct LineSeg {
    Vec3 p1, p2;

    LineSeg(const Vec3& p1, const Vec3& p2) : p1(p1), p2(p2) {}

    static double Distance2D(const LineSeg& seg1, const LineSeg& seg2) {
        if(LineSeg::Intersect(seg1, seg2)) return 0;
        double d1 = LineSeg::Distance(seg2, seg1.p1);
        double d2 = LineSeg::Distance(seg2, seg1.p2);
        double d3 = LineSeg::Distance(seg1, seg2.p1);
        double d4 = LineSeg::Distance(seg1, seg2.p2);

        return std::min({d1, d2, d3, d4});
    }

    static double Distance3D(const LineSeg& seg1, const LineSeg& seg2) {
        Vec3 u = seg1.p2 - seg1.p1;
        Vec3 v = seg2.p2 - seg2.p1;
        Vec3 w = seg1.p1 - seg2.p1;

        double a = u*u;
        double b = u*v;
        double c = v*v;
        double d = u*w;
        double e = v*w;
        double D = a * c - b * b;

        double sc, sN, sD = D;
        double tc, tN, tD = D;

        const double EPS = 1e-8;

        if (D < EPS) {
            sN = 0.0;
            sD = 1.0;
            tN = e;
            tD = c;
        } else {
            sN = (b * e - c * d);
            tN = (a * e - b * d);
            if (sN < 0.0) {
                sN = 0.0;
                tN = e;
                tD = c;
            } else if (sN > sD) {
                sN = sD;
                tN = e + b;
                tD = c;
            }
        }

        if (tN < 0.0) {
            tN = 0.0;
            if (-d < 0.0)
                sN = 0.0;
            else if (-d > a)
                sN = sD;
            else {
                sN = -d;
                sD = a;
            }
        } else if (tN > tD) {
            tN = tD;
            if ((-d + b) < 0.0)
                sN = 0;
            else if ((-d + b) > a)
                sN = sD;
            else {
                sN = (-d + b);
                sD = a;
            }
        }

        sc = (abs(sN) < EPS ? 0.0 : sN / sD);
        tc = (abs(tN) < EPS ? 0.0 : tN / tD);

        Vec3 dP = w + u * sc - v * tc;  // Closest vector between points
        return dP.Length();
    }

    static double Distance(const LineSeg& seg, const Vec3& q) {
        Vec3 A = seg.p1;
        Vec3 B = seg.p2;
    
        Vec3 AB = B - A;
        Vec3 AQ = q - A;
    
        double AB_AB = AB*AB;
        double AQ_AB = AQ*AB;
    
        double t = std::min(std::max(AQ_AB / AB_AB, 0.0), 1.0);
        Vec3 closestPoint = Vec3(A.x + t*AB.x, A.y + t*AB.y, A.z + t*AB.z);
        Vec3 diff = Vec3(q.x, q.y, q.z) - closestPoint;
        return diff.Length();
    }

private:
    static bool onSegment(const Vec3& p1, const Vec3& p2, const Vec3& p3) {
        return (p3.x <= std::max(p1.x, p2.x) && p3.x >= std::min(p1.x, p2.x) && p3.y <= std::max(p1.y, p2.y) && p3.y >= std::min(p1.y, p2.y));
    }

public:

    static bool Intersect(const LineSeg& seg1, const LineSeg& seg2) {
        int o1 = Vec3::Orientation(seg1.p1, seg1.p2, seg2.p1);
        int o2 = Vec3::Orientation(seg1.p1, seg1.p2, seg2.p2);
        int o3 = Vec3::Orientation(seg2.p1, seg2.p2, seg1.p1);
        int o4 = Vec3::Orientation(seg2.p1, seg2.p2, seg1.p2);
    
        if(o1 != o2 && o3 != o4) return true;
    
        if(o1 == 0 && onSegment(seg1.p1, seg1.p2, seg2.p1)) return true;
        if(o2 == 0 && onSegment(seg1.p1, seg1.p2, seg2.p2)) return true;
        if(o3 == 0 && onSegment(seg2.p1, seg2.p2, seg1.p1)) return true;
        if(o4 == 0 && onSegment(seg2.p1, seg2.p2, seg1.p2)) return true;
    
        return false;
    }
};


struct Plane {
    Vec3 point;  
    Vec3 normal;

    Plane() = default;
    Plane(const Vec3& point, const Vec3& normal)
        : point(point), normal(normal) {}
    
    Plane(const Vec3& a, const Vec3& b, const Vec3& c) {
        this->normal = ((b - a)^(c - a)); //.Norm();
        this->point = a;
    }

    double SignedDistance(const Vec3& p) const {
        return (p - point) * normal;
    }

    double Distance(const Vec3& p) const {
        return abs(SignedDistance(p));
    }

    Vec3 Project(const Vec3& p) const {
        return p - normal * SignedDistance(p);
    }

    // Check which half-space the point lies in
    // Returns:
    //   > 0: point is above the plane (in direction of normal)
    //   = 0: point is on the plane
    //   < 0: point is below the plane
    double HalfSpace(const Vec3& p) const {
        return SignedDistance(p);
    }

    // Reflect a point across the plane
    Vec3 Reflect(const Vec3& p) const {
        return p - normal * (2 * SignedDistance(p));
    }
};


struct HitInfo {
    bool hitted;
    Vec3 i1, i2;
    HitInfo(bool hitted = false, const Vec3& i1 = {0,0,0}, const Vec3& i2 = {0,0,0}):
        hitted(hitted), i1(i1), i2(i2) {}
};

struct Sphere {
    Vec3 origin;
    double radius;

    Sphere(const Vec3& origin, double radius) : origin(origin), radius(radius) {}
};

struct Circle {
    Vec3 center = {};
    double radius = 0;
    
    Circle(Vec3 center = {}, double radius = 1) : center(center), radius(radius) {}
    Circle(Vec3 A, Vec3 B, Vec3 C) {
        B = B-A; 
        C = C-A;

        double d = 2*(B^C).z;
        if(abs(d) < 1e-7) return;
        this->center = {
            C.y*(B.x*B.x + B.y*B.y) - B.y*(C.x*C.x + C.y*C.y),
            B.x*(C.x*C.x + C.y*C.y) - C.x*(B.x*B.x + B.y*B.y),
            0
        };
        center = center/d;

        this->radius = sqrt(center.x*center.x + center.y*center.y);
        center = center + A;
    }

private:
    static Circle TrivialCircle(const std::vector<Vec3>& R) {
        if(R.size() == 1) return {R[0], 0};
        if(R.size() == 2) {
            Vec3 c = R[0].Lerp(R[1], 0.5);
            return {c, Vec3::Distance(R[0], c)};
        }
        if(R.size() == 3) return Circle(R[0], R[1], R[2]);
        
        return {{0,0,0}, 0};
    }

    static Circle Welzl(std::vector<Vec3>& P, std::vector<Vec3> R, int n) {
        if(n == 0 || R.size() == 3)
            return Circle::TrivialCircle(R);
        
        // Remove random point
        int rIdx = rand() % n;
        Vec3 p = P[rIdx];
        P[rIdx] = P[n-1];
        P[n-1] = p;

        Circle D = Circle::Welzl(P, R, n-1);
        if(D.Contains(p)) return D;

        R.push_back(p);
        return Circle::Welzl(P, R, n-1);
    }
    
public:

    static Circle MEC(std::vector<Vec3>& points) {
        return Circle::Welzl(points, {}, points.size());
    }

    static HitInfo iCircle(const Circle& c1, const Circle& c2) {
        HitInfo result = {};
        Vec3 d = c2.center - c1.center;
        double dist = d.Length();

        // No intersection: circles are separate or one is completely inside the other
        if (dist > c1.radius + c2.radius || dist < abs(c1.radius - c2.radius) || abs(dist) < 1e-8)
            return result;

        result.hitted = true;

        // Distance from c1.center to the midpoint along the line between centers
        float a = (c1.radius * c1.radius - c2.radius * c2.radius + dist * dist) / (2 * dist);
        float h = sqrt(c1.radius * c1.radius - a * a);

        Vec3 mid = c1.center + d * (a / dist);  // Point along the line between centers

        // Perpendicular offset for the intersection points
        Vec3 offset = Vec3{-d.y, d.x} * (h / dist);

        result.i1 = mid + offset;
        result.i2 = mid - offset;

        return result;
    }

    std::vector<Ray> Tangents(const Vec3& origin) {
        Vec3 toCircle = this->center - origin;
        double distSqr = toCircle.SqrLength();

        // No tangent if origin is inside or on the circle
        if (distSqr <= this->radius * this->radius) return {};

        double dist = sqrt(distSqr);
        double angle = asin(this->radius / dist);
        Vec3 dirToCenter = toCircle.Norm();
        Vec3 perp = {-dirToCenter.y, dirToCenter.x, 0};
        double cosA = cos(angle), sinA = sin(angle);

        Vec3 dir1 = dirToCenter * cosA + perp * sinA;
        Vec3 dir2 = dirToCenter * cosA - perp * sinA;

        return { {origin, dir1}, {origin, dir2} };
    }

    bool isAtEdge(const Vec3& p) const {
        double eps = 1e-7;
        return (abs(Vec3::SqrDistance(p, center)-(radius*radius)) < eps);
    }

    bool Contains(const Vec3& p) const {
        return Vec3::SqrDistance(p, center) <= radius*radius;
    }

    double Area() const {
        return PI*radius*radius;
    }

    double CLen() const {
        return 2*PI*radius;
    }

    inline void Print() const {
        printf("(%.2lf, %.2lf, %.2lf) - r: %.2lf\n", this->center.x, this->center.y, this->center.z, this->radius);
    }
};

struct Ray {
    Vec3 origin, dir;

    Ray(const Vec3& pO, const Vec3& pD) : origin(pO) {
        this->dir = (pD-pO);//.Norm();
    }

    static bool iSphere(const Ray& ray, const Sphere& sph) {
        Vec3 oc = ray.origin - sph.origin;
	
        double b = (oc*ray.dir);
        double c = (oc*oc) - sph.radius * sph.radius;
        double h = b*b - c;

        if(h >= 0) {
            double d1 = -b - sqrt(h) + 1e-4, d2 = -b + sqrt(h) + 1e-4;
            if(d1 < 0 || d2 < 0) return false;
        }
        else return false;
        return true;
    }

    static HitInfo iCircle(const Ray& ray, const Circle& circle) {
        Vec3 od = (ray.origin - circle.center);
        double /*A = 1,*/ B = od*2*ray.dir, C = od.SqrLength() - circle.radius*circle.radius;
        double D = B*B - 4*C;
        
        double t1 = (D >= 0 ? (-B - sqrt(D))/2 : 0), t2 = (D >= 0 ? (-B + sqrt(D))/2 : 0);
        return {D >= 0 && t1 >= 0, ray.origin + ray.dir*t1, ray.origin + ray.dir*t2};
    }

    Vec3 iEllipse(int A, int B) {
        Vec3 ocn = {origin.x/A, origin.y/B};
        Vec3 rdn = {dir.x/A, dir.y/B};
        double a = rdn*rdn;
        double b = ocn*rdn;
        double c = ocn*ocn;
        double h = b*b - a*(c-1.0);
        if( h < 0.0 ) return Vec3(0.0);
        h = sqrt(h);
        double t1 = (-b-h)/a;
        double t2 = (-b+h)/a;
        if( std::max(t1, t2) < 0.0 ) return Vec3(0.0);
        double t = (t1 > 0.0) ? t1 : t2;
        return origin + dir*t;
    }
    
    static HitInfo iPlane(const Ray& ray, const Plane& plane) {
        double d = ray.dir * plane.normal;
        if(fabs(d) <= 1e-6) return {false, {}, {}};
        Vec3 diff = plane.point - ray.origin;
        double t = diff * plane.normal / d;
        return {true, ray.origin + ray.dir*t, {}};
    }
};

// Requires all points to be coplanar
bool isInsideTriangle3D(const std::array<Vec3, 3>& tri, const Vec3& p) {
    Vec3 v0 = tri[1] - tri[0];
    Vec3 v1 = tri[2] - tri[0];
    Vec3 v2 = p - tri[0];

    double d00 = v0*v0;
    double d01 = v0*v1;
    double d11 = v1*v1;
    double d20 = v2*v0;
    double d21 = v2*v1;

    double denom = d00 * d11 - d01 * d01;
    if (abs(denom) < 1e-10)
        // Triangle is degenerate
        return false;

    double v = (d11 * d20 - d01 * d21) / denom;
    double w = (d00 * d21 - d01 * d20) / denom;
    double u = 1.0 - v - w;

    const double EPS = 1e-8;
    return u >= -EPS && v >= -EPS && w >= -EPS;
}

bool isInsideTriangle(const std::array<Vec3, 3>& tri, const Vec3& p) {
    double area = abs((tri[1].x - tri[0].x) * (tri[2].y - tri[0].y) - (tri[2].x - tri[0].x) * (tri[1].y - tri[0].y))/2;    
    double area1 = abs((tri[0].x - p.x) * (tri[1].y - p.y) - (tri[1].x - p.x) * (tri[0].y - p.y))/2;
    double area2 = abs((tri[1].x - p.x) * (tri[2].y - p.y) - (tri[2].x - p.x) * (tri[1].y - p.y))/2;
    double area3 = abs((tri[2].x - p.x) * (tri[0].y - p.y) - (tri[0].x - p.x) * (tri[2].y - p.y))/2;
    return abs(area - (area1 + area2 + area3)) < 1e-8;
}

struct Polygon {
    int v;
    std::vector<Vec3> points;

    Polygon(int v = 0, const std::vector<Vec3>& points = std::vector<Vec3>()) : v(v), points(points) {}
    Polygon(const std::vector<Vec3>& points = std::vector<Vec3>()) : v(points.size()), points(points) {}

    double Area() {
        double s = 0;
        for(int i = 0; i < this->v; i++) {
            s += this->points[i].x * this->points[(i+1)%v].y;
            s -= this->points[i].y * this->points[(i+1)%v].x;
        }
        
        return abs(s/2);
    }

    bool isConvex() {
        if(this->v <= 3) return true;
        
        this->RadialSort();

        bool sign = false;
        for(int i = 0; i < this->v; i++) {
            double zCross = ((points[i]-points[(i+1)%v]) ^ (points[(i+2)%v]-points[(i+1)%v])).z;
            
            if(i == 0) sign = (zCross > 0);
            else if(sign != (zCross > 0)) return false; 
        }

        return true;
    }

    double Distance(const Vec3& p) {
        if(this->v < 3) return 0;
        this->RadialSort();
        double minDist = INF;
        for(int i = 0; i < this->v; i++) {
            Vec3 p1 = this->points[i], p2 = this->points[(i+1)%this->v];
            double d = LineSeg::Distance(LineSeg(p1, p2), p);
            if(d < minDist) minDist = d;
        }
        return minDist;
    }
    
    bool ContainsInside(const Vec3& p) {
        if(this->v < 3) return false;
        this->RadialSort();
        bool inside = false;
 
        for(int i = 1; i <= this->v; i++) {
            Vec3 p1 = this->points[i-1], p2 = this->points[i%this->v];
            if(Vec3::Orientation(p1, p2, p) == 0 && std::min(p1.x, p2.x) <= p.x && p.x <= std::max(p1.x, p2.x) && std::min(p1.y, p2.y) <= p.y && p.y <= std::max(p1.y, p2.y)) return true;
            if((p1.x <= p.x && p.x < p2.x && Vec3::Orientation(p, p1, p2) < 0) || (p2.x <= p.x && p.x < p1.x && Vec3::Orientation(p, p2, p1) < 0))
                inside = !inside;
        }
 
        return inside;
    }

    std::vector<Vec3> ConvexHull(bool includeCollinear = false) {
        if(this->v < 3) return std::vector<Vec3>();
        this->RadialSort();

        if(includeCollinear) {
            int i = this->v-1;
            while (i >= 0 && Vec3::Orientation(this->points[0], this->points[i], this->points.back()) == 0) 
                i--;
            std::reverse(points.begin()+i+1, points.end());
        }

        std::vector<Vec3> hull = std::vector<Vec3>();

        for(int i = 0; i < this->v; i++) {
            while(hull.size() > 1 && Vec3::Orientation(hull[hull.size()-2], hull.back(), this->points[i]) < (1-includeCollinear)) 
                hull.pop_back();
            hull.push_back(this->points[i]);
        }

        return hull;
    }

private:
    void RadialSort(bool clockwise = false) {
        auto minPointIt = std::min_element(points.begin(), points.end(),
            [](const Vec3& a, const Vec3& b) {
                return (a.y < b.y) || (a.y == b.y && a.x < b.x);
            });
        Vec3 pivot = *minPointIt;

        std::sort(points.begin(), points.end(), [pivot, clockwise](const Vec3& lhs, const Vec3& rhs) {
            int o = Vec3::Orientation(pivot, lhs, rhs);
            if (o == 0) return Vec3::SqrDistance(pivot, lhs) < Vec3::SqrDistance(pivot, rhs);
            return (clockwise ? (o < 0) : (o > 0)); // Sort in counter-clockwise order
        });
    }
};