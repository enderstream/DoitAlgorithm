#include <iostream>
#include <vector>
#include <numeric>

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

typedef unsigned long long ui64;

void solution(int N, ui64 k);
void solution(int N, vector<int> &perm);
ui64 calc_factorial(int N);

vector<ui64> factorials;

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, problem;
    cin >> N >> problem;

    // 팩토리얼 미리 계산
    factorials.resize(N);
    factorials[0] = 1;
    for (int i = 1; i < N; i++)
        factorials[i] = factorials[i - 1] * i;

    if (problem == 1)
    {
        ui64 k;
        cin >> k;
        solution(N, k - 1); // 1~k 를 0~k-1번째로 변환
    }
    else
    {
        vector<int> perm(N);
        for (int &p : perm)
            cin >> p;

        solution(N, perm);
    }

    return 0;
}

void solution(int N, ui64 k)
{
    vector<ui64> nums(N), answer;
    iota(nums.begin(), nums.end(), 1);

    for (int i = 1; i < N; i++)
    {
        ui64 product = factorials[N - i];
        ui64 section = k / product;
        ui64 end = k % product;
        answer.push_back(nums[section]);
        nums.erase(nums.begin() + section);
        k = end;
    }
    answer.push_back(nums[0]);

    for (const int a : answer)
        cout << a << " ";
}

void solution(int N, vector<int> &perm)
{
    ui64 answer = 1, end = 0;
    vector<ui64> nums(N);
    iota(nums.begin(), nums.end(), 1);

    for (int i = 1; i < N; i++)
    {
        ui64 product = factorials[N - i];
        ui64 section = lower_bound(nums.begin(), nums.end(), perm[i - 1]) - nums.begin();
        answer += product * section;
        end = answer + product - 1;
        if (answer == end)
            break;
        nums.erase(nums.begin() + section);
    }

    cout << answer;
}