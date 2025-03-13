#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
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

#define INF 2000000000

using namespace std;

typedef unordered_map<int, unordered_map<int, int>> graph_t;
typedef pair<int, int> path_t;
void solution(int V, int E, graph_t &graph, int K);

struct compare
{
    bool operator()(const path_t &a, const path_t &b) const
    {
        return a.second > b.second;
    }
};

int main(int argc, char const *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int V, E, K, u, v, w;
    cin >> V >> E >> K;

    graph_t graph;
    for (int i = 0; i < E; i++)
    {
        cin >> u >> v >> w;
        // 값이 있다면 더 작은걸로 업데이트, 값이 없다면 그냥 삽입
        // if (road_map[u].find(v) != road_map[u].end())
        //     road_map[u][v] = min(road_map[u][v], w);
        // else
        //     road_map[u][v] = w;

        // 더 간결하게 리팩토링 ver1 -> 직관적임
        graph[u][v] = (graph[u].find(v) != graph[u].end()) ? min(graph[u][v], w) : w;

        // 더 간결하게 리팩토링 ver2 -> 조금덜 직관적임
        // if (!road_map[u].count(v) || w < road_map[u][v])
        //     road_map[u][v] = w;
    }

    solution(V, E, graph, K);
    return 0;
}

void solution(int V, int E, graph_t &graph, int K)
{
    priority_queue<path_t, vector<path_t>, compare> PQ; // 우선수위 큐의 두번째 요소인 가중치를 기준으로 오름차순 정렬
    vector<int> min_dist(V + 1, INF);   // 최단 거리를 저장할 벡터
    vector<bool> visited(V + 1, false); // 방문여부를 저장할 벡터
    min_dist[K] = 0;                    // 출발지는 비용이 0
    PQ.push({K, 0}); // 시작 정점 추가

    while (!PQ.empty())
    {
        path_t current_path = PQ.top();  // current_path.first: 현재 정점, current_path.second: 시작점에서의 거리
        PQ.pop();

        // 이 정점이 처리되지 않은 경우만 작업
        if (!visited[current_path.first])
        {
            visited[current_path.first] = true;

            // 현재 정점에서 갈 수 있는 모든 인접 정점 검사
            for (const path_t &next_path : graph[current_path.first])
            {
                int new_distance = current_path.second + next_path.second;

                // 더 짧은 경로를 발견한 경우 큐에 추가
                if (!visited[next_path.first] && new_distance < min_dist[next_path.first])
                {
                    // 방문체크를 하면 더 최적화 가능
                    min_dist[next_path.first] = new_distance;
                    PQ.push({next_path.first, new_distance});
                }
            }
        }
    }

    // 결과 출력
    for (int i = 1 ; i <= V; i++)
        (min_dist[i] == INF) ? cout << "INF\n" : cout << min_dist[i] << "\n";
}