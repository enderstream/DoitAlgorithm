#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

typedef unordered_map<int, vector<int>> dict;

void solution(int N, dict &graph, int V);
void DFS(int N, dict &graph, int V);
void BFS(int N, dict &graph, int V);

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N, M, V;
    cin >> N >> M >> V;

    dict graph;
    for (int i = 1; i <= N; i++)
        graph[i];

    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= N; i++)
        if (graph[i].size() > 0)
            sort(graph[i].begin(), graph[i].end());

    solution(N, graph, V);
    return 0;
}

void solution(int N, dict &graph, int V)
{
    DFS(N, graph, V);
    cout << "\n";
    BFS(N, graph, V);
}

void DFS(int N, dict &graph, int V)
{
    vector<bool> visited(N + 1, false);
    stack<int> stack;
    stack.push(V);
    while (!stack.empty())
    {
        int node = stack.top();
        stack.pop();
        if (visited[node])
            continue;

        cout << node << " ";
        visited[node] = true;

        for (int i = graph[node].size() - 1; i >= 0; i--)
            if (!visited[graph[node][i]])
                stack.push(graph[node][i]);
    }
}

void BFS(int N, dict &graph, int V)
{
    vector<bool> visited(N + 1, false);
    queue<int> Q;
    Q.push(V);
    visited[V] = true;
    while (!Q.empty())
    {
        int node = Q.front();
        cout << node << " ";
        Q.pop();

        for (int i = 0; i < graph[node].size(); i++)
            if (!visited[graph[node][i]])
            {
                visited[graph[node][i]] = true;
                Q.push(graph[node][i]);
            }
    }
}