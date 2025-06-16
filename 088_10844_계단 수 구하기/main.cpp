#include <iostream>
#include <vector>
#include <numeric>

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

#define MOD 1000000000

using namespace std;

typedef unsigned long long ui64;

void solution(int N);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;

    solution(N);
    return 0;
}

void solution(int N)
{
    vector<vector<ui64>> DP(N + 1, vector<ui64>(10, 1));
    for (int i = 2; i <= N; i++)
    {
        DP[i][0] = DP[i - 1][1] % MOD;
        DP[i][9] = DP[i - 1][8] % MOD;
        for (int j = 1; j <= 8; j++)
            DP[i][j] = (DP[i - 1][j - 1] + DP[i - 1][j + 1]) % MOD;
    }

    ui64 answer = 0;
    for (int i = 1; i < 10; i++)
        answer += DP[N][i] % MOD;

    cout << answer % MOD;
}
// 메모리 더 최적화 할 수 있을 듯...