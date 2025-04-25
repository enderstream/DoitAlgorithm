#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

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

int solution(int N, unordered_map<int, vector<int>> &tree, int root);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, node, discard, root;
    cin >> N;

    unordered_map<int, vector<int>> tree;

    for (int i = 0; i < N; i++)
    {
        cin >> node;
        tree[i].push_back(node);
        if (node == -1)
            root = i;
    }

    cin >> discard;

    for (int i = 0; i < N; i++)
        if (i != discard && tree[i][0] != -1)
            tree[tree[i][0]].push_back(i);
    tree.erase(discard);

    cout << (root == discard ? 0 : solution(N, tree, root));
    return 0;
}

int solution(int N, unordered_map<int, vector<int>> &tree, int root)
{
    int leaf_node = 0;
    stack<int> S;
    S.push(root);
    while (!S.empty())
    {
        int node = S.top();
        S.pop();
        if (tree[node].size() == 1)
            leaf_node++;
        else
            for (int i = 1; i < tree[node].size(); i++)
                S.push(tree[node][i]);
    }
    return leaf_node;
}