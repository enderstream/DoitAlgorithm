#include <iostream>
#include <vector>

using namespace std;

void solution(int N);

int main(int argc, const char *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;

    solution(N);
    return 0;
}

void solution(int N)
{
    int sum = 1;
    int cnt = 1;
    int i = 1, j = 1;

    while (j != N)
        if (sum < N)
            sum += ++j;
        else if (sum > N)
            sum -= i++;
        else
        {
            sum += ++j;
            cnt++;
        }
    cout << cnt;
}