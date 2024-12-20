int BIT[maxN][maxN];
int n;
//Complexidade: O(log n x log n)
void updateBIT(int x, int y, int val){
    for (; x <= n; x += (x & -x)){
        for (int yy=y; yy <= n; yy += (yy & -yy))
            BIT[x][yy] += val;
    }
}
//Complexidade: O(log n x log )
int getSum(int x, int y){
    int sum = 0;
    for(; x > 0; x -= x&-x){
        for(int yy=y; yy > 0; yy -= yy&-yy){
            sum += BIT[x][yy];
        }
    }
    return sum;
}
//Complexidade: O(log n x log n)
int getInterval(int x1,int y1,int x2,int y2){
    return getSum(x2, y2)-getSum(x2, y1-1)-getSum(x1-1, y2)+getSum(x1-1, y1-1);
}