#include <iostream>
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

typedef unordered_map<char, pair<char, char>> tree_t;

void solution(int N, tree_t &tree);
void preorder(tree_t &tree);
void inorder(tree_t &tree);
void postorder(tree_t &tree);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;
    char node, left, right;
    tree_t tree;
    for (int i = 0; i < N; i++)
    {
        cin >> node >> left >> right;
        tree[node] = {left, right};
    }

    solution(N, tree);
    return 0;
}

void solution(int N, tree_t &tree)
{
    preorder(tree);
    inorder(tree);
    postorder(tree);
}

void preorder(tree_t &tree)
{
    stack<char> S;
    char node = 'A';
    S.push(node);

    while (!S.empty())
    {
        node = S.top();
        cout << node;
        S.pop();
        if (tree[node].second != '.')
            S.push(tree[node].second);

        if (tree[node].first != '.')
            S.push(tree[node].first);
    }
    cout << "\n";
}

void inorder(tree_t &tree)
{
    stack<char> S;
    char node = 'A';
    while (true)
        if (node != '.')
        {
            S.push(node);
            node = tree[node].first;
        }
        else if (!S.empty())
        {
            node = S.top();
            S.pop();
            cout << node;
            node = tree[node].second;
        }
        else
            break;
    cout << "\n";
}

void postorder(tree_t &tree)
{
    stack<char> S;
    stack<char> visited;
    char node = 'A';
    S.push(node);

    while (!S.empty())
    {
        node = S.top();
        S.pop();
        visited.push(node);
        if (tree[node].first != '.')
            S.push(tree[node].first);
        if (tree[node].second != '.')
            S.push(tree[node].second);
    }
    while (!visited.empty())
    {
        cout << visited.top();
        visited.pop();
    }
    cout << "\n";
}