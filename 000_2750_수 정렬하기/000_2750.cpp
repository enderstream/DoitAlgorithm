#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solution(int N, vector<int> &vec);

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N = 0;
    cin >> N;
    vector<int> vec(N, 0);
    for (int i = 0; i < N; i++)
        cin >> vec[i];

    solution(N, vec);
    return 0;
}

void solution(int N, vector<int> &vec)
{
    sort(vec.begin(), vec.end());
    for (int i = 0; i < N; i++)
        cout << vec[i] << "\n";
}