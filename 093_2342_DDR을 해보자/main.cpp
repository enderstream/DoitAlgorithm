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

#define INF 4000000

using namespace std;

void solution(vector<int> &sequence);
void initiallize_movement(vector<vector<int>> &movement);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int order;
    vector<int> sequence;
    while (cin >> order && order != 0)
        sequence.push_back(order);

    solution(sequence);
    return 0;
}

void solution(vector<int> &sequence)
{
    int L = 0, R = 0, N = sequence.size();
    vector<vector<vector<int>>> DP(N + 1, vector<vector<int>>(5, vector<int>(5, INF)));
    vector<vector<int>> movement(5, vector<int>(5, 0));
    initiallize_movement(movement);
    DP[0][0][0] = 0;

    for (int s = 0; s < N; s++)
    {
        int next = sequence[s];
        for (int i = 0; i < 5; i++)
            if (i != next)
                for (int prev = 0; prev < 5; prev++)
                {
                    // 1) 오른발을 움직인 경우: i는 왼발 위치 고정, prev(=이전 오른발 위치) → next(=새로운 위치) 로 오른발 이동
                    if (DP[s][i][prev] != INF)
                        DP[s + 1][i][next] = min(DP[s + 1][i][next], DP[s][i][prev] + movement[prev][next]);

                    // 2) 왼발을 움직인 경우: i는 오른발 위치 고정, prev(=이전 왼발 위치) → next(=새로운 위치) 로 왼발 이동
                    if (DP[s][prev][i] != INF)
                        DP[s + 1][next][i] = min(DP[s + 1][next][i], DP[s][prev][i] + movement[prev][next]);
                }
    }

    int min_power = INF;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            min_power = min(min_power, DP[N][i][j]);

    cout << min_power;
}

void initiallize_movement(vector<vector<int>> &movement)
{
    for (int i = 1; i < 5; i++)
    {
        movement[i][i] = 1;
        movement[0][i] = 2;
        movement[i][i % 4 + 1] = movement[i % 4 + 1][i] = 3;
    }
    for (int i = 1; i <= 2; i++)
        movement[i][i + 2] = movement[i + 2][i] = 4;
}
