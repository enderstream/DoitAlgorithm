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

typedef unordered_map<int, unordered_map<int, int>> city_map;
typedef pair<int, int> path_t;

struct compare
{
    bool operator()(const path_t &a, const path_t &b) const
    {
        return a.second > b.second;
    }
};

void solution(int n, int m, int k, city_map &city_map);

int main(int argc, char const *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int n, m, k, a, b, c;
    cin >> n >> m >> k;
    city_map city_map;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        city_map[a][b] = c;
    }

    solution(n, m, k, city_map);
    return 0;
}

void solution(int n, int m, int k, city_map &city_map)
{
    // 최대힙을 이용 -> 큐의 바닥에는 최단거리, 큐의 천장에는 k번째 최단거리가 저장됨, 이러면 top하고만 비교하면 됨
    // 같은 거리인 경로가 여러 개 있을 수 있음:: 예) k = 4일 때, 1->5로 가는 경로의 비용이 1, 2, 3, 3 <- 이럴 수 있음(비용 합이 3인 경로가 2개)
    // 따라서 k번째 최단거리는 3                                                 k(4)번째 최단거리^
    vector<priority_queue<int, vector<int>>> dist_Q(n + 1);
    priority_queue<path_t, vector<path_t>, compare> PQ;
    dist_Q[1].push(0);
    PQ.push({1, 0}); // {도착지, 가중치} :: 1 -> 1

    while (!PQ.empty())
    {
        path_t curr_path = PQ.top();
        PQ.pop();

        // 중복방문 체크를 삭제
        // 그런데 사이클이 있으면 무한루프에 빠지려나...??? -> k개로 제한을 걸면 됨
        for (const path_t &next_path : city_map[curr_path.first])
        {
            int new_cost = curr_path.second + next_path.second;
            // 큐가 꽉 찬 경우, new_cost와 기존에 큐에 있는 최대cost(top)중 더 작은값이 들어가야함
            if (dist_Q[next_path.first].size() == k && new_cost < dist_Q[next_path.first].top())
            {
                dist_Q[next_path.first].pop();
                dist_Q[next_path.first].push(new_cost);
                PQ.push({next_path.first, new_cost}); // 이거 밖으로 빼는 순간 무한루프에 빠짐!!!
            }
            else if (dist_Q[next_path.first].size() < k) // k개 미만으로 설정해야 무한루프에 안 빠짐
            {
                dist_Q[next_path.first].push(new_cost);
                PQ.push({next_path.first, new_cost}); // 이거 밖으로 빼는 순간 무한루프에 빠짐!!!
            }
        }
    }
    for (int i = 1; i <= n; i++)
        (dist_Q[i].size() < k) ? cout << -1 << "\n" : cout << dist_Q[i].top() << "\n";
}