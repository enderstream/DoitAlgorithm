#include <iostream>
#include <vector>
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

void solution(int N, int K);

int main(int argc, char const *argv[])
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
    vector<vector<int>> pascal_triangle(N + 1, vector<int>(N + 1, 0));
    for (int i = 0; i <= N; i++)
        pascal_triangle[i][0] = pascal_triangle[i][i] = 1;

    // fill pascal's triangle
    for (int i = 2; i <= N; i++)
        for (int j = 1; j <= i - 1; j++)
            pascal_triangle[i][j] = (pascal_triangle[i - 1][j - 1] + pascal_triangle[i - 1][j]) % 10007;

    cout << pascal_triangle[N][K];

    // for (int i = 0; i <= N; i++)
    // {
    //     for (int j = 0; j <= i; j++)
    //         debug << setw(5) << pascal_triangle[i][j] << " ";
    //     debug << "\n";
    // }
}

// 메모리를 쥐어짜는 버전 O(K)
// void solution(int N, int K) {
//     const int MOD = 10007;
//     // dp[j] = 현재까지 계산된 C(i, j)
//     vector<int> dp(K+1, 0);
//     dp[0] = 1;  // C(i,0)=1
//     for (int i = 1; i <= N; i++) {
//         // j는 i, K 중 작은 값까지만 계산해도 충분
//         int upper = min(i, K);
//         // 뒤에서부터 갱신해야 이전 행 값이 보존됨
//         for (int j = upper; j >= 1; j--) {
//             dp[j] = (dp[j] + dp[j-1]) % MOD;
//         }
//         // dp[0]은 항상 1
//     }
//     cout << dp[K];
// }

