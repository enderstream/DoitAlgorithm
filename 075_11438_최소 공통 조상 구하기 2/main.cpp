#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

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

typedef vector<vector<int>> tree_t;
typedef vector<pair<int, int>> query_set_t;

void solution(int N, int M, tree_t &temp_tree, query_set_t &query_set);
tree_t organize_tree(int N, tree_t &temp_tree, vector<int> &depth, int &max_step);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M, node1, node2;

    cin >> N;
    tree_t temp_tree(N + 1);

    for (int i = 0; i < N - 1; i++)
    {
        cin >> node1 >> node2;
        temp_tree[node1].push_back(node2);
        temp_tree[node2].push_back(node1);
    }

    cin >> M;
    query_set_t query_set(M);

    for (int i = 0; i < M; i++)
        cin >> query_set[i].first >> query_set[i].second;

    solution(N, M, temp_tree, query_set);
    return 0;
}

void solution(int N, int M, tree_t &temp_tree, query_set_t &query_set)
{
    int node1, node2, max_step;
    vector<int> depth(N + 1), answer_set(M);
    tree_t parent = organize_tree(N, temp_tree, depth, max_step);

    for (int i = 0; i < M; i++)
    {
        auto [node1, node2] = query_set[i];
        // int [node1, node2] = query_set[i];
        if (depth[node1] < depth[node2])
            swap(node1, node2);

        // 깊이 맞추기 - 비트 조작
        int depth_diff = depth[node1] - depth[node2];
        for (int step = 0; step <= max_step; step++)
            if ((depth_diff >> step) & 1)
                node1 = parent[step][node1];

        // LCA 찾기 - 통합된 로직
        for (int step = max_step; step >= 0; step--)
            if (parent[step][node1] != parent[step][node2])
            {
                node1 = parent[step][node1];
                node2 = parent[step][node2];
            }

        // 결과 처리 - 삼항 연산자로 통합
        answer_set[i] = (node1 == node2) ? node1 : parent[0][node1];
    }
    for (const int &answer : answer_set)
        cout << answer << "\n";
}

tree_t organize_tree(int N, tree_t &temp_tree, vector<int> &depth, int &max_step)
{
    // 기존 temp_tree는 무방향 트리라서 부모 자식 관계를 BFS로 알아내야함
    vector<int> direct_parent(N + 1, 0); //
    vector<bool> visited(N + 1, false);
    visited[1] = true;

    queue<pair<int, int>> Q;
    Q.push({0, 1});
    while (!Q.empty())
    {
        pair<int, int> node = Q.front(); // depth, current_node
        Q.pop();
        for (const int &next_node : temp_tree[node.second])
            if (!visited[next_node])
            {
                visited[next_node] = true;
                depth[next_node] = node.first + 1;      // 깊이 설정
                direct_parent[next_node] = node.second; // 부모 설정
                Q.push({node.first + 1, next_node});
            }
    }

    // create parent table
    max_step = int(log2(*max_element(depth.begin(), depth.end()))); // 1 << K <= log2(가장 깊은 노드의 깊이)인 최대 K
    tree_t parent(max_step + 1, vector<int>(N + 1, 0));
    parent[0] = direct_parent;
    for (int k = 1; k <= max_step; k++)
        for (int n = N; n >= 1; n--)
            parent[k][n] = parent[k - 1][parent[k - 1][n]];

    return parent;
}

// 구버전
// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>
// #include <cmath>

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

// typedef vector<vector<int>> tree_t;
// typedef vector<pair<int, int>> query_set_t;

// void solution(int N, int M, tree_t &temp_tree, query_set_t &query_set);
// tree_t organize_tree(int N, tree_t &temp_tree, vector<int> &depth);

// int main(int argc, char const *argv[])
// {
//     FAST_IO;
//     if constexpr (local)
//         (void)!freopen("./input.txt", "r", stdin);

//     int N, M, node1, node2, query1, query2;

//     cin >> N;
//     tree_t temp_tree(N + 1);

//     for (int i = 0; i < N - 1; i++)
//     {
//         cin >> node1 >> node2;
//         temp_tree[node1].push_back(node2);
//         temp_tree[node2].push_back(node1);
//     }

