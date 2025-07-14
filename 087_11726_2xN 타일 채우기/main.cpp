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

#define MOD 10007

using namespace std;

typedef unsigned long long ui64;

void solution(int N);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;

    solution(N);
    return 0;
}

void solution(int N)
{
    // 전형적인 피보나치
    int A = 0, B = 1, C = 1;
    for (int i = 2; i <= N; i++)
    {
        A = B;
        B = C;
        C = (B + A) % MOD;
    }
    cout << C;
}