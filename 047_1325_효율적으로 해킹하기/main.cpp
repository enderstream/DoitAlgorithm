#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

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

void solution(int N, vector<vector<int>> &trust_network);
int BFS(int target, int N, vector<vector<int>> &trust_network);

int main(int argc, char const *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> trust_network(N + 1);
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        trust_network[v].push_back(u);
    }

    solution(N, trust_network);
    return 0;
}

void solution(int N, vector<vector<int>> &trust_network)
{
    vector<int> infested(N + 1, 0);
    int max_infested = 0;
    for (int i = 1; i <= N; i++)
    {
        infested[i] = BFS(i, N, trust_network);
        max_infested = max(max_infested, infested[i]);
    }

    for (int i = 1; i <= N; i++)
        if (infested[i] == max_infested)
            cout << i << " ";
}

int BFS(int target, int N, vector<vector<int>> &trust_network)
{
    vector<bool> visited(N + 1, false);
    queue<int> Q({target});
    visited[target] = true;
    int infested = 1;
    while (!Q.empty())
    {
        int PC = Q.front();
        Q.pop();
        for (auto next : trust_network[PC])
            if (!visited[next])
            {
                infested++;
                visited[next] = true;
                Q.push(next);
            }
    }
    return infested;
}