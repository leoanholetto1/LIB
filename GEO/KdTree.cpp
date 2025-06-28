// Fast
using ll = long long;
 
template<class T, int d>
struct pt {
    array<T, d> p;
    bool operator!=(const pt &o) const { return p != o.p; }
    T dist(const pt &o) const {
        T res = 0;
        for (int i = 0; i < d; i++)
            res += abs(p[i] - o.p[i]);
        return res;
    }
};

template<class pt, class T, int d>
struct kd_tree {
    struct node {
        int ax;
        T val;
        pt point;
        node *izq, *der;
        array<T, d> min_bounds, max_bounds;
    };
    node *root;
 
    T minimal_distance(const pt &q, const array<T, d> &minb, const array<T, d> &maxb) {
        T dist = 0;
        for (int i = 0; i < d; i++) {
            if (q.p[i] < minb[i])
                dist += minb[i] - q.p[i];
            else if (q.p[i] > maxb[i])
                dist += q.p[i] - maxb[i];
        }
        return dist;
    }
 
    node *build_tree(vector<pt> &a, int l, int r) {
        if (l > r) return nullptr;
        node *cur = new node();
        array<T, d> minb, maxb;
        for (int i = 0; i < d; i++) {
            minb[i] = a[l].p[i];
            maxb[i] = a[l].p[i];
        }
        for (int j = l + 1; j <= r; j++) {
            for (int i = 0; i < d; i++) {
                if (a[j].p[i] < minb[i])
                    minb[i] = a[j].p[i];
                if (a[j].p[i] > maxb[i])
                    maxb[i] = a[j].p[i];
            }
        }
        cur->min_bounds = minb;
        cur->max_bounds = maxb;
 
        int ax = 0;
        T best_spread = 0;
        for (int i = 0; i < d; i++) {
            T spread = maxb[i] - minb[i];
            if (spread > best_spread) {
                best_spread = spread;
                ax = i;
            }
        }
        cur->ax = ax;
 
        int mid = (l + r) / 2;
        nth_element(a.begin() + l, a.begin() + mid, a.begin() + r + 1, [ax](const pt &x, const pt &y) {
            return x.p[ax] < y.p[ax];
        });
        cur->point = a[mid];
        cur->val = a[mid].p[ax];
 
        cur->izq = build_tree(a, l, mid - 1);
        cur->der = build_tree(a, mid + 1, r);
        return cur;
    }
 
    kd_tree(vector<pt> &a) {
        root = build_tree(a, 0, a.size() - 1);
    }
 
    void query(node *cur, const pt &q, T &ans) {
        if (cur == nullptr) return;
 
        if (q != cur->point) {
            T d_here = q.dist(cur->point);
            if (d_here < ans)
                ans = d_here;
        } else {
            ans = min(ans, (T)0);
        }
 
        vector<pair<T, node *>> children;
        if (cur->izq) {
            T d_left = minimal_distance(q, cur->izq->min_bounds, cur->izq->max_bounds);
            children.push_back({d_left, cur->izq});
        }
        if (cur->der) {
            T d_right = minimal_distance(q, cur->der->min_bounds, cur->der->max_bounds);
            children.push_back({d_right, cur->der});
        }
 
        sort(children.begin(), children.end(), [](const auto &a, const auto &b) {
            return a.first < b.first;
        });
 
        for (auto &[d_val, child] : children) {
            if (d_val < ans) {
                query(child, q, ans);
            }
        }
    }
 
    T query(const pt &q) {
        T ans = numeric_limits<T>::max();
        query(root, q, ans);
        return ans;
    }
};

// KNN
#include <stdio.h>
#include <math.h>
#include <queue>
#include <algorithm>

// Credits: https://codeforces.com/blog/entry/5930?#comment-266157

struct Point {
	int x, y;
	Point(int x = 0, int y = 0): x(x), y(y) {}	
};

double dist(const Point& p1, const Point& p2) {
    int dx = (p1.x-p2.x);
    int dy = (p1.y-p2.y);
    return sqrt(dx*dx + dy*dy);
}

// the "hyperplane split", use comparators for all dimensions
bool cmpx(const Point& a, const Point& b) {return a.x < b.x;}
bool cmpy(const Point& a, const Point& b) {return a.y < b.y;}

class KDTree2D {
	Point* tree;
	int n;

public:

	KDTree2D(Point points[], int n): tree(new Point[n]), n(n) {
		std::copy(points, points + n, tree);
		Build(0, n, false);
	}

	~KDTree2D() { delete[] tree; }

	// k-nearest neighbor query, O(k log(k) log(n)) on average
	std::vector<Point> QueryKNN(const Point& p, int k = 1) {
		while (!maxHeap.empty()) maxHeap.pop(); // Clear heap for next query
		GetKNN(p, k, 0, n, false);
		std::vector<Point> points;
		while (!maxHeap.empty()) {
			points.push_back(*maxHeap.top().second);
			maxHeap.pop();
		}
		std::reverse(points.begin(), points.end());
		return points;
	}

private:
	// build is O(n log n) using divide and conquer
	void Build(int L, int R, bool axis) {
		if (L >= R) return;
		int M = (L + R) / 2;
		// get median in O(n), split x-coordinate if dvx is true
		std::nth_element(tree+L, tree+M, tree+R, axis ? cmpx : cmpy);
		Build(L, M, !axis); 
        Build(M+1, R, !axis);
	}

	// priority queue for KNN, keep the K nearest
	std::priority_queue<std::pair<double, Point*>> maxHeap;
	void GetKNN(const Point& p, int k, int L, int R, bool axis) {
		if (L >= R) return;
		int M = (L + R) >> 1;
		double dx = p.x - tree[M].x;
		double dy = p.y - tree[M].y;
		double delta = axis ? dx : dy;
		double sqrDist = dx * dx + dy * dy;

		// if point is nearer to the kth farthest, put point in queue
		if (maxHeap.size() < k || sqrDist < maxHeap.top().first) {
			maxHeap.push(std::make_pair(sqrDist, &tree[M]));
			if (maxHeap.size() > k) maxHeap.pop(); // keep k elements only
		}

		int nearL = L, nearR = M, farL = M + 1, farR = R;
		if (delta > 0) { // right is nearer
			std::swap(nearL, farL);
			std::swap(nearR, farR);
		}
        
        // Query the nearer child
		GetKNN(p, k, nearL, nearR, !axis);

		if (maxHeap.size() < k || delta * delta < maxHeap.top().first) // Query the farther child if there might be candidates
			GetKNN(p, k, farL, farR, !axis);
	}
};