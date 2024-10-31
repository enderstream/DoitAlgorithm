#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

void solution(int N);
bool is_prime(int number);

int main(int argc, char const *argv[])
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
    vector<int> interesting_primes;
    stack<pair<int, int>> stk;

    for (int p : {2, 3, 5, 7})
        stk.push(pair<int, int>(p, 1));

    while (!stk.empty())
    {
        pair<int, int> top = stk.top();
        stk.pop();

        int number = top.first;
        int digit = top.second;

        if (digit == N)
            interesting_primes.push_back(number);
        else
            for (int i : {1, 3, 5, 7, 9})
            {
                int next_number = number * 10 + i;
                if (is_prime(next_number))
                    stk.push(pair<int, int>(next_number, digit + 1));
            }
    }

    sort(interesting_primes.begin(), interesting_primes.end());
    for (auto p : interesting_primes)
        cout << p << "\n";
}

bool is_prime(int number)
{
    if (number % 2 == 0)
        return false;
    for (int i = 3; i * i <= number; i += 2)
        if (number % i == 0)
            return false;
    return true;
}