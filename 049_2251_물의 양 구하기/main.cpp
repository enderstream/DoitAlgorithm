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

typedef pair<int, int> tuple_t;

void solution(int A, int B, int C);
vector<int> BFS(int A, int B, int C);

int main(int argc, const char *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int A, B, C;
    cin >> A >> B >> C;

    solution(A, B, C);
    return 0;
}

void solution(int A, int B, int C)
{
    vector<int> volumes = BFS(A, B, C);
    sort(volumes.begin(), volumes.end());
    for (const int &volume : volumes)
        cout << volume << " ";
}

vector<int> BFS(int A, int B, int C)
{
    vector<int> capacity = {A, B, C};
    vector<vector<bool>> visited(C + 1, vector<bool>(C + 1, false));
    vector<int> volumes = {C};
    vector<vector<int>> movements = {{0, 1}, {0, 2}, {1, 0}, {1, 2}, {2, 0}, {2, 1}};
    queue<vector<int>> Q({{0, 0, C}});
    visited[0][0] = true;

    while (!Q.empty())
    {
        vector<int> curr = Q.front();
        Q.pop();
        for (const auto &movement : movements)
        {
            int from = movement[0];
            int to = movement[1];
            vector<int> ABC = {curr[0], curr[1], curr[2]}; // 현재 물 상태
            if (ABC[from] == 0)                            // 딴데 부으려고 봤는데 텅 비었으면 못부음
                continue;

            ABC[to] += ABC[from];
            ABC[from] = 0;
            if (ABC[to] > capacity[to])
            {
                ABC[from] = ABC[to] - capacity[to];
                ABC[to] = capacity[to];
            }

            if (visited[ABC[0]][ABC[1]])
                continue;
            visited[ABC[0]][ABC[1]] = true;

            Q.push(ABC);
            if (ABC[0] == 0)
                volumes.push_back(ABC[2]);
        }
    }

    return volumes;
}