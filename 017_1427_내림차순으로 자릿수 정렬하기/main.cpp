#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void solution(string N);

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    string N;
    cin >> N;

    solution(N);
    return 0;
}

void solution(string N)
{
    int N_len = N.length();
    vector<int> vec(N_len, 0);

    for (int i = 0; i < N_len; i++)
        vec[i] = N[i] - '0';

    for (int i = 0; i < N_len; i++)
        for (int j = i+1; j < N_len; j++)
            if (vec[i] < vec[j])
                swap(vec[i], vec[j]);
    
    for (int i = 0; i < N_len; i++)
        cout << vec[i];
    
}