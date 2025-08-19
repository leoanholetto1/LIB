#include <array>
#include <vector>

// O(nm)
constexpr int sz = 5e2+1;
int h, w;
std::array<int, 5> maxArea(bool mat[sz][sz]) {
    std::vector<int> height(w, 0);
    int maxArea = 0;
    int top = -1, left = -1, bottom = -1, right = -1;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
            if (mat[i][j]) height[j]++;
            else height[j] = 0;

        std::vector<int> stk;
        std::vector<int> l(w), r(w, w);

        for (int j = 0; j < w; ++j) {
            while (!stk.empty() && height[stk.back()] >= height[j])
                stk.pop_back();
            l[j] = stk.empty() ? -1 : stk.back();
            stk.push_back(j);
        }

        while (!stk.empty()) stk.pop_back();

        for (int j = w - 1; j >= 0; --j) {
            while (!stk.empty() && height[stk.back()] >= height[j])
                stk.pop_back();
            r[j] = stk.empty() ? w : stk.back();
            stk.push_back(j);
        }

        for (int j = 0; j < w; ++j) {
            int width = r[j] - l[j] - 1;
            int area = height[j] * width;

            if (area <= maxArea) continue;
            maxArea = area;
            bottom = i;
            top = i - height[j] + 1;
            left = l[j] + 1;
            right = r[j] - 1;
        }
    }
 
    return {maxArea, top, left, bottom, right};
}