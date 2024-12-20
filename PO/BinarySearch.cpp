//Complexidade: O(log n)
//Joga para esquerda
int i=0,f=tl-1;
while(i<=f){
    m = (i+f)/2;
    if(p[m]>=l){
        k1=m;
        f = m-1;
    }
    else i = m+1; 
}
//Joga para direita
int i=0,f=tl-1;
while(i<=f){
    m = (i+f)/2;
    if(p[m]<=r){
        k2=m;
        i = m+1;
    }
    else f = m-1; 
}
//Bisection
for(int i=0;i<n;i++){
    double m = (i+f)/2.0;
    if(val(m)) f = m;
    else i = m;
}
//Funções Unimodal
int i=0,f=1e9,ans,m;
while(i<=f){
    m = (i+f)/2;
    if(val(m)){
        ans = m;//depende se quiser o min ou o max
        f = m-1;
    }
    else i = m+1;
}