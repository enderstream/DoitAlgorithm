#include <iostream>
#include <string>

using namespace std;

void solution(int N, string num);

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N = 0;
    cin >> N;

    string num = "";
    cin >> num;

    solution(N, num);
    return 0;
}

void solution(int N, string num)
{
    int sum = 0;
    for (int i = 0; i < N; i++)
        sum += num[i] - '0';
    cout << sum;
}