#include <iostream>
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

typedef unsigned long long i64;

void solution(i64 A, i64 B);
i64 get_GCD(i64 A, i64 B);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
    {
        (void)!freopen("./input.txt", "r", stdin);
        debug << "\n";
    }

    i64 A, B;
    cin >> A >> B;

    solution(A, B);
    return 0;
}

void solution(i64 A, i64 B)
{
    if (A == B)
        for (int i = 1; i <= A; i++)
            cout << 1;
    else
    {
        i64 G = get_GCD(max(A, B), min(A, B));
        for (int i = 1; i <= G; i++)
            cout << 1;
    }
}

i64 get_GCD(i64 A, i64 B)
{
    // A > B is guaranteed
    while (A % B != 0)
    {
        A %= B;
        swap(A, B);
    }
    return B;
}