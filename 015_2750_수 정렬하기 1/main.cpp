#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solution(int N, vector<int> &vec);

int main(int argc, const char *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;
    vector<int> vec(N, 0);
    for (int i = 0; i < N; i++)
        cin >> vec[i];

    solution(N, vec);
    return 0;
}

void solution(int N, vector<int> &vec)
{
    // bubble sort
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N - 1 - i; j++)
            if (vec[j] > vec[j + 1])
                swap(vec[j], vec[j + 1]);

    for (int i = 0; i < N; i++)
        cout << vec[i] << "\n";
}