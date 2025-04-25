#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

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

#define NEG_INF -9000000000000000000

using namespace std;

typedef long long i64;
typedef pair<i64, i64> path_t;
typedef unordered_map<i64, unordered_map<i64, i64>> city_map;

string solution(i64 N, i64 dept, i64 dest, i64 M, city_map &city_map);
bool check_positive_cycle(i64 dept, i64 dest, i64 N, city_map &city_map, vector<i64> DP);

int main(int argc, char const *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    i64 N, dept, dest, M, u, v, w;
    cin >> N >> dept >> dest >> M;
    city_map city_map;
    for (i64 i = 0; i < M; i++)
    {
        cin >> u >> v >> w;
        if (!city_map[u].count(v) || w < city_map[u][v])
            city_map[u][v] = w;
    }
    vector<i64> profit(N, 0);
    for (i64 i = 0; i < N; i++)
        cin >> profit[i];

    // it->first : 출발도시
    // path.first : 도착도시
    // path.second : 출발도시 -> 도착도시로 가는데 드는 비용
    for (auto it = city_map.begin(); it != city_map.end(); it++)
        for (const path_t &path : city_map[it->first])
            city_map[it->first][path.first] = profit[path.first] - city_map[it->first][path.first];

    string answer = solution(N, dept, dest, M, city_map);
    if (answer != "gg" && answer != "Gee")
        cout << i64(stoll(answer)) + profit[dept]; // 출발지에서 벌 수 있는 돈을 추가해야함
    else
        cout << answer;

    return 0;
}

string solution(i64 N, i64 dept, i64 dest, i64 M, city_map &city_map)
{
    vector<i64> DP(N, NEG_INF);
    DP[dept] = 0;
    for (i64 i = 1; i < N; i++)     // N-1 :: 도시 개수 -1회 반복
        for (i64 j = 0; j < N; j++) // 0번도시부터 N-1번 도시까지
            if (DP[j] != NEG_INF)
                for (const path_t &path : city_map[j])
                    DP[path.first] = max(DP[path.first], DP[j] + path.second); // path.first: 도착지, path.second: 출발지(j)에서 도착지(path.first)로 가는 비용

    if (DP[dest] == NEG_INF)
        return "gg"; // gg // 도달할 수 없는지부터 확인
    else if (check_positive_cycle(DP[dest], dest, N, city_map, DP))
        return "Gee"; // 도달할 수 있는데, 양수 사이클이 있을 떄
    else
        return to_string(DP[dest]); // 그 외
}

bool check_positive_cycle(i64 cost, i64 dest, i64 N, city_map &city_map, vector<i64> DP)
{
    // 양수사이클을 체크하기위해 한번더 업데이트
    for (i64 j = 0; j < N; j++) // 0번도시부터 N-1번 도시까지 -> dept부터 dest까지의 알려진 최단 경로에 대해서만 검사
        if (DP[j] != NEG_INF)
            for (const path_t &path : city_map[j])
                    DP[path.first] = max(DP[path.first], DP[j] + path.second); // path.first: 도착지, path.second: 출발지(j)에서 도착지(path.first)로 가는 비용

    // 변했다면(커졌다면, 즉 양수사이클이 있다면) true, 안 변했다면(그대로라면, 즉 양수사이클이 없다면) false
    return DP[dest] != cost;
}