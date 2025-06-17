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

using namespace std;

void solution(int N);

int main(int argc, const char *argv[])
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
    vector<int> DP(N + 1, N + 1);
    DP[1] = DP[0] = 0;
    for (int i = 1; i < N; i++)
    {
        DP[i + 1] = min(DP[i] + 1, DP[i + 1]);
        if (i * 2 <= N)
            DP[i * 2] = min(DP[i] + 1, DP[i * 2]);
        if (i * 3 <= N)
            DP[i * 3] = min(DP[i] + 1, DP[i * 3]);
    }
    cout << DP[N];
}