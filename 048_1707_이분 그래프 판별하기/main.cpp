#include <iostream>
#include <vector>
#include <stack>

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

void solution(int V, vector<vector<int>> &graph);
string DFS(int target, vector<int> &visited, int V, vector<vector<int>> &graph);

int main(int argc, const char *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int K;
    cin >> K;
    for (int tc = 0; tc < K; tc++)
    {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> graph(V + 1);
        for (int i = 0; i < E; i++)
        {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        solution(V, graph);
    }

    return 0;
}

void solution(int V, vector<vector<int>> &graph)
{
    bool flag = true;
    vector<int> visited(V + 1, 0);
    for (int i = 1; i <= V; i++)
        if (visited[i] == 0 && "NO" == DFS(i, visited, V, graph))
        {
            cout << "NO" << "\n";
            flag = false;
            break;
        }
    if (flag)
        cout << "YES" << "\n";
}

string DFS(int target, vector<int> &visited, int V, vector<vector<int>> &graph)
{
    int flag = 1;
    visited[target] = flag;
    stack<int> S({target});

    while (!S.empty())
    {
        int node = S.top();
        S.pop();
        flag = visited[node];
        for (auto next : graph[node])
            if (visited[next] == 0)
            {
                visited[next] = -1 * flag;
                S.push(next);
            }
            else if (visited[next] == flag)
                return "NO";
    }
    return "YES";
}
