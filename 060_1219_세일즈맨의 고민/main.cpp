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

#define INF 9000000000000000000

using namespace std;

typedef long long i64;
typedef pair<i64, i64> path_t;
typedef unordered_map<i64, unordered_map<i64, i64>> city_map;

string solution(i64 N, i64 dept, i64 dest, i64 M, city_map &city_map);

int main(int argc, const char *argv[])
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
    for (city_map::iterator it = city_map.begin(); it != city_map.end(); it++)
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
    vector<i64> DP(N, -INF);
    DP[dept] = 0;
    for (i64 i = 0; i <= 2 * N; i++)
        for (city_map::iterator it = city_map.begin(); it != city_map.end(); it++)
        {
            i64 start = it->first;
            for (const path_t &path : city_map[it->first])
            {
                i64 end = path.first;
                i64 cost = path.second;
                if (DP[start] == INF)
                    DP[end] = INF;
                else if (DP[start] != -INF && DP[end] < DP[start] + cost)
                {
                    DP[end] = DP[start] + cost;
                    if (i >= N - 1)
                        DP[end] = INF;
                }
            }
        }

    if (DP[dest] == -INF)
        return "gg";
    else if (DP[dest] == INF)
        return "Gee";
    else
        return to_string(DP[dest]);
}