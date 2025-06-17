#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

struct compare
{
    bool operator()(int a, int b)
    {
        int abs_a = abs(a);
        int abs_b = abs(b);
        if (abs_a == abs_b)
            return a > b;
        else
            return abs_a > abs_b;
    }
};

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
    priority_queue<int, vector<int>, compare> PQ;
    for (int i = 0; i < N; i++)
    {
        int command;
        cin >> command;

        if (command != 0)
            PQ.push(command);
        else if (PQ.empty())
            cout << "0\n";
        else
        {
            cout << PQ.top() << "\n";
            PQ.pop();
        }
    }
}