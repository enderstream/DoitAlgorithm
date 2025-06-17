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

typedef struct TP
{
    int T = 0; // time
    int P = 0; // price
} TP_t;

void solution(int N, vector<TP_t> &schedule);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;
    vector<TP_t> schedule(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> schedule[i].T >> schedule[i].P;

    solution(N, schedule);
    return 0;
}

void solution(int N, vector<TP_t> &schedule)
{
    vector<int> DP(N + 2, 0);
    for (int i = N; i >= 1; i--) // reverse DP
        if (i + schedule[i].T > N + 1)
            DP[i] = DP[i + 1];
        else
            DP[i] = max(DP[i + 1], DP[i + schedule[i].T] + schedule[i].P);
    cout << DP[1];
}