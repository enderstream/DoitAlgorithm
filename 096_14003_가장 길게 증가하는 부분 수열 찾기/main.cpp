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

void solution(int N, vector<int> &A);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    solution(N, A);
    return 0;
}

void solution(int N, vector<int> &A)
{
    vector<int> DP(N);     // memoize for index
    vector<int> min_tails; // memoize for minimum tails for every LIS wrt length

    for (int i = 0; i < N; i++)
    {
        vector<int>::iterator it = lower_bound(min_tails.begin(), min_tails.end(), A[i]);
        int idx = it - min_tails.begin();
        if (it == min_tails.end())
            min_tails.push_back(A[i]);
        else
            *it = A[i];

        DP[i] = idx + 1;
    }

    int LIS_len = *max_element(DP.begin(), DP.end());
    cout << LIS_len << "\n";

    vector<int> LIS(LIS_len);
    for (int i = N - 1; i >= 0; i--)
        if (DP[i] == LIS_len)
            LIS[--LIS_len] = A[i];

    for (const int L : LIS)
        cout << L << " ";
}