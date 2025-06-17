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

void solution(vector<pair<int, int>> meetings);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
    {
        (void)!freopen("./input.txt", "r", stdin);
        debug << "\n";
    }

    int N;
    cin >> N;
    vector<pair<int, int>> meetings(N, pair<int, int>(0, 0));

    for (int i = 0; i < N; i++)
        cin >> meetings[i].first >> meetings[i].second;

    sort(meetings.begin(), meetings.end(), [](const pair<int, int> &a, const pair<int, int> &b)
         { return (a.second == b.second) ? (a.first < b.first) : (a.second < b.second); });

    solution(meetings);
    return 0;
}

void solution(vector<pair<int, int>> meetings)
{
    int max_meetings = 0, start = 0, end = 0;
    for (auto &meeting : meetings)
        if (meeting.first >= end)
        {
            max_meetings++;
            start = meeting.first, end = meeting.second;
        }

    cout << max_meetings;
}