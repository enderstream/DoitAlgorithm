#include <iostream>
#include <vector>

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

void solution(vector<pair<int, int>> &query_set);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int T;
    cin >> T;
    vector<pair<int, int>> query_set(T);
    for (int i = 0; i < T; i++)
        cin >> query_set[i].first >> query_set[i].second;

    solution(query_set);
    return 0;
}

void solution(vector<pair<int, int>> &query_set)
{
    // 0층 ~ 14층 / 1호 ~ 14호
    vector<vector<int>> apartment(15, vector<int>(15, 0));
    for (int j = 1; j <= 14; j++)
    {
        apartment[0][j] = j;
        apartment[j][1] = 1;
    }

    for (int j = 2; j <= 14; j++)
        for (int i = 1; i <= 14; i++)
            apartment[i][j] = apartment[i][j - 1] + apartment[i - 1][j];

    for (const pair<int, int> &q : query_set)
        cout << apartment[q.first][q.second] << "\n";
}

// for (int i = 14; i >= 0; i--)
// {
//     for (int j = 0; j < 15; j++)
//     {
//         debug << setw(8) << apartment[i][j] << " ";
//     }
//     debug << "\n";
// }