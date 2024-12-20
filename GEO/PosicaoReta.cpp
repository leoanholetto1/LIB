//Complexidade: O(1)
int verifica(double x1,double y1,double x2,double y2,double x3,double y3){
    x1 = x3-x1; y1 = y3 - y1;
    x2 = x3-x2; y2 = y3 - y2;
    double p = x1*y2-x2*y1;
     if(p > 0) return 1;
    else if(p < 0) return -1;
    else return 0;
}