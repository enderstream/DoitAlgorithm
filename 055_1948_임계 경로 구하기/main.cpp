#include <iostream>
#include <vector>
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

using namespace std;

void solution(int n, int m);

int main(int argc, char const *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    solution(n, m);
    return 0;
}

void solution(int n, int m)
{
    vector<vector<int>> road_map(n + 1, vector<int>(n + 1, 0)); // 양방향으로 도로 연결
    vector<vector<int>> roads(n + 1);
    vector<vector<int>> reverse_roads(n + 1);
    vector<int> cities(n + 1, 0); // 도시의 진입 차수
    vector<int> DP(n + 1, 0);     // 도시별 누적 도착 시간
    int dept, dest, time, city, cnt = 0;
    for (int i = 0; i < m; i++)
    {
        cin >> dept >> dest >> time;
        road_map[dept][dest] = time; // 양방향 연결
        road_map[dest][dept] = time; // 양방향 연결
        roads[dept].push_back(dest);
        reverse_roads[dest].push_back(dept);
        cities[dest]++;
    }
    cin >> dept >> dest;

    queue<int> Q;
    Q.push(dept); // 출발도시 삽입

    // 도시 위상정렬 + 총 이동시간 계산
    while (!Q.empty())
    {
        city = Q.front();
        Q.pop();
        for (const int &next_city : roads[city])
        {
            cities[next_city]--;
            if (cities[next_city] == 0)
                Q.push(next_city);
            DP[next_city] = max(DP[next_city], DP[city] + road_map[city][next_city]);
        }
    }

    cout << DP[dest] << "\n";
    vector<bool> visited(n + 1, false);
    Q.push(dest);
    // 도시를 역순으로 위상정렬 -> 역추적
    while (!Q.empty())
    {
        city = Q.front();
        Q.pop();
        for (const int &before_city : reverse_roads[city])
        {
            // 되돌아갈 도시가 최대 코스트를 요구하는 경로를 거치는지 확인
            if (DP[city] == road_map[before_city][city] + DP[before_city])
            {
                cnt++;
                if (!visited[before_city]) // 중복방문을 예방하기 위해 방문처리
                {
                    Q.push(before_city);
                    visited[before_city] = true;
                }
            }
        }
    }
    cout << cnt;
}