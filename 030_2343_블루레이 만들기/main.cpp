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

void solution(int N, int M, vector<int> &vec, int L, int R);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;
    int max_time = 0, sum_time = 0;
    vector<int> vec(N, 0);
    for (int i = 0; i < N; i++)
    {
        int lecture = 0;
        cin >> lecture;
        max_time = max(max_time, lecture);
        sum_time += lecture;
        vec[i] = lecture;
    }

    solution(N, M, vec, max_time, sum_time);
    return 0;
}

void solution(int N, int M, vector<int> &vec, int left, int right)
{
    while (left <= right)
    {
        int mid = (left + right) / 2;
        int saved_lectures = 0;
        int blueray_disks = 0;
        for(int lecture : vec)
        {
            if (saved_lectures + lecture > mid)
            {
                blueray_disks++;
                saved_lectures = 0;
            }
            saved_lectures += lecture;
        }
        if (saved_lectures != 0)
            blueray_disks++;

        if (blueray_disks > M)
            left = mid + 1;
        else
            right = mid - 1;
    }
    cout << left;
}