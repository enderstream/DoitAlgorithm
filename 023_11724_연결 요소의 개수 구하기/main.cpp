#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

typedef unordered_map<int, vector<int>> dict;

void solution(int N, dict &graph);
void DFS(vector<bool> &visited, stack<int> &stk, dict &graph);

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;
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

    solution(N, graph);
    return 0;
}

void solution(int N, dict &graph)
{
    int connected_component = 0;
    vector<bool> visited(N + 1, false);
    stack<int> stk;
    for (int i = 1; i <= N; i++)
        if (!visited[i])
        {
            visited[i] = true;
            stk.push(i);
            DFS(visited, stk, graph);
            connected_component++;
        }
    cout << connected_component;
}

void DFS(vector<bool> &visited, stack<int> &stk, dict &graph)
{
    while (!stk.empty())
    {
        int node = stk.top();
        stk.pop();
        if (graph[node].size() > 0)
            for (auto next_node : graph[node])
                if (!visited[next_node])
                {
                    visited[next_node] = true;
                    stk.push(next_node);
                }
    }
}