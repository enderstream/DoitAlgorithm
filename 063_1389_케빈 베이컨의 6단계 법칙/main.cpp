#include <iostream>
#include <vector>
#include <algorithm>
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

#define INF 1000000000

using namespace std;

void solution(int N, vector<vector<int>> &friends);

int main(int argc, const char *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M, A, B;
    cin >> N >> M;
    vector<vector<int>> friends(N + 1, vector<int>(N + 1, INF));
    for (int i = 0; i < M; i++)
    {
        cin >> A >> B;
        friends[A][B] = 1;
        friends[B][A] = 1;
    }

    for (int i = 0; i <= N; i++)
        friends[i][i] = 0;

    solution(N, friends);
    return 0;
}

void solution(int N, vector<vector<int>> &friends)
{
    for (int bridge = 1; bridge <= N; bridge++)
        for (int A = 1; A <= N; A++)
            for (int B = 1; B <= N; B++)
            {
                friends[A][B] = min(friends[A][B], friends[A][bridge] + friends[bridge][B]);
                friends[B][A] = min(friends[A][B], friends[A][bridge] + friends[bridge][B]);
            }

    for (int i = 1; i <= N; i++)
        friends[i][0] = accumulate(++friends[i].begin(), friends[i].end(), 0);

    int kebin_bacon = 1;
    for (int i = 2; i <= N; i++)
        if (friends[i][0] < friends[kebin_bacon][0])
            kebin_bacon = i;

    cout << kebin_bacon;
}