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
bool is_prime(int number);
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
    if (N <= 2)
        return 2;
    while (true)
    {
        if (is_prime(N) && is_palindrome(N))
            return N;
        N++;
    }
}

bool is_prime(int number)
{
    if (number % 2 == 0)
        return false;
    for (int i = 3; i * i <= number; i += 2)
        if (number % i == 0)
            return false;

    return true;
}

bool is_palindrome(int prime)
{
    string str_prime = to_string(prime);
    int i = 0;
    int j = str_prime.length() - 1;
    while (i <= j)
        if (str_prime[i++] != str_prime[j--])
            return false;

    return true;
}