#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 998244353;

ll mod_pow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }
    return res;
}

vector<int> mobius(int n) {
    vector<int> mu(n + 1, 1);
    vector<bool> is_prime(n + 1, true);
    for (int p = 2; p <= n; ++p) {
        if (is_prime[p]) {
            for (int i = p; i <= n; i += p) {
                is_prime[i] = false;
                mu[i] *= -1;
            }
            for (int i = p*p; i <= n; i += p*p)
                mu[i] = 0;
        }
    }
    return mu;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    vector<int> a(n-1);
    for (auto &x : a) cin >> x;
    
    map<int, vector<int>> prime_factors;
    for (int x : a) {
        int t = x;
        for (int p = 2; p*p <= t; ++p) {
            if (t % p == 0) {
                int cnt = 0;
                while (t % p == 0) {
                    t /= p;
                    ++cnt;
                }
                prime_factors[p].push_back(cnt);
            }
        }
        if (t > 1) {
            prime_factors[t].push_back(1);
        }
    }
    
    ll product = 1;
    for (int i = 0; i < n-1; ++i) {
        product = product * mod_pow(a[i], n-1 - i) % MOD;
    }
    
    auto mu = mobius(1e6);
    ll ans = 0;
    
    vector<int> divisors = {1};
    for (auto &[p, cnts] : prime_factors) {
        vector<int> new_divisors;
        for (int d : divisors) {
            new_divisors.push_back(d);
            new_divisors.push_back(d * p);
        }
        swap(divisors, new_divisors);
    }
    
    for (int d : divisors) {
        if (d == 1) continue;
        bool valid = true;
        for (int x : a) {
            if (x % d != 0) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;
        int cnt = 0;
        for (int x : a) {
            int t = x;
            while (t % d == 0) {
                t /= d;
                ++cnt;
            }
        }
        ll ways = mod_pow(2, cnt);
        ans = (ans + mu[d] * ways) % MOD;
    }
    
    ans = (ans * product) % MOD;
    if (ans < 0) ans += MOD;
    cout << ans << endl;
    
    return 0;
}