#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

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

typedef unsigned long long ui64;

string solution(int N, int M, ui64 K);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M;
    ui64 K;
    cin >> N >> M >> K;

    cout << solution(N, M, K);
    return 0;
}

string solution(int N, int M, ui64 K)
{
    vector<vector<ui64>> C(N + M + 1, vector<ui64>(N + M + 1, 0));
    for (int i = 0; i <= N + M; i++)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = min(K + 1, C[i - 1][j - 1] + C[i - 1][j]);
    }

    if (C[N + M][M] < K)
        return "-1";

    string answer;
    answer.reserve(N + M);
    while (N + M > 0)
        if (C[N + M - 1][M] >= K)
        {
            answer += 'a';
            N--;
        }
        else
        {
            answer += 'z';
            K -= C[N + M - 1][M];
            M--;
        }
    return answer;
}