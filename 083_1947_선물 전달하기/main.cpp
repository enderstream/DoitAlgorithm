#include <iostream>

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

#define MOD 1000000000

using namespace std;

typedef unsigned long long ui64;

ui64 solution(ui64 N);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    ui64 N;
    cin >> N;

    cout << solution(N);
    return 0;
}

ui64 solution(ui64 N)
{
    if (N <= 3)
        return N - 1;

    ui64 prev = 1, curr = 2;
    for (ui64 i = 4; i <= N; i++)
    {
        ui64 next = ((i - 1) * (prev + curr)) % MOD;
        prev = curr;
        curr = next;
    }
    return curr;
}