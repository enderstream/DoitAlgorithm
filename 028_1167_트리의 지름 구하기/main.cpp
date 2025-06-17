#include <iostream>
#include <vector>
#include <unordered_map>
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

typedef unordered_map<int, vector<pair<int, int>>> pair_dict;

void solution(int V, pair_dict &tree);
pair<int, int> BFS(int V, pair_dict &tree, int start_node);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int V;
    cin >> V;
    pair_dict tree;
    for (int i = 1; i <= V; i++)
        tree[i];

    for (int i = 1; i <= V; i++)
    {
        int v;
        cin >> v;
        while (true)
        {
            int u, d;
            cin >> u;
            if (u == -1)
                break;
            cin >> d;
            tree[v].push_back(pair<int, int>(u, d));
            tree[u].push_back(pair<int, int>(v, d));
        }
    }

    solution(V, tree);
    return 0;
}

void solution(int V, pair_dict &tree)
{
    cout << BFS(V, tree, BFS(V, tree, 1).first).second;
}

pair<int, int> BFS(int V, pair_dict &tree, int start_node)
{
    vector<bool> visited(V + 1, false);
    vector<int> distance(V + 1, 0);
    queue<int> Q;

    Q.push(start_node);
    visited[start_node] = true;

    while (!Q.empty())
    {
        int node = Q.front();
        Q.pop();

        for (auto next_node : tree[node])
            if (!visited[next_node.first])
            {
                visited[next_node.first] = true;
                Q.push(next_node.first);
                distance[next_node.first] = distance[node] + next_node.second;
            }

    } // 최대값인 인덱스, 최대 거리 리턴
    return pair<int, int>(
        max_element(distance.begin(), distance.end()) - distance.begin(),
        *max_element(distance.begin(), distance.end()));
}