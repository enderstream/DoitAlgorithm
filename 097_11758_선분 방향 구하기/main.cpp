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

using namespace std;

typedef struct point
{
    int x;
    int y;
} point_t;

void solution(point_t P1, point_t P2, point_t P3);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    point_t P1, P2, P3;
    cin >> P1.x >> P1.y >> P2.x >> P2.y >> P3.x >> P3.y;

    solution(P1, P2, P3);
    return 0;
}

void solution(point_t P1, point_t P2, point_t P3)
{
    int CCW = (P2.x - P1.x) * (P3.y - P2.y) - (P2.y - P1.y) * (P3.x - P2.x);
    // or
    // int CCW = P1.x * P2.y + P2.x * P3.y + P3.x * P1.y - P2.x * P1.y - P3.x * P2.y - P1.x * P3.y;
    cout << (CCW > 0) - (CCW < 0);
}