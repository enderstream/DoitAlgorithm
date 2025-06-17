#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solution(int N, int M, vector<int> &vec);

int main(int argc, const char *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;
    vector<int> vec(N, 0);
    for (int i = 0; i < N; i++)
        cin >> vec[i];

    sort(vec.begin(), vec.end());

    solution(N, M, vec);
    return 0;
}

void solution(int N, int M, vector<int> &vec)
{
    int i = 0;
    int j = N - 1;
    int cnt = 0;
    while (i < j)
        if (vec[i] + vec[j] > M)
            j--;
        else if (vec[i] + vec[j] < M)
            i++;
        else
        {
            cnt++;
            i++;
            j--;
        }
    cout << cnt;
}