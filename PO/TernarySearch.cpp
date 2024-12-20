//Complexidade: O(log n)
double ternary_search(double l, double r) {
    double eps = 1e-9;             
    while (r - l > eps) { //(t--) -> onde t eh fixo t>=500
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double f1 = f(m1);
        double f2 = f(m2);      
        if (f1 < f2) //inverte se for minimo
            l = m1;
        else
            r = m2;
    }
    return f(l);
}