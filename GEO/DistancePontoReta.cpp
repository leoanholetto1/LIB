//Complexidade: O(1)
double dist(Reta r,double x,double y){
    return abs(r.a*x + r.b*y + r.c)/sqrt(r.a*r.a+r.b*r.b);
}