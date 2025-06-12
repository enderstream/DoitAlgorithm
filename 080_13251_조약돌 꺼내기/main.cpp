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

using namespace std;

typedef unsigned long long ui64;

void solution(int M, vector<int> &stones, int K);
ui64 calc_combination(int n, int r);
ui64 calc_gcd(ui64 a, ui64 b);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int M, K;
    cin >> M;
    vector<int> stones(M + 1, 0);
    for (int i = 1; i <= M; i++)
        cin >> stones[i];

    cin >> K;

    solution(M, stones, K);

    return 0;
}

void solution(int M, vector<int> &stones, int K)
{
    int total_stones = accumulate(stones.begin(), stones.end(), 0);
    long double result = 0.0;

    for (int stone : stones)
        if (stone >= K)
        {
            long double probability = 1.0;
            for (int j = 0; j < K; j++)
                probability *= ((long double)(stone - j) / (long double)(total_stones - j));
            result += probability;
        }
    cout << fixed << setprecision(15) << result;
}
