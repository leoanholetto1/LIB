//Complexidade: O(1)
bool ver(Point P, Point A1, Point B1, Point A2, Point B2) {
    ll a1 = B1.y - A1.y;
    ll b1 = A1.x - B1.x;
    ll c1 = a1 * A1.x + b1 * A1.y;
    ll a2 = B2.y - A2.y;
    ll b2 = A2.x - B2.x;
    ll c2 = a2 * A2.x + b2 * A2.y;
    ll d1 = a1 * P.x + b1 * P.y - c1;
    ll d2 = a2 * P.x + b2 * P.y - c2;
    return (d1 * d2 < 0);
}