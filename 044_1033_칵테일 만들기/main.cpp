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

using namespace std;

typedef unordered_map<long, vector<long>> vector_map;
typedef vector<vector<pair<long, long>>> pair_matrix;

void reduction(long &p, long &q);
long get_GCD(long p, long q);
void solution(long N, pair_matrix &ratios, vector_map &ingredients);
void calculate_ratio_BFS(long N, vector<pair<long, long>> &mass, pair_matrix &ratios, vector_map &ingredients);
long get_LCM(long p, long q);

int main(long argc, const char *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    long N;
    cin >> N;
    vector_map ingredients;
    pair_matrix ratios(N, vector<pair<long, long>>(N, {0, 0}));
    for (long i = 1; i < N; i++)
    {
        long a, b, p, q;
        cin >> a >> b >> p >> q;
        reduction(p, q);
        ratios[a][b] = {p, q};
        ratios[b][a] = {q, p};
        ingredients[a].push_back(b);
        ingredients[b].push_back(a);
    }

    solution(N, ratios, ingredients);
    return 0;
}

void reduction(long &p, long &q)
{
    if (p == q)
    {
        p = 1;
        q = 1;
    }
    else
    {
        long GCD = get_GCD(max(p, q), min(p, q));
        p /= GCD;
        q /= GCD;
    }
}

long get_GCD(long p, long q)
{
    // p > q is guaranteed
    // p = 27, q = 15
    while (p % q != 0) // 15 % 12 // 12 %3 == 0 >> return 3
    {
        p %= q;     // p=3, q = 12
        swap(p, q); // p = 12, q = 3
    }
    return q;
}

void solution(long N, pair_matrix &ratios, vector_map &ingredients)
{
    long LCM = 1;
    vector<pair<long, long>> mass(N, {1, 1});
    calculate_ratio_BFS(N, mass, ratios, ingredients);

    for (auto m : mass)
    {
        reduction(m.first, m.second);
        LCM = get_LCM(LCM, m.second);
    }

    for (auto m : mass)
        cout << m.first * (LCM / m.second) << " ";
}

void calculate_ratio_BFS(long N, vector<pair<long, long>> &mass, pair_matrix &ratios, vector_map &ingredients)
{
    pair<long, long> std;
    vector<bool> visited(N, false);
    queue<long> Q{{0}};
    visited[0] = true;
    while (!Q.empty())
    {
        long node = Q.front();
        Q.pop();
        std = mass[node];
        for (long next_node : ingredients[node])
            if (!visited[next_node])
            {
                Q.push(next_node);
                visited[next_node] = true;
                mass[next_node].first = std.first * ratios[next_node][node].first;
                mass[next_node].second = std.second * ratios[next_node][node].second;
                reduction(mass[next_node].first, mass[next_node].second);
            }
    }
}

long get_LCM(long p, long q)
{
    long GCD = get_GCD(max(p, q), min(p, q));
    return (p * q) / GCD;
}

/*
"이 비율을 이용해서 칵테일에 들어가는 전체 재료의 비율을 알아낼 수 있다."
라는 의미가 모든 재료는 서클로 연결이 된다는 의미 인가요?
    -> 만약 모든 재료가 서클로 연결이 되었다면, 재료 쌍의 비율이 N - 1 아니라 N 입니다.

4개의 재료가 있는데, 첫번째 재료부터 3번째 재료 까지는 서로 비율이 정해져있고 4번째 재료만 독립적으로 떨어져있는 인풋이 들어오지 않는다는건가요?
아니면 독립적으로 들어올때는 독립적인 재료에 대해서만 최소 값 1을 출력하는 건가요?
    -> 전체 재료의 비율을 알아낼 수 있다고 했으니 독립적으로 떨어져있는 인풋은 들어올 수 없는 것 같습니다.
       마찬가지로 서로 독립적인 재료 쌍들의 집합은 없는 것 같습니다.
       두 집합 사이의 비율을 알 수 없으니 전체 비율을 알아낼 수 없다고 생각했습니다.
       저는 이렇게 상정하고 풀었습니다.
*/