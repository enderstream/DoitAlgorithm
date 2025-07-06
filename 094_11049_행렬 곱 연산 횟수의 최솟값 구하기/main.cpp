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

#define INF 2147483647

using namespace std;

typedef struct matrix
{
    int r;
    int c;
} matrix_t;

void solution(int N, vector<matrix_t> &matrices);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;

    vector<matrix_t> matrices(N);
    for (int i = 0; i < N; i++)
        cin >> matrices[i].r >> matrices[i].c;

    solution(N, matrices);
    return 0;
}

void solution(int N, vector<matrix_t> &matrices)
{
    vector<vector<int>> DP(N, vector<int>(N, INF));
    for (int i = 0; i < N; i++)
        DP[i][i] = 0;

    for (int len = 1; len < N; len++)
        for (int i = 0; i < N - len; i++)
            for (int k = i; k < i + len; k++)
                DP[i][i + len] = min(DP[i][i + len],
                                     DP[i][k] + DP[k + 1][i + len] + matrices[i].r * matrices[k].c * matrices[i + len].c);

    cout << DP[0][N - 1];
}