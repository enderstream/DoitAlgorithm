#include <iostream>
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

typedef unsigned long long ui64;
using namespace std;

void solution(vector<pair<int, int>> &query_set);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int T;
    cin >> T;
    vector<pair<int, int>> query_set(T);

    for (int i = 0; i < T; i++)
        cin >> query_set[i].first >> query_set[i].second;

    solution(query_set);
    return 0;
}

void solution(vector<pair<int, int>> &query_set)
{
    int N, R;
    ui64 n, r;
    for (const pair<int, int> &q : query_set)
    {
        int N = q.second, R = q.first;
        ui64 result = 1;
        for (int i = 0; i < R; i++)
            result = result * (N - i) / (i + 1);

        cout << result << "\n";
    }
}