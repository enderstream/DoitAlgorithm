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
bool ckeck_negative_cycle(ll N, bus_route &bus_route, vector<ll> &DP);

int main(int argc, const char *argv[])
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
    for (ll i = 1; i < N; i++)      // N-1회 반복 :: "최대 i개의 간선을 사용"이 아님!!!! << 절대 이렇게 생각 금지
        for (ll j = 1; j <= N; j++) // 모든 출발 노드에 대해
            if (DP[j] != INF)       // 도달 가능한 노드만 고려
                for (const path_t &route : bus_route[j])
                    DP[route.first] = min(DP[route.first], DP[j] + route.second);

    // 음수 사이클 검사 -> 한번 더 루프했을 때, 변화가 생긴다면 음수 사이클이 있다는 뜻
    if (ckeck_negative_cycle(N, bus_route, DP))
        cout << -1;
    else
        for (ll i = 2; i <= N; i++)
            DP[i] == INF ? cout << "-1\n" : cout << DP[i] << "\n";
}

bool ckeck_negative_cycle(ll N, bus_route &bus_route, vector<ll> &DP)
{
    for (ll j = 1; j <= N; j++)
        if (DP[j] != INF) // j로 갈 수 있는 경로가 있는 경우에만 탐색 시도
            for (const path_t &route : bus_route[j])
                if (DP[route.first] > DP[j] + route.second)
                    return true; // 음수 사이클 발견
    return false;
}