#include <iostream>
#include <algorithm>
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

void solution(int n, vector<int> &nums);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int n;
    cin >> n;
    vector<int> nums(n);
    for (int &num : nums)
        cin >> num;

    solution(n, nums);
    return 0;
}

void solution(int n, vector<int> &nums)
{
    vector<int> DP_L(n, 0);
    vector<int> DP_R(n, 0);
    DP_L[0] = nums[0];
    DP_R[n - 1] = nums[n - 1];
    int result = DP_L[0];

    for (int i = 1; i <= n - 1; i++)
    {
        DP_L[i] = max(DP_L[i - 1] + nums[i], nums[i]);
        result = max(DP_L[i], result);
    }

    for (int i = n - 2; i >= 0; i--)
        DP_R[i] = max(DP_R[i + 1] + nums[i], nums[i]);

    for (int i = 1; i < n - 1; i++)
        result = max(result, DP_L[i - 1] + DP_R[i + 1]);

    cout << result;
}