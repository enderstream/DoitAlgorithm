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

typedef vector<vector<int>> tree_t;
typedef vector<pair<int, int>> query_set_t;

void solution(int N, int M, tree_t &temp_tree, query_set_t &query_set);
void organize_tree(int N, tree_t &temp_tree, vector<int> &depth, vector<int> &parent);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M, node1, node2, query1, query2;

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
    vector<int> depth(N + 1);
    vector<int> parent(N + 1);
    vector<int> answer_set(M);
    organize_tree(N, temp_tree, depth, parent);
    int node1, node2;

    for (int i = 0; i < M; i++)
    {
        node1 = query_set[i].first, node2 = query_set[i].second;
        // node1 을 더 깊은 것으로 고정
        if (depth[node1] < depth[node2])
            swap(node1, node2);

        // 두 노드의 깊이를 맞춰줌
        while (depth[node1] != depth[node2])
            node1 = parent[node1];

        // 같은 깊이에서 공통 조상을 찾음
        while (node1 != node2)
        {
            node1 = parent[node1];
            node2 = parent[node2];
        }
        answer_set[i] = node1;
    }
    for (const int &answer : answer_set)
        cout << answer << "\n";
}

void organize_tree(int N, tree_t &temp_tree, vector<int> &depth, vector<int> &parent)
{
    // 기존 temp_tree는 무방향 트리라서 부모 자식 관계를 BFS로 알아내야함
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
                depth[next_node] = node.first + 1; // 깊이 설정
                parent[next_node] = node.second;   // 부모 설정
                Q.push({node.first + 1, next_node});
            }
    }
}

// 백준 제한시간이 비정상적으로 빡빡해서 통과 못한 코드
// 이차원 벡터의 캐시 히트가 낮아서 통과 실패

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>

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
// tree_t organize_tree(int N, tree_t &temp_tree);

// int main(int argc, const char *argv[])
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
//     tree_t tree = organize_tree(N, temp_tree);
//     vector<int> answer_set(M);
//     int node1, node2;

//     for (int i = 0; i < M; i++)
//     {
//         node1 = query_set[i].first, node2 = query_set[i].second;
//         // node1 을 더 깊은 것으로 고정
//         if (tree[node1][0] < tree[node2][0])
//             swap(node1, node2);

//         // 두 노드의 깊이를 맞춰줌
//         while (tree[node1][0] != tree[node2][0])
//             node1 = tree[node1][1];

//         // 같은 깊이에서 공통 조상을 찾음
//         while (node1 != node2)
//         {
//             node1 = tree[node1][1];
//             node2 = tree[node2][1];
//         }
//         answer_set[i] = node1;
//     }
//     for (const int &answer : answer_set)
//         cout << answer << "\n";
// }

// tree_t organize_tree(int N, tree_t &temp_tree)
// {
//     // 기존 temp_tree는 무방향 트리라서 부모 자식 관계를 BFS로 알아내야함
//     tree_t tree(N + 1, vector<int>(2, 0)); // 인덱스: 노드번호 | 0: 깊이, 1: 부모, 자식은 필요X
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
//                 tree[next_node][0] = node.first + 1; // 깊이 설정
//                 tree[next_node][1] = node.second;    // 부모 설정
//                 Q.push({node.first + 1, next_node});
//             }
//     }

//     return tree;
// }