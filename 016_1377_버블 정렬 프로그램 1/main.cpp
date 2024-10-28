#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solution(int N, vector<pair<int, int>> &vec);

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;
    vector<pair<int, int>> vec(N, pair<int, int>(0, 0));
    for (int i = 0; i < N; i++)
    {
        cin >> vec[i].first;
        vec[i].second = i;
    }

    solution(N, vec);
    return 0;
}

void solution(int N, vector<pair<int, int>> &vec)
{
    sort(vec.begin(), vec.end());
    int max_index_diff = -N;
    for (int i = 0; i < N; i++)
        max_index_diff = max(max_index_diff, vec[i].second - i);

    cout << ++max_index_diff;
}