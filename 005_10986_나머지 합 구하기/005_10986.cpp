#include <iostream>
#include <vector>

using namespace std;

void solution(int N, int M, vector<int> &vec);

int main(int argc, char const *argv[])
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
        vec[i] %= M;
    }

    solution(N, M, vec);
    return 0;
}

void solution(int N, int M, vector<int> &vec)
{
    long cases = 0;
    vector<long> remainders(M, 0);

    for (int i = 1; i <= N; i++)
    {
        remainders[vec[i]]++;
        if (vec[i] == 0)
            cases++;
    }

    for (int i = 0; i < M; i++)
        cases += remainders[i] * (remainders[i] - 1) / 2;
    cout << cases;
}