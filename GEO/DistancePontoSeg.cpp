double cross(Point A, Point B, Point C) {
    return (B.first - A.first) * (C.second - A.second) - (B.second - A.second) * (C.first - A.first);
}

double dot(Point A, Point B, Point C) {
    return (B.first - A.first) * (C.first - A.first) + (B.second - A.second) * (C.second - A.second);
}

double dist(Point A, Point B) {
    return hypot(A.first - B.first, A.second - B.second);
}

double pointSegmentDist(Point A, Point B, Point P) {
    double proj = dot(A, B, P) / dot(A, B, B);
    if (proj < 0.0) return dist(A, P); 
    if (proj > 1.0) return dist(B, P);

    double crossProd = abs(cross(A, B, P)) / dist(A, B);
    return crossProd;
}