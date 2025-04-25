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

void solution(int N, vector<vector<int>> &connections);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;
    vector<vector<int>> connections(N + 1);
    for (int i = 0; i < N; i++)
    {
        int node1, node2;
        cin >> node1 >> node2;
        connections[node1].push_back(node2);
        connections[node2].push_back(node1);
    }

    solution(N, connections);
    return 0;
}

void solution(int N, vector<vector<int>> &connections)
{
    stack<int> STK;
    vector<int> parents(N + 1, -1);
    vector<bool> visited(N + 1, false);
    STK.push(1);
    while (!STK.empty())
    {
        int parent = STK.top();
        STK.pop();
        for (const int &child : connections[parent])
            if (!visited[child])
            {
                parents[child] = parent;
                if (parent != child)
                {
                    STK.push(child);
                    visited[child] = true;
                }
            }
    }
    
    for (int i = 2; i <= N; i++)
        cout << parents[i] << "\n";
}