//     cin >> M;
//     query_set_t query_set(M);

//     for (int i = 0; i < M; i++)
//         cin >> query_set[i].first >> query_set[i].second;

//     solution(N, M, temp_tree, query_set);
//     return 0;
// }

// void solution(int N, int M, tree_t &temp_tree, query_set_t &query_set)
// {
//     int node1, node2, depth_diff, step;
//     vector<int> depth(N + 1);
//     vector<int> answer_set(M);
//     tree_t parent = organize_tree(N, temp_tree, depth);

//     for (int i = 0; i < M; i++)
//     {
//         node1 = query_set[i].first, node2 = query_set[i].second;
//         // node1 을 더 깊은 것으로 고정
//         if (depth[node1] < depth[node2])
//             swap(node1, node2);

//         depth_diff = depth[node1] - depth[node2]; // 깊이 차이 계산

//         // 두 노드의 깊이를 맞춰줌
//         while (depth_diff != 0)
//         {
//             step = int(log2(depth_diff)); // step : (1 << K) <= depth_diff인 최대 K
//             node1 = parent[step][node1];
//             depth_diff = depth[node1] - depth[node2];
//         }

//         if (node1 == node2)
//             answer_set[i] = node1;
//         else
//         {
//             // 같은 깊이에서 공통 조상을 찾음
//             int max_step = int(log2(depth[node1]));

//             // 이렇게 안해도 됨, 물론 이것도 가능은 함
//             // while (max_step >= 0)
//             // {
//             //     if (parent[max_step][node1] == parent[max_step][node2])
//             //     {
//             //         if (max_step == 0)
//             //         {
//             //             answer_set[i] = parent[max_step][node1];
//             //             break;
//             //         }
//             //         else
//             //         {
//             //             max_step--;
//             //         }
//             //     }
//             //     else
//             //     {
//             //         node1 = parent[max_step][node1];
//             //         node2 = parent[max_step][node2];
//             //         max_step = int(log2(depth[node1]));
//             // 8칸 점프하면 안되는데, 4칸 점프해도 가능하면 다음 점프는 4칸 점프가 불가능함!
//             // ^ 이게 굳이 max_step를 다시 계산할 필요가 없는 이유!, 순차적으로 감소시킨걸 구현해도 되는 이유!
//             //     }
//             // }
//             for (int step = max_step; step >= 0; step--)
//                 if (parent[step][node1] != parent[step][node2]) // 점프해도 되는지만 확인
//                 {
//                     node1 = parent[step][node1]; // 확인 후 점프
//                     node2 = parent[step][node2];
//                 }
//             // 이 시점에서 node1과 node2는 LCA의 바로 아래 자식들
//             answer_set[i] = parent[0][node1];
//         }
//     }
//     for (const int &answer : answer_set)
//         cout << answer << "\n";
// }

// tree_t organize_tree(int N, tree_t &temp_tree, vector<int> &depth)
// {
//     // 기존 temp_tree는 무방향 트리라서 부모 자식 관계를 BFS로 알아내야함
//     vector<int> direct_parent(N + 1, 0); //
//     vector<bool> visited(N + 1, false);
//     visited[1] = true;

//     queue<pair<int, int>> Q;
//     Q.push({0, 1});
//     while (!Q.empty())
//     {
//         pair<int, int> node = Q.front(); // depth, current_node
//         Q.pop();
//         for (const int &next_node : temp_tree[node.second])
//             if (!visited[next_node])
//             {
//                 visited[next_node] = true;
//                 depth[next_node] = node.first + 1;      // 깊이 설정
//                 direct_parent[next_node] = node.second; // 부모 설정
//                 Q.push({node.first + 1, next_node});
//             }
//     }

//     // create parent table
//     int table_depth = int(log2(*max_element(depth.begin(), depth.end()))); // 1 << K <= log2(가장 깊은 노드의 깊이)인 최대 K
//     tree_t parent(table_depth + 1, vector<int>(N + 1, 0));
//     parent[0] = direct_parent;
//     for (int k = 1; k <= table_depth; k++)
//         for (int n = N; n >= 1; n--)
//             parent[k][n] = parent[k - 1][parent[k - 1][n]];

//     return parent;
// }