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

void solution(int n, vector<vector<int>> &city);

int main(int argc, char const *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int n, m, a, b, c;
    cin >> n >> m;
    vector<vector<int>> city(n + 1, vector<int>(n + 1, INF));

    for (int cnt = 0; cnt < m; cnt++)
    {
        cin >> a >> b >> c;
        city[a][b] = (city[a][b] != 0) ? min(city[a][b], c) : c;
    }

    for (int i = 1; i <= n; i++)
        city[i][i] = 0;

    solution(n, city);
    return 0;
}

void solution(int n, vector<vector<int>> &city)
{
    for (int layover = 1; layover <= n; layover++)
        for (int dept = 1; dept <= n; dept++)
            for (int dest = 1; dest <= n; dest++)
                city[dept][dest] = min(city[dept][layover] + city[layover][dest], city[dept][dest]);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << (city[i][j] == INF ? 0 : city[i][j]) << " ";
        cout << "\n";
    }
}