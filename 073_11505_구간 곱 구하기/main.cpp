#include <iostream>
#include <vector>
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

#define MOD 1000000007

using namespace std;

typedef long long i64;

void solution(int N, int M, int K, vector<int> &origin);
void update_tree(int index, int alter, int N, vector<i64> &segment_tree);
void get_product(int leaf_start, int from, int to, vector<i64> &segment_tree);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M, K;
    cin >> N >> M >> K;

    vector<int> origin(N + 1, 1);
    for (int i = 1; i <= N; i++)
        cin >> origin[i];

    solution(N, M, K, origin);
    return 0;
}

void solution(int N, int M, int K, vector<int> &origin)
{
    int a, b, c;
    int level = int(ceil(log2(N)));
    int leaf_start = (1 << level);
    vector<i64> segment_tree(1 << (level + 1), 0);

    // create segment tree
    for (int i = 1; i <= N; i++)
        segment_tree[leaf_start + i - 1] = origin[i];

    for (int i = leaf_start - 1; i >= 1; i--)
        segment_tree[i] = (segment_tree[i * 2] * segment_tree[i * 2 + 1]) % MOD;

    for (int i = 0; i < M + K; i++)
    {
        cin >> a >> b >> c;
        if (a == 1)
            update_tree(leaf_start + b - 1, c, N, segment_tree);
        else // a == 2
            get_product(leaf_start, b, c, segment_tree);
    }
}

void update_tree(int index, int alter, int N, vector<i64> &segment_tree)
{
    segment_tree[index] = alter;
    for (int i = index; i >= 2; i /= 2)
        if (i % 2 == 0)
            segment_tree[i / 2] = (segment_tree[i] * segment_tree[i + 1]) % MOD;
        else
            segment_tree[i / 2] = (segment_tree[i] * segment_tree[i - 1]) % MOD;
}

void get_product(int leaf_start, int from, int to, vector<i64> &segment_tree)
{
    int product = 1;
    int left = leaf_start + from - 1;
    int right = leaf_start + to - 1;

    while (left <= right)
    {
        if (left % 2 == 1)
            product = (segment_tree[left++] * product) % MOD;
        if (right % 2 == 0)
            product = (segment_tree[right--] * product) % MOD;
        left /= 2;
        right /= 2;
    }
    cout << product % MOD << "\n";
}