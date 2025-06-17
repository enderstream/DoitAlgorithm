#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
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

typedef pair<int, int> edge;
typedef vector<vector<edge>> edges;

struct compare
{
    bool operator()(const edge &a, const edge &b) const
    {
        return a.second > b.second;
    }
};

void solution(int V, int E, edges &edges);

int main(int argc, const char *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int V, E, A, B, C;
    cin >> V >> E;

    edges edges(V + 1);

    for (int i = 0; i < E; i++)
    {
        cin >> A >> B >> C;
        edges[A].push_back({B, C});
        edges[B].push_back({A, C});
    }

    solution(V, E, edges);
    return 0;
}

void solution(int V, int E, edges &edges)
{
    int total_weight = 0;
    vector<bool> visited(V + 1, false);
    priority_queue<edge, vector<edge>, compare> PQ;
    PQ.push({1, 0});
    visited[1] = true;

    for (const edge &edge : edges[1])
        PQ.push(edge);

    while (!PQ.empty())
    {
        edge next_edge = PQ.top();
        PQ.pop();
        if (!visited[next_edge.first])
        {
            visited[next_edge.first] = true;
            total_weight += next_edge.second;
            for (const edge &edge : edges[next_edge.first])
                if (!visited[edge.first])
                    PQ.push(edge);
        }
    }

    cout << total_weight;
}