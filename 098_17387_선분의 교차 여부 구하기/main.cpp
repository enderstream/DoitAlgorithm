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

typedef struct point
{
    int x;
    int y;
} point_t;

void solution(point_t &P1, point_t &P2, point_t &P3, point_t &P4);
bool is_cross(point_t &P1, point_t &P2, point_t &P3, point_t &P4);
bool is_overlab(point_t &P1, point_t &P2, point_t &P3, point_t &P4);
int get_CCW(point_t &P1, point_t &P2, point_t &P3);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    point_t P1, P2, P3, P4;
    cin >> P1.x >> P1.y >> P2.x >> P2.y >> P3.x >> P3.y >> P4.x >> P4.y;
    solution(P1, P2, P3, P4);
    return 0;
}

void solution(point_t &P1, point_t &P2, point_t &P3, point_t &P4)
{
    cout << (is_cross(P1, P2, P3, P4) ? 1 : 0);
}

bool is_cross(point_t &P1, point_t &P2, point_t &P3, point_t &P4)
{
    int ABC = get_CCW(P1, P2, P3);
    int ABD = get_CCW(P1, P2, P4);
    int CDA = get_CCW(P3, P4, P1);
    int CDB = get_CCW(P3, P4, P2);

    if (ABC * ABD == 0 && CDA * CDB == 0)
        return is_overlab(P1, P2, P3, P4);
    else if (ABC * ABD <= 0 && CDA * CDB <= 0)
        return true;
    return false;
}

bool is_overlab(point_t &P1, point_t &P2, point_t &P3, point_t &P4)
{
    return (min(P1.x, P2.x) <= max(P3.x, P4.x) && min(P3.x, P4.x) <= max(P1.x, P2.x) && min(P1.y, P2.y) <= max(P3.y, P4.y) && min(P3.y, P4.y) <= max(P1.y, P2.y));
}

int get_CCW(point_t &P1, point_t &P2, point_t &P3)
{
    long long v = 1LL * (P2.x - P1.x) * (P3.y - P1.y) - 1LL * (P2.y - P1.y) * (P3.x - P1.x);
    return (v > 0) - (v < 0); // 1, 0, -1
}
