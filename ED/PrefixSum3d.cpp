//Complexidade: O(n^3)
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        for(int p=1;p<=n;p++){
            cin>>x;
            sumP[i][j][p] = sumP[i - 1][j][p] + sumP[i][j - 1][p] + sumP[i][j][p - 1] 
                        - sumP[i - 1][j - 1][p] - sumP[i][j - 1][p - 1] - sumP[i - 1][j][p - 1] 
                        + sumP[i - 1][j - 1][p - 1] + x;
        }
    }
}
//Complexidade: O(1)
ll query(int x1, int y1, int x2, int y2, int x3, int y3) {
    return sumP[y1][y2][y3] - sumP[x1 - 1][y2][y3] - sumP[y1][x2 - 1][y3] + sumP[x1 - 1][x2 - 1][y3] - 
	(sumP[y1][y2][x3 - 1] - sumP[x1 - 1][y2][x3 - 1] - sumP[y1][x2 - 1][x3 - 1] + sumP[x1 - 1][x2 - 1][x3 - 1]);
}