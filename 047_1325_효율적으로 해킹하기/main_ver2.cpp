// cycle에 매우 취약한 DP방식의 코드 >> 근데 DFS와 DP를 접목한 점에서 나름 의미는 있는듯
#include <iostream>
#include <vector>
#include <unordered_set>
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

typedef vector<unordered_set<int>> vector_set;

void solution(int N, vector_set &trust_network);
void DFS(vector<bool> &visited, vector<int> &DP, int target, vector_set &trust_network);

int main(int argc, char const *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;

    vector_set trust_network(N + 1);
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        trust_network[v].insert(u);
    }

    solution(N, trust_network);
    return 0;
}

void solution(int N, vector_set &trust_network)
{
    vector<int> DP(N + 1, 0);
    vector<bool> visited(N + 1, false);
    for (int i = 1; i <= N; i++)
        if (!visited[i])
            DFS(visited, DP, i, trust_network);

    for (auto i : DP)
        cout << i << " ";
}

void DFS(vector<bool> &visited, vector<int> &DP, int target, vector_set &trust_network)
{
    stack<int> visit_stack;
    stack<int> DFS_stack;
    DFS_stack.push(target);
    visited[target] = true;
    while (!DFS_stack.empty())
    {
        int PC = DFS_stack.top();
        DFS_stack.pop();
        visit_stack.push(PC);

        for (auto next : trust_network[PC])
            if (!visited[next])
            {
                visited[next] = true;
                DFS_stack.push(next);
            }
    }
    while (!visit_stack.empty())
    {
        int PC = visit_stack.top();
        visit_stack.pop();
        for (auto next : trust_network[PC])
            DP[PC] += DP[next];
        DP[PC] += trust_network[PC].size();
    }
}