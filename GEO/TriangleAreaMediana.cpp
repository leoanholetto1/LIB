//Complexidade: O(1)
void area(int a,int b,int c){
    double s=(a+b+c)/2.0;
    double valor = s*(s-a)*(s-b)*(s-c);	
    if(valor <= 0.0) printf("-1.000\n");
    else  printf("%.3lf\n",4.0*(sqrt(valor) + 1e-9)/3.0);
}