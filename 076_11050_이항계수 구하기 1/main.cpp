#include <iostream>

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

void solution(int N, int K);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, K;
    cin >> N >> K;

    solution(N, K);
    return 0;
}

void solution(int N, int K)
{
    int A = 1, B = 1;
    for (int i = N - K + 1; i <= N; i++)
        A *= i;
    for (int i = 2; i <= K; i++)
        B *= i;

    cout << A / B;
}

/*
nCk

n!
= n n-1 n-2 n-3 ... n-k n-k-1 n-k-2 ... 1
> n ~ n-k+1
---
(n-k)! * k!
= n-k * n-k-1 ... 1 * k k-1 k-2 ...


*/
