// 3차원 벡터를 활용한 풀이
#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

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

// 우선순위 큐에서 다리 길이가 짧은 순으로 정렬하기 위한 비교 함수
struct compare
{
    bool operator()(const vector<int> &a, const vector<int> &b) const
    {
        return a[2] > b[2]; // 다리 길이가 짧은 것이 우선순위가 높음
    }
};

void solution(int N, int M, vector<vector<int>> &country);
bool boundary_check(int i, int j, int N, int M);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;
    vector<vector<int>> country(N, vector<int>(M, 0)); // 지도 정보 (1: 섬, 0: 바다)

    // 지도 입력 받기
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> country[i][j];

    solution(N, M, country);
    return 0;
}

void solution(int N, int M, vector<vector<int>> &country)
{
    // 상하좌우 이동을 위한 방향 벡터
    vector<vector<int>> delta = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // graph[i][j][k]: (i,j) 위치에서 상하좌우로 갈 수 있는 다리 길이 (-1은 연결 불가)
    vector<vector<vector<int>>> graph(N, vector<vector<int>>(M, vector<int>(4, -1)));

    int si = 0, sj = 0;   // 시작 섬 위치
    int total_island = 0; // 총 섬의 개수

    // 그래프 구성 - 각 섬에서 사방으로 다른 섬까지의 거리 계산
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (country[i][j]) // 현재 위치가 섬인 경우
            {
                total_island++; // 섬 개수 증가
                si = i, sj = j; // 시작점 갱신 (마지막 섬의 위치가 저장됨)

                // 상하좌우 4방향으로 탐색
                for (int k = 0; k < 4; k++)
                {
                    int ni = i + delta[k][0], nj = j + delta[k][1], dist = 0;

                    // 경계 내에 있고 바다인 동안 직진하며 거리 측정
                    while (boundary_check(ni, nj, N, M) && !country[ni][nj])
                    {
                        ni += delta[k][0];
                        nj += delta[k][1];
                        dist++;
                    }

                    // 다른 섬에 도달했으면 거리 기록 (다리 길이가 2 이상이어야 유효)
                    if (boundary_check(ni, nj, N, M))
                        graph[i][j][k] = dist;
                }
            }

    // 최소 신장 트리(MST) 알고리즘 - 프림 알고리즘
    priority_queue<vector<int>, vector<vector<int>>, compare> PQ; // {i, j, 다리 길이}
    vector<vector<bool>> visited(N, vector<bool>(M, false));      // 방문 여부 확인용
    int total_bridge = 0, island = 0;                             // 총 다리 길이, 연결된 섬 개수

    // 첫 번째 섬부터 시작
    PQ.push({si, sj, 0});

    while (!PQ.empty())
    {
        vector<int> node = PQ.top();
        PQ.pop();
        int i = node[0], j = node[1], bridge = node[2]; // 현재 다리 길이와 위치

        if (!visited[i][j]) // 방문하지 않은 섬이면
        {
            visited[i][j] = true;   // 방문 표시
            total_bridge += bridge; // 다리 길이 누적
            island++;               // 연결된 섬 개수 증가

            // 4방향으로 연결 가능한 다른 섬 탐색
            for (int k = 0; k < 4; k++)
                if (abs(graph[i][j][k]) != 1) // 유효한 다리가 있으면 (길이가 2 이상)
                {
                    // 다음 섬의 위치 계산: 현재 위치 + 거리 + 1
                    int ni = i + delta[k][0] * (graph[i][j][k] + 1);
                    int nj = j + delta[k][1] * (graph[i][j][k] + 1);

                    if (!visited[ni][nj]) // 아직 방문하지 않은 섬이면 큐에 추가
                        PQ.push({ni, nj, graph[i][j][k]});
                }
        }
    }

    // 모든 섬이 연결되었으면 전체 다리 길이 출력, 아니면 -1 출력
    cout << (island == total_island ? total_bridge : -1);
}

// 경계 확인
bool boundary_check(int i, int j, int N, int M)
{
    return 0 <= i && i < N && 0 <= j && j < M;
}

// unordered_map을 활용한 풀이

// #include <iostream>
// #include <queue>
// #include <vector>
// #include <algorithm>
// #include <unordered_map>

// #ifdef BOJ // 백준 채점환경
// constexpr bool local = false;
// #else // 로컬
// constexpr bool local = true;
// #endif

// #define FAST_IO                       \
//     std::ios::sync_with_stdio(false); \
//     std::cin.tie(nullptr);            \
//     std::cout.tie(nullptr);
// #define debug            \
//     if constexpr (local) \
//     std::cout
// #define endl "\n"

// using namespace std;

// struct compare
// {
//     bool operator()(const vector<int> &a, const vector<int> &b) const
//     {
//         return a[0] > b[0];
//     }
// };

// void solution(int N, int M, vector<vector<int>> &country);
// void prim(int N, int M, int si, int sj, unordered_map<int, vector<vector<int>>> &graph);
// bool boundary_check(int i, int j, int N, int M);

// int main(int argc, char const *argv[])
// {
//     FAST_IO;
//     if constexpr (local)
//         (void)!freopen("./input.txt", "r", stdin);

//     int N, M;
//     cin >> N >> M;
//     vector<vector<int>> country(N, vector<int>(M, 0));

//     for (int i = 0; i < N; i++)
//         for (int j = 0; j < M; j++)
//             cin >> country[i][j];

//     solution(N, M, country);
//     return 0;
// }

// void solution(int N, int M, vector<vector<int>> &country)
// {
//     vector<vector<int>> delta = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
//     unordered_map<int, vector<vector<int>>> graph;
//     int si = 0, sj = 0;
//     for (int i = 0; i < N; i++)
//         for (int j = 0; j < M; j++)
//             if (country[i][j])
//             {
//                 vector<vector<int>> connection;
//                 si = i, sj = j;
//                 for (const vector<int> &d : delta)
//                 {
//                     int ni = i + d[0], nj = j + d[1], dist = 0;
//                     while (boundary_check(ni, nj, N, M) && !country[ni][nj])
//                     {
//                         ni += d[0];
//                         nj += d[1];
//                         dist++;
//                     }
//                     if (boundary_check(ni, nj, N, M) && dist != 1)
//                         connection.push_back({dist, ni, nj});
//                     graph[100 * i + j] = connection;
//                 }
//             }

//     prim(N, M, si, sj, graph);
// }

// void prim(int N, int M, int si, int sj, unordered_map<int, vector<vector<int>>> &graph)
// {
//     priority_queue<vector<int>, vector<vector<int>>, compare> PQ;
//     vector<vector<bool>> visited(N, vector<bool>(M, false));
//     int cnt = 0, total_weight = 0;
//     PQ.push({0, si, sj});

//     while (!PQ.empty())
//     {
//         vector<int> node = PQ.top();
//         PQ.pop();
//         int w = node[0], i = node[1], j = node[2];
//         if (visited[i][j])
//             continue;
//         visited[i][j] = true;
//         total_weight += w;
//         cnt++;
//         for (const vector<int> &next_node : graph[100 * i + j])
//             if (!visited[next_node[1]][next_node[2]])
//                 PQ.push(next_node);
//     }
//     cout << (cnt == graph.size() ? total_weight : -1);
// }

// bool boundary_check(int i, int j, int N, int M)
// {
//     return 0 <= i && i < N && 0 <= j && j < M;
// }