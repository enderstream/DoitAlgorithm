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

void solution(int A, int B);
int get_GCD(int A, int B);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
    {
        (void)!freopen("./input.txt", "r", stdin);
        debug << "\n";
    }

    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        int A, B;
        cin >> A >> B;
        if (A < B)
            swap(A, B);
        solution(A, B);
    }

    return 0;
}

void solution(int A, int B)
{
    int G = get_GCD(A, B);
    cout << A * B / G << "\n";
}

int get_GCD(int A, int B)
{
    if (A == B)
        return A;
    else // A > B
    {
        while (A % B != 0)
        {
            A %= B; // :: A < B
            swap(A, B);
        }
        return B;
    }
}