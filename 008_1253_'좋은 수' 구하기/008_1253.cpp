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

    int N;
    cin >> N;

    vector<int> vec(N, 0);
    for (int i = 0; i < N; i++)
        cin >> vec[i];

    sort(vec.begin(), vec.end());

    if (N <= 2)
        cout << 0;
    else
        solution(N, vec);

    return 0;
}

void solution(int N, vector<int> &vec)
{

    int cnt = 0;
    for (int k = 0; k < N; k++)
    {
        int i = 0;
        int j = N - 1;
        while (i < j)
            if (vec[i] + vec[j] < vec[k])
                i++;
            else if (vec[i] + vec[j] > vec[k])
                j--;
            else
                if (i == k)
                    i++;
                else if (j == k)
                    j--;
                else
                {
                    cnt++;
                    break;
                }
    }
    cout << cnt;
}

/*
2 3 5 7 11 13
2,147,483,647
1,000,000,000

counter example:
5
-1 0 1 2 3
*/