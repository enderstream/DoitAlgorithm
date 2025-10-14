#include <iostream>
#include <vector>
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

#define INF 1000000000

using namespace std;

void solution(int N, vector<vector<int>> &W);
int popcount(int bitmask);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    // io here
    int N;
    cin >> N;
    vector<vector<int>> W(N, vector<int>(N, INF));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            W[i][j] = (cin >> W[i][j], W[i][j] ? W[i][j] : INF);

    solution(N, W);
    return 0;
}

void solution(int N, vector<vector<int>> &W)
{
    int full_set = (1 << (N - 1)) - 1;
    vector<vector<int>> DP(N, vector<int>(full_set + 1, INF));

    for (int i = 1; i < N; i++)
        DP[i][0] = W[i][0];

    for (int cnt = 1; cnt < N - 1; cnt++)
        for (int A = 0; A <= full_set; A++)
            if (popcount(A) == cnt)
                for (int i = 1; i < N; i++)
                    if (!(A & (1 << (i - 1)))) // if(i not in A)
                        for (int j = 1, bits = A; bits > 0; bits >>= 1, j++)
                            if (bits & 1) // for only j in A
                                DP[i][A] = min(DP[i][A], W[i][j] + DP[j][A & ~(1 << (j - 1))]);

    for (int j = 1; j < N; j++)
        DP[0][full_set] = min(DP[0][full_set], W[0][j] + DP[j][full_set ^ (1 << (j - 1))]);

    cout << DP[0][full_set];
}

int popcount(int bitmask)
{
    int cnt = 0;
    while (bitmask)
    {
        bitmask &= bitmask - 1;
        cnt++;
    }
    return cnt;
}