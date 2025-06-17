#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>

#ifdef BOJ // 백준 채점환경
constexpr bool local = false;
#else // 로컬
constexpr bool local = true;
#endif

#define FAST_IO                       \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);
#define debug            \
    if constexpr (local) \
    std::cout
#define endl "\n"

using namespace std;

typedef unsigned long long i64;

void solution(i64 n);
vector<i64> sieve_of_eratosthenes(i64 n);
unordered_set<i64> find_factors(i64 n);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
    {
        (void)!freopen("./input.txt", "r", stdin);
        debug << "\n";
    }

    i64 n;
    cin >> n;

    solution(n);
    return 0;
}

void solution(i64 n)
{
    unordered_set<i64> factors = find_factors(n);

    for (i64 factor : factors)
        n -= n / factor;
    cout << n;
}

unordered_set<i64> find_factors(i64 n)
{
    vector<i64> primes = sieve_of_eratosthenes(1 + i64(sqrt(n)));
    unordered_set<i64> factors;

    for (i64 prime : primes)
        while (n % prime == 0)
        {
            n /= prime;
            factors.insert(prime);
        }

    if (n > 1)
        factors.insert(n);

    return factors;
}

vector<i64> sieve_of_eratosthenes(i64 n)
{
    vector<i64> primes = {2};
    vector<bool> is_prime(n, true);
    is_prime[0] = false;
    is_prime[1] = false;

    for (i64 p = 2; p * p <= n; p++)
        if (is_prime[p])
            for (i64 i = p * p; i <= n; i += p)
                is_prime[i] = false;

    for (i64 i = 3; i <= n; i += 2)
        if (is_prime[i])
            primes.push_back(i);

    return primes;
}