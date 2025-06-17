#include <iostream>
#include <vector>
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

#define INF 1000000000

using namespace std;

void solution(int N, vector<vector<int>> &graph);

int main(int argc, const char *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;
    vector<vector<int>> graph(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> graph[i][j];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            graph[i][j] = (graph[i][j] == 0 ? INF : 1);

    solution(N, graph);
    return 0;
}

void solution(int N, vector<vector<int>> &graph)
{
    for (int layover = 0; layover < N; layover++)
        for (int dept = 0; dept < N; dept++)
            for (int dest = 0; dest < N; dest++)
            {
                // 이미 경로가 있는 것으로 확인 되었으면 넘어감
                if (graph[dept][dest] == 1)
                    continue;

                // 경로가 처음으로 발견되었으면 표시하고 넘어감
                if (graph[dept][layover] + graph[layover][dest] < INF)
                    graph[dept][dest] = 1;

                // 기존 플로이드처럼 해도 됨
                // graph[dept][dest] = min(graph[dept][dest], graph[dept][layover] + graph[layover][dest]);
            }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << (graph[i][j] == INF ? 0 : 1) << " ";
        cout << "\n";
    }
}