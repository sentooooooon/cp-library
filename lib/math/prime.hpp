// ===== 素数・約数 =====
// 【使い方】
//   is_prime(97)          // true。O(√n)
//   divisors(12)          // {1, 2, 3, 4, 6, 12}。O(√n)
//   factorize(12)         // {{2, 2}, {3, 1}}  → 12 = 2^2 × 3^1。O(√n)
//
//   たくさんの数を判定・分解したいとき（n ≦ 10^7 くらい）は篩（ふるい）:
//   Sieve sv(1000000);
//   sv.is_prime[x]        // x が素数か
//   sv.primes             // 1000000 以下の素数のリスト
//   sv.factorize(x)       // x を素因数分解（とても速い）

bool is_prime(long long n) {
    if(n < 2) return false;
    for(long long i = 2; i * i <= n; i++)
    {
        if(n % i == 0) return false;
    }
    return true;
}

vector<long long> divisors(long long n) {
    vector<long long> res;
    for(long long i = 1; i * i <= n; i++)
    {
        if(n % i == 0)
        {
            res.push_back(i);
            if(i != n / i) res.push_back(n / i);
        }
    }
    sort(res.begin(), res.end());
    return res;
}

vector<pair<long long, int>> factorize(long long n) {
    vector<pair<long long, int>> res;
    for(long long p = 2; p * p <= n; p++)
    {
        if(n % p != 0) continue;
        int cnt = 0;
        while(n % p == 0)
        {
            n /= p;
            cnt++;
        }
        res.push_back({p, cnt});
    }
    if(n > 1) res.push_back({n, 1});
    return res;
}

struct Sieve {
    vector<bool> is_prime;
    vector<int> min_factor;  // min_factor[x] = x を割り切る最小の素数
    vector<int> primes;

    Sieve(int n) {
        is_prime.assign(n + 1, true);
        min_factor.assign(n + 1, 0);
        is_prime[0] = false;
        if(n >= 1) is_prime[1] = false;
        for(int i = 2; i <= n; i++)
        {
            if(!is_prime[i]) continue;
            primes.push_back(i);
            min_factor[i] = i;
            for(long long j = (long long)i * i; j <= n; j += i)
            {
                if(is_prime[j])
                {
                    is_prime[j] = false;
                    min_factor[j] = i;
                }
            }
        }
    }

    vector<pair<int, int>> factorize(int x) {
        vector<pair<int, int>> res;
        while(x > 1)
        {
            int p = min_factor[x];
            int cnt = 0;
            while(x % p == 0)
            {
                x /= p;
                cnt++;
            }
            res.push_back({p, cnt});
        }
        return res;
    }
};
