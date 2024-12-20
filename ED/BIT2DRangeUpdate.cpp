//Complexidade: O(log n x log n)
void update(vector<vector<int>>& bit, int x, int y, int delta) {
    int rows = bit.size() - 1;
    int cols = bit[0].size() - 1;
    while (x <= rows) {
        int y1 = y;
        while (y1 <= cols) {
            bit[x][y1] += delta;
            y1 += y1 & -y1;
        }
        x += x & -x;
    }
}
//Complexidade: O(log n x log n)
//Range Update
void range_update(vector<vector<int>>& bit, int x1, int y1, int x2, int y2, int delta) {
    update(bit, x1, y1, delta);
    update(bit, x1, y2 + 1, -delta);
    update(bit, x2 + 1, y1, -delta);
    update(bit, x2 + 1, y2 + 1, delta);
}
//Complexidade: O(log n x log x)
//Consulta de Ponto
int query(const vector<vector<int>>& bit, int x, int y) {
    int result = 0;
    while (x > 0) {
        int y1 = y;
        while (y1 > 0) {
            result += bit[x][y1];
            y1 -= y1 & -y1;
        }
        x -= x & -x;
    }
    return result;
}
//Complexidade: O(log n x log n)
void range_update_radius(vector<vector<int>>& bit, int x, int y, int radius, int delta) {
    int rows = bit.size() - 1;
    int cols = bit[0].size() - 1;
    int x1 = max(1, x - radius);
    int y1 = max(1, y - radius);
    int x2 = min(rows, x + radius);
    int y2 = min(cols, y + radius);
    range_update(bit, x1, y1, x2, y2, delta);
}

vector<vector<int>> bit(n + 1, vector<int>(m + 1, 0));