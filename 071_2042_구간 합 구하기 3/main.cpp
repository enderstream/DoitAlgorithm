// 펜윅트리를 사용한 버전
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

typedef long long i64;

void solution(int N, int M, int K, vector<i64> &fenwik_tree);
void update_tree(int index, i64 delta, int N, vector<i64> &fenwik_tree);
i64 prefix_sum(int index, int N, vector<i64> &fenwik_tree);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    i64 N, M, K;
    cin >> N >> M >> K;

    vector<i64> origin(N + 1, 0);
    for (int i = 1; i <= N; i++)
        cin >> origin[i];

    solution(N, M, K, origin);
    return 0;
}

void solution(int N, int M, int K, vector<i64> &origin)
{
    vector<i64> fenwik_tree(N + 1, 0);
    for (int i = 1; i <= N; i++)
        update_tree(i, origin[i], N, fenwik_tree);

    i64 a, b, c;
    for (int i = 0; i < M + K; i++)
    {
        cin >> a >> b >> c;
        if (a == 1)
        {
            update_tree(b, c - origin[b], N, fenwik_tree);
            origin[b] = c;
        }
        else // a == 2
            cout << (prefix_sum(c, N, fenwik_tree) - prefix_sum(b - 1, N, fenwik_tree)) << "\n";
    }
}

void update_tree(int index, i64 delta, int N, vector<i64> &fenwik_tree)
{
    while (index <= N)
    {
        fenwik_tree[index] += delta;
        index += (index & -index);
    }
}

i64 prefix_sum(int index, int N, vector<i64> &fenwik_tree)
{
    i64 sum = 0;
    while (index > 0)
    {
        sum += fenwik_tree[index];
        index -= (index & -index);
    }
    return sum;
}

/*

// 세그먼트 트리를 사용한 버전

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

int main(int argc, const char *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("input.txt", "r", stdin);

    ll N, M, K, a, b, c, d, sum;
    cin >> N >> M >> K;
    vector<ll> vec(N + 1, 0);
    ll level = (ll)ceil(log2(N));
    ll leaf_start = (1 << level);
    vector<ll> tree((1 << (level + 1)), 0);

    for (ll i = 1; i <= N; i++)
        cin >> vec[i];

    // create segment tree
    for (ll i = 1; i <= N; i++)
        tree[leaf_start + i - 1] = vec[i];

    for (ll i = leaf_start - 1; i >= 1; i--)
        tree[i] = tree[i * 2] + tree[i * 2 + 1];

    for (ll i = 0; i < M + K; i++)
    {
        cin >> a >> b >> c;

        // solution
        if (a == 1) // value update
        {
            d = c - vec[b]; // d :: delta for update
            vec[b] = c;     // update vector
            for (ll i = b + leaf_start - 1; i > 0; i /= 2)
                tree[i] += d; // update_segment tree
        }
        else //  find sum
        {
            sum = 0;
            ll left = leaf_start + b - 1;
            ll right = leaf_start + c - 1;

            while (left <= right)
            {
                if (left % 2 == 1)
                    sum += tree[left++];

                if (right % 2 == 0)
                    sum += tree[right--];

                left /= 2;
                right /= 2;
            }

            cout << sum << "\n";
        }
    }

    return 0;
}

*/