#include <iostream>
#include <vector>
#include <iomanip>
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

#define MOD 1000000007

using namespace std;

typedef unsigned long long ui64;

void solution(int N, int L, int R);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, L, R;
    cin >> N >> L >> R;

    solution(N, L, R);
    return 0;
}

void solution(int N, int L, int R)
{
    vector<vector<ui64>> C(N + 1, vector<ui64>(N + 1, 0));
    for (int i = 0; i <= N; i++)
        C[i][0] = C[i][i] = 1;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= i - 1; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;

    vector<vector<vector<ui64>>> DP(N + 1, vector<vector<ui64>>(N + 1, vector<ui64>(N + 1, 0)));
    DP[1][0][1] = DP[1][1][0] = DP[1][1][1] = 1;

    // DP 테이블 초기화
    for (int i = 2; i <= N; i++)
    {
        for (int j = 1; j <= i; j++)
            for (int k = 1; k <= i - j + 1; k++)
                DP[i][j][k] = C[j - 1 + k - 1][k - 1];
        DP[i][1][1] = 0;

        for (int j = 2; j <= i; j++)
            for (int k = 1; k <= j; k++)
                DP[i][j - k + 1][k] = (DP[i][j - k + 1][k] * DP[i - 1][j - 1][0]) % MOD;

        // 0번 열에 합을 저장
        for (int j = 1; j <= i; j++)
            for (int k = 1; k <= i - j + 1; k++)
                DP[i][j][0] = (DP[i][j][0] + DP[i][j][k]) % MOD;
    }

    cout << DP[N][L][R] % MOD;
}