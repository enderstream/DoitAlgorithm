#include <iostream>
#include <queue>

using namespace std;

void solution(queue<int> Q);

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;
    queue<int> Q;
    for (int i = 1 ; i <= N; i++)
        Q.push(i);
    
    solution(Q);
    return 0;
}

void solution(queue<int> Q)
{
    while (Q.size()> 1)
    {
        Q.pop();
        Q.push(Q.front());
        Q.pop();
    }
    cout << Q.front();
}