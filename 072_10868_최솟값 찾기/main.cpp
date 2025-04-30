#include <iostream>
#include <vector>
#include <cmath>
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

#define INF 2000000000

using namespace std;

void solution(int N, int M, vector<int> &vec);
void find_min(int a, int b, int leaf_start, vector<int> &segment_tree);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;

    vector<int> vec(N + 1, 0);
    for (int i = 1; i <= N; i++)
        cin >> vec[i];

    solution(N, M, vec);
    return 0;
}

void solution(int N, int M, vector<int> &vec)
{
    int a, b;
    int level = (int)ceil(log2(N));
    int leaf_start = (1 << level);
    vector<int> segement_tree(1 << (level + 1), 0);

    // create segment tree
    for (int i = 1; i <= N; i++)
        segement_tree[leaf_start + i - 1] = vec[i];

    for (int i = leaf_start - 1; i >= 1; i--)
        segement_tree[i] = min(segement_tree[i * 2], segement_tree[i * 2 + 1]);

    for (int i = 0; i < M; i++)
    {
        cin >> a >> b;
        find_min(a, b, leaf_start, segement_tree);
    }
}

void find_min(int a, int b, int leaf_start, vector<int> &segment_tree)
{
    int section_min = INF;
    int left = leaf_start + a - 1;
    int right = leaf_start + b - 1;

    while (left <= right)
    {
        if (left % 2 == 1)
            section_min = min(section_min, segment_tree[left++]);
        if (right % 2 == 0)
            section_min = min(section_min, segment_tree[right--]);

        left /= 2;
        right /= 2;
    }

    cout << section_min << "\n";
}