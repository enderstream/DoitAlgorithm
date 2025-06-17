#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

map<string, int> ACGT{
    {"A", 0},
    {"C", 1},
    {"G", 2},
    {"T", 3}};

void solution(int S, int P, string &DNA_str, vector<int> &DNA_vec);
bool is_password_strong(vector<int> &window, vector<int> &DNA_vec);

int main(int argc, const char *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int S, P;
    cin >> S >> P;
    string DNA_str; // CCTGGATTG
    cin >> DNA_str;
    vector<int> DNA_vec(4, 0);
    for (int k = 0; k < 4; k++)
        cin >> DNA_vec[k];

    solution(S, P, DNA_str, DNA_vec);
    return 0;
}

void solution(int S, int P, string &DNA_str, vector<int> &DNA_vec)
{
    int cnt = 0;
    vector<int> window(4, 0);
    for (int k = 0; k < P; k++)
        window[ACGT[string(1, DNA_str[k])]]++;

    if (is_password_strong(window, DNA_vec))
        cnt++;

    int i = 1;
    int j = P;
    while (j < S)
    {
        window[ACGT[string(1, DNA_str[i - 1])]]--;
        window[ACGT[string(1, DNA_str[j])]]++;
        if (is_password_strong(window, DNA_vec))
            cnt++;
        i++;
        j++;
    }
    cout << cnt;
}

bool is_password_strong(vector<int> &window, vector<int> &DNA_vec)
{
    for (int i = 0; i < 4; i++)
        if (window[i] < DNA_vec[i])
            return false;
    return true;
}