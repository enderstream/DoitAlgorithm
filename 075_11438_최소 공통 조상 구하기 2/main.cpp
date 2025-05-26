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
int organize_tree(int N, tree_t &temp_tree, vector<int> &depth, vector<int> &parent);

int main(int argc, char const *argv[])
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
    int max_K = organize_tree(N, temp_tree, depth, parent);
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

int organize_tree(int N, tree_t &temp_tree, vector<int> &depth, vector<int> &parent)
{
    // 기존 temp_tree는 무방향 트리라서 부모 자식 관계를 BFS로 알아내야함
    vector<bool> visited(N + 1, false);
    visited[1] = true;
    int max_K = floor(log2(N)) + 1;

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
    return max_K;
}

/*
// max_K를 구할 때 중요한 참고 자료

#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, const char *argv[])
{
    for (int i = 1; i < 1000; i++)
    {
        int k1 = 0, k2 = 0, level = 1;

        while (level <= i)
        {
            level <<= 1;
            k1++;
        }
        k2 = ceil(log2(i)); // 이건 안됨
        // k2 = floor(log2(i)) + 1; // 이건 됨
        if (k1 != k2)
            cout << "i: " << i << " | " << "k1 != k2 :: " << k1 << " != " << k2 << "\n";
    }
}

*/