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

typedef unsigned long long ui64;

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
    // memory optimized
    ui64 end_with_0 = 0, end_with_1 = 1;
    for (int i = 2; i <= N; i++)
    {
        end_with_0 += end_with_1;             // i자리에서 0으로 끝나는 경우 = i-1자리에서 0으로 끝나는경우 + 1로 끝나는 경우
        end_with_1 = end_with_0 - end_with_1; // i자리에서 1로 끝나는 경우 = i-1 자리에서 0으로 끝나는 경우, 그런데 위 식에서 0으로 끝나는 경우에 1로 끝나는 경우가 추가되어버렸으므로, 그것만큼 배제할 것
    }
    cout << end_with_0 + end_with_1;
}

// void solution(int N)
// {
//     vector<vector<ui64>> DP(N + 1, vector<ui64>(2, 0));
//     DP[1][0] = 0;
//     DP[1][1] = 1;
//     for (int i = 2; i <= N; i++)
//     {
//         DP[i][0] = DP[i - 1][0] + DP[i - 1][1];
//         DP[i][1] = DP[i - 1][0];
//     }
//     cout << DP[N][0] + DP[N][1];
// }