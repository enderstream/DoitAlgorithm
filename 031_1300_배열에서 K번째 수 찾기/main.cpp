#include <iostream>
#include <algorithm>

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

void solution(long N, long K);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    long N, K;
    cin >> N >> K;

    solution(N, K);
    return 0;
}

void solution(long N, long K)
{
    long L = 1, R = K;

    while (L <= R)
    {
        long M = (L + R) / 2, cnt = 0;
        
        for (long i = 1; i <= N; i++)
            cnt += min(M / i, N);
        if (cnt < K)
            L = M + 1;
        else // cnt => K
            R = M - 1;
    }

    cout << L;
}