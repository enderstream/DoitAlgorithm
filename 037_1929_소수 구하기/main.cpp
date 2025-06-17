#include <iostream>
#include <vector>

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

void solution(int M, int N);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
    {
        (void)!freopen("./input.txt", "r", stdin);
        debug << "\n";
    }

    int M, N;
    cin >> M >> N;

    solution(M, N);
    return 0;
}

void solution(int M, int N)
{
    vector<bool> primes(N + 1, true);
    primes[0] = false;
    primes[1] = false;

    for (int p = 2; p * p <= N; p++)
        if (primes[p])
            for (int i = p * p; i <= N; i += p)
                primes[i] = false;

    for (int p = M; p <= N; p++)
        if (primes[p])
            cout << p << "\n";
}

/*
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 ...

2 > 2*2, 2*3, 2*4, ...
3 > 3*3, 3*4, 3*5, ...
4 > continue
5 > 5*5


21 4748 3648
2 * 10^9
4 * 10^18
9,223,372,036,854,775,807
9 * 10^18
*/
