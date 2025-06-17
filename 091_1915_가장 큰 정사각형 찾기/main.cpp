#include <iostream>
#include <algorithm>
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

void solution(int n, int m, vector<vector<int>> &DP);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    string line;
    vector<vector<int>> DP(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        cin >> line;
        for (int j = 0; j < m; j++)
            DP[i][j] = line[j] - '0';
    }

    solution(n, m, DP);
    return 0;
}

void solution(int n, int m, vector<vector<int>> &DP)
{
    int max_side = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (DP[i][j] == 1 && i > 0 && j > 0)
                DP[i][j] += min({DP[i - 1][j - 1], DP[i - 1][j], DP[i][j - 1]});
            max_side = max(max_side, DP[i][j]);
        }

    cout << max_side * max_side;
}