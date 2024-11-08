#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
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

typedef vector<unordered_set<int>> vector_set;

void solution(int N, int K, int X, vector_set &city);
vector<int> BFS(int N, int K, int X, vector_set &city);

int main(int argc, char const *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M, K, X;
    cin >> N >> M >> K >> X;

    vector_set city(N + 1);

    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        city[u].insert(v);
    }

    solution(N, K, X, city);
    return 0;
}

void solution(int N, int K, int X, vector_set &city)
{
    vector<int> dist = BFS(N, K, X, city);
    vector<int> K_dist;
    for (int i = 1; i <= N; i++)
        if (dist[i] == K)
            K_dist.push_back(i);

    if (K_dist.size())
    {
        sort(K_dist.begin(), K_dist.end());
        for (auto node : K_dist)
            cout << node << "\n";
    }
    else
        cout << -1;
}

vector<int> BFS(int N, int K, int X, vector_set &city)
{
    vector<bool> visited(N + 1, false);
    vector<int> dist(N + 1, 0);
    visited[X] = true;
    queue<int> Q({X});

    while (!Q.empty())
    {
        int curr = Q.front();
        Q.pop();

        for (int next = 1; next <= N; next++)
        {
            if (visited[next] || city[curr].find(next) == city[curr].end())
                continue;

            dist[next] = dist[curr] + 1;

            if (dist[next] > K)
                return dist;

            visited[next] = true;
            Q.push(next);
        }
    }
    return dist;
}

// typedef unordered_map<int, unordered_map<int,int>> nested_dict;
// bool safe_access(nested_dict &city, int &curr, int &next)
// {
//     auto it_outer = city.find(curr);
//     if (it_outer == city.end())
//         return false;
//     auto it_inner = it_outer->second.find(next);
//     if (it_inner == it_outer->second.end())
//         return false;
//     return true;
// }