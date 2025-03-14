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

#define INF 9000000000000000000
// 왜 출력초과가 나지...???

using namespace std;

typedef long long ll;
typedef unordered_map<ll, unordered_map<ll, ll>> bus_route; // 출발 -> 도착 -> 가중
typedef pair<ll, ll> path_t;

void solution(ll N, bus_route &bus_route);

int main(ll argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    ll N, M, A, B, C;
    cin >> N >> M;
    bus_route bus_route;
    for (ll i = 0; i < M; i++)
    {
        cin >> A >> B >> C;
        if (!bus_route[A].count(B) || C < bus_route[A][B])
            bus_route[A][B] = C;
    }

    solution(N, bus_route);
    return 0;
}

void solution(ll N, bus_route &bus_route)
{
    vector<ll> DP(N + 1, INF);
    DP[1] = 0;
    for (ll i = 1; i < N; i++) // for 루프 추가
        for (ll j = 1; j <= N; j++)
            for (const path_t &route : bus_route[j])
                DP[route.first] = min(DP[route.first], DP[j] + route.second);

    // 음수 사이클 검사 -> 한번 더 루프했을 때, 변화가 생긴다면 음수 사이클이 있다는 뜻
    for (ll i = 1; i <= N; i++)
        for (const path_t &route : bus_route[i])
            if (DP[i] == INF || DP[route.first] > DP[i] + route.second)
                DP[i] = -1;

    for (ll i = 2; i <= N; i++)
        cout << DP[i] << "\n";
}