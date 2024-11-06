#include <iostream>
#include <vector>
#include <cmath>

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

vector<i64> sieve_of_eratosthenes(i64 B);
void solution(i64 A, i64 B);
int log_p_N(i64 prime, i64 N);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
    {
        (void)!freopen("./input.txt", "r", stdin);
        debug << "\n";
    }

    i64 A, B;
    cin >> A >> B;

    solution(A, B);
    return 0;
}

void solution(i64 A, i64 B)
{
    int almost_prime = 0;
    vector<i64> primes = sieve_of_eratosthenes(B);
    for (i64 prime : primes)
        almost_prime += (log_p_N(prime, B) - log_p_N(prime, A - 1));

    cout << almost_prime;
}

vector<i64> sieve_of_eratosthenes(i64 B)
{
    vector<i64> primes;
    B = 1 + i64(sqrt(B));
    vector<bool> is_prime(B, true);
    is_prime[0] = false;
    is_prime[1] = false;

    for (i64 p = 2; p * p <= B; p++)
        if (is_prime[p])
            for (i64 i = p * p; i <= B; i += p)
                is_prime[i] = false;

    for (i64 i = 2; i <= B; i++)
        if (is_prime[i])
            primes.push_back(i);

    return primes;
}

int log_p_N(i64 prime, i64 N)
{
    int exp = 0;
    for (; prime <= N; exp++)
        N /= prime;

    return !exp ? 0 : exp - 1;
}
