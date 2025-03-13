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

typedef unordered_map<int, unordered_map<int, int>> bus_route;
typedef pair<int, int> path_t;

struct compare
{
    bool operator()(const path_t &a, const path_t &b) const
    {
        return a.second > b.second;
    }
};

void solution(int dept, int dest, int N, bus_route &bus_route);

int main(int argc, char const *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M, dept, dest, cost;
    cin >> N >> M;
    bus_route bus_route;
    for (int i = 0; i < M; i++)
    {
        cin >> dept >> dest >> cost;
        if (!bus_route[dept].count(dest) || cost < bus_route[dept][dest])
            bus_route[dept][dest] = cost;
    }
    cin >> dept >> dest;

    solution(dept, dest, N, bus_route);
    return 0;
}

void solution(int dept, int dest, int N, bus_route &bus_route)
{
    priority_queue<path_t, vector<path_t>, compare> PQ;
    vector<int> min_cost(N + 1, INF);
    vector<bool> visited(N + 1, false);

    min_cost[dept] = 0;
    PQ.push({dept, 0}); // 도착지, 비용 (dest -> dest)

    while (!PQ.empty())
    {
        path_t curr_path = PQ.top(); // first: 이번 정류장, second: 누적 비용
        PQ.pop();

        // 이 정류장을 가본 적이 없다면 탐색 시도
        if (!visited[curr_path.first])
        {
            visited[curr_path.first] = true; // 방문처리

            for (const path_t &next_path : bus_route[curr_path.first])
            {
                int new_cost = curr_path.second + next_path.second; // 누적 비용 계산
                if (!visited[next_path.first] && new_cost < min_cost[next_path.first])
                {
                    min_cost[next_path.first] = new_cost;
                    PQ.push({next_path.first, new_cost});
                }
            }
        }
    }

    cout << min_cost[dest];
}