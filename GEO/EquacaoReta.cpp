//Complexidade: O(1)
Reta EquacaoGeralDaReta(double x1, double y1, double x2, double y2) {
    Reta r;
    r.a = y2 - y1;
    r.b = x1 - x2;
    r.c = x2 * y1 - x1 * y2;
    return r;
}