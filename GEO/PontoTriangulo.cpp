//Complexidade: O(1)
double prodVet(pii A, pii B, pii P) {
    return (B.f - A.f) * (P.s - A.s) - (B.s - A.s) * (P.f - A.f);
}
bool pontoDentro(pii a,pii b,pii c,pii p) {
    int cross1 = prodVet(a, b, p);
    int cross2 = prodVet(b, c, p);
    int cross3 = prodVet(c, a, p);
    return (cross1 >= 0 && cross2 >= 0 && cross3 >= 0) || (cross1 <= 0 && cross2 <= 0 && cross3 <= 0);
}
