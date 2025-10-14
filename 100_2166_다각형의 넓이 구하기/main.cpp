#include <iostream>
#include <vector>
#include <cmath>

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

typedef long long i64;

using namespace std;

typedef struct point
{
    i64 x;
    i64 y;
} point_t;

void solution(int N, vector<point_t> &points);
i64 get_area(point_t &P1, point_t &P2);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;
    vector<point_t> points(N);
    for (point_t &p : points)
        cin >> p.x >> p.y;

    solution(N, points);
    return 0;
}

void solution(int N, vector<point_t> &points)
{
    i64 area = 0;
    for (int i = 0; i < N - 1; i++)
        area += get_area(points[i], points[i + 1]);

    area += get_area(points[N - 1], points[0]);
    cout << fixed;
    cout.precision(1);
    cout << abs(static_cast<double>(area / 2.0));
}

i64 get_area(point_t &P1, point_t &P2)
{
    return P1.x * P2.y - P1.y * P2.x;
}