#include <iostream>
#include <vector>

using namespace std;

void solution(vector<int> vec);

int main(int argc, const char *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;

    vector<int> vec(10001, 0);

    for (int i = 0; i < N; i++)
    {
        int n;
        cin >> n;
        vec[n]++;
    }

    solution(vec);
    return 0;
}

void solution(vector<int> vec)
{
    for (int i = 1; i <= 10000; i++)
        for (int cnt = vec[i]; cnt > 0; cnt--)
            cout << i << "\n";
}