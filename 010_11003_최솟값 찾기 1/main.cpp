#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

void solution(int N, int L);

int main(int argc, const char *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N, L;
    cin >> N >> L;

    solution(N, L);
    return 0;
}

void solution(int N, int L)
{
    deque<pair<int, int>> deq(1, pair<int, int>(-1, 2000000000));
    for (int i = 0; i < N; i++)
    {
        int A_i;
        cin >> A_i;
        
        while (!deq.empty() && deq.back().second > A_i)
            deq.pop_back();
        deq.push_back({i, A_i});
        if (deq.front().first + L <= i)
            deq.pop_front();
        
        cout << deq.front().second << " ";
    }
}

// 2,147,483,647
// 1,000,000,000