#include <iostream>
#include <vector>

using namespace std;

void solution(int M, vector<int> &vec);

int main(int argc, const char *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;
    vector<int> vec(N + 1, 0);
    for (int i = 1; i <= N; i++)
    {
        cin >> vec[i];
        vec[i] += vec[i - 1];
    }

    solution(M, vec);
    return 0;
}

void solution(int M, vector<int> &vec)
{
    for (int m = 0; m < M; m++)
    {
        int i, j;
        cin >> i >> j;
        cout << vec[j] - vec[i - 1] << "\n";
    }
}