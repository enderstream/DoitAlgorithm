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

void solution(bool zero, int P, int N, vector<int> &pos, vector<int> &neg);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;
    vector<int> pos;
    vector<int> neg;
    bool zero = false;
    for (int i = 0; i < N; i++)
    {
        int number;
        cin >> number;
        if (number > 0)
            pos.push_back(number);
        else if (number < 0)
            neg.push_back(number);
        else
            zero = true;
    }

    sort(pos.begin(), pos.end(), greater<int>()); // 양수는 내림차순
    sort(neg.begin(), neg.end());                 // 음수는 오름차순

    solution(zero, pos.size(), neg.size(), pos, neg);
    return 0;
}

void solution(bool zero, int P, int N, vector<int> &pos, vector<int> &neg)
{
    int sum = 0;
    // 양수 먼저 계산
    // 1부터 처리
    for (int i = P - 1; i >= 0; i--)
        if (pos[i] == 1)
            sum++;

    // 전체 양수 개수 중 1개수 제외
    P -= sum;
    for (int i = 0; i <= P - 2; i += 2)
        sum += pos[i] * pos[i + 1];
    if (P % 2 == 1)
        sum += pos[P - 1];

    // 음수 계산
    for (int i = 0; i <= N - 2; i += 2)
        sum += neg[i] * neg[i + 1];
    if (!zero && N % 2 == 1)
        sum += neg[N - 1];

    cout << sum;
}