//Complexidade: O(log n)
//Fib(Fib(n)) mod m  = Fib(Fib(n) mod Pisano(m) ) mod m
//F(i)%mod = F(i)%pi(mod)
//Existe um resto zero até 6*n
//pi(n) <= 6*n
ll pisano(ll m){
    ll a = 1;
    ll b = 1;
    ll ans = 1;
    
    while (1){
        ll temp = b % m;
        b = (a + b) % m;
        a = temp;
        ++ans;
        
        if (a == 1 && b == 1) return ans - 1;
    }
}