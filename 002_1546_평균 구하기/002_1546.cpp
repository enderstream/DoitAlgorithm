#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

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
    double M = double(*max_element(vec.begin(), vec.end()));
    double sum = accumulate(vec.begin(), vec.end(), double(0));

    cout << (sum * 100.0) / (M * N);
}