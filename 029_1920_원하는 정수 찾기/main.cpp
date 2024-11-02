#include <iostream>
#include <vector>
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

void solution(int N, vector<long> &vec, int M, vector<long> &targets);
bool binary_search(long target, int N, vector<long> &vec);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N;
    vector<long> vec(N, 0);

    for (int i = 0; i < N; i++)
        cin >> vec[i];

    sort(vec.begin(), vec.end());

    cin >> M;
    vector<long> targets(M, 0);
    for (int i = 0; i < M; i++)
        cin >> targets[i];

    solution(N, vec, M, targets);
    return 0;
}

void solution(int N, vector<long> &vec, int M, vector<long> &targets)
{
    for (long target : targets)
        binary_search(target, N, vec) ? cout << 1 << "\n" : cout << 0 << "\n";
}

bool binary_search(long target, int N, vector<long> &vec)
{
    int L = 0;
    int R = N - 1;
    while (L <= R)
    {
        int M = (L + R) / 2;
        if (vec[M] > target)
            R = M - 1;
        else if (vec[M] < target)
            L = M + 1;
        else
            return true;
    }
    return false;
}
