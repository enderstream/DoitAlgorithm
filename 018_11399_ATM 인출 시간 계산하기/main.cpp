#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

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
    // bubble sort from back
    for (int i = 1; i < N; i++)
        for (int j = i; j > 0; j--)
            if (vec[j - 1] > vec[j])
                swap(vec[j], vec[j - 1]);
            else
                break;

    for (int i = 1; i < N; i++)
        vec[i] += vec[i - 1];

    cout << accumulate(vec.begin(), vec.end(), 0);
}