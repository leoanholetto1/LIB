//Complexidade: O(log n)
long long lcm(int a, int b) { 
    return (a / gcd(a, b)) * b; 
} 