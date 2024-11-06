#include <iostream>
#include <vector>
#include <string>

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

int solution(int N);
vector<int> sieve_of_eratosthenes(int N);
bool is_palindrome(int prime);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
    {
        (void)!freopen("./input.txt", "r", stdin);
        debug << "\n";
    }

    int N;
    cin >> N;

    cout << solution(N);
    return 0;
}

int solution(int N)
{
    vector<int> primes = sieve_of_eratosthenes(N);
    for (int prime : primes)
        if (is_palindrome(prime))
            return prime;
}

vector<int> sieve_of_eratosthenes(int N)
{
    vector<int> primes = {2};
    N++;
    vector<bool> is_prime(N, true);
    is_prime[0] = false;
    is_prime[1] = false;

    for (int p = 2; p * p <= N; p++)
        if (is_prime[p])
            for (int i = p * p; i <= N; i += p)
                is_prime[i] = false;

    for (int i = 3; i <= N; i += 2)
        if (is_prime[i])
            primes.push_back(i);

    return primes;
}

bool is_palindrome(int prime)
{
    string str_prime = to_string(prime);
    int i = 0;
    int j = str_prime.length() - 1;
    while(i <= j)
        if(str_prime[i++] != str_prime[j--])
            return false;

    return true;
}